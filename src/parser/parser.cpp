//
// Created by przemek on 19.03.2020.
//

#include <parser/parser.h>
#include <AST/statement/return_stmt.h>
#include <AST/statement/while_stmt.h>
#include <AST/statement/if_stmt.h>
#include <AST/statement/assign_stmt.h>
#include <AST/statement/function_call.h>
#include <AST/statement/print_stmt.h>
#include <AST/expression/base_math_expr.h>
#include <AST/expression/additive_expr.h>
#include <AST/expression/multiply_expr.h>
#include <AST/expression/base_logic_expr.h>
#include <AST/expression/realtion_expr.h>
#include <AST/expression/and_logic_expr.h>
#include <AST/expression/or_logic_expr.h>

using namespace vecc;

Parser::Parser(std::ostream &out)
        : out_(out), scanner_(std::make_unique<Scanner>(nullptr)),
          currentProgram(std::make_unique<Program>()), currentContext(nullptr) {}

Parser::Parser(std::unique_ptr<Reader> source, std::ostream &out)
        : out_(out), scanner_(std::make_unique<Scanner>(std::move(source))),
          currentProgram(std::make_unique<Program>()), currentContext(nullptr) {}

void Parser::setSource(std::unique_ptr<Reader> source) {
    scanner_->setReader(std::move(source));
}

void Parser::parse() {
    scanner_->parseToken();
    while (scanner_->getToken().getType() != Token::Type::EoF) {
        expectToken(Token::Type::Function);
        parseFunctionDef();
    }
}

std::unique_ptr<Program> Parser::getProgram() {
    std::unique_ptr<Program> temp = std::make_unique<Program>();
    std::swap(currentProgram, temp);
    return temp;
}

bool Parser::tryToken(const Token::Type type, const std::function<void()> &ifTrue) {
    if (scanner_->getToken().getType() == type) {
        if (ifTrue) {
            ifTrue();
        }
        scanner_->parseToken();
        return true;
    } else {
        return false;
    }
}

void Parser::parseFunctionDef() {
    Token funToken;
    expectToken(Token::Type::Identifier, [&]() {
        funToken = scanner_->getToken();
    });

    if (!currentProgram->existFunction(funToken.getLiteral())) {
        std::unique_ptr<Function> function =
                std::make_unique<Function>(funToken.getLiteral());

        expectToken(Token::Type::ParenthesisOpen);
        parseParameters(*function);

        expectToken(Token::Type::CurlyBracketOpen);

        // NOTE : need to add to allow recursion, reference to save
        Function *funRef = function.get();
        currentProgram->addFunction(std::move(function));

        parseStatementBlock(funRef->getFunctionBody());
    } else {
        throw RedefinedFun(funToken);
    }
}

void Parser::parseParameters(Function &def) {
    if (tryToken(Token::Type::Identifier, [&]() {
        def.addParameter(scanner_->getToken().getLiteral());
    })) {

        while (tryToken(Token::Type::Comma)) {
            expectToken(Token::Type::Identifier, [&]() {
                def.addParameter(scanner_->getToken().getLiteral());
            });
        }
    }
    expectToken(Token::Type::ParenthesisClose);
}

void Parser::parseStatementBlock(StatementBlock &newBlock) {
    currentContext = &newBlock.getContext();

    while (!tryToken(Token::Type::CurlyBracketClose)) {
        Token token = scanner_->getToken();
        switch (token.getType()) {
            default:
                throw UnexpectedToken(token, {Token::Type::If,
                                              Token::Type::While,
                                              Token::Type::Return,
                                              Token::Type::Var,
                                              Token::Type::Identifier,
                                              Token::Type::Print,
                                              Token::Type::CurlyBracketOpen});
                //no need to break
            case Token::Type::Var :
                newBlock.addInstruction(parseInitStatement());
                break;
            case Token::Type::Identifier :
                //funCallStmt or assignment
                newBlock.addInstruction(parseIdentifier());
                break;
            case Token::Type::If :
                newBlock.addInstruction(parseIfStatement());
                break;
            case Token::Type::While :
                newBlock.addInstruction(parseWhileStatement());
                break;
            case Token::Type::Return :
                newBlock.addInstruction(parseReturnStatement());
                break;
            case Token::Type::Print :
                newBlock.addInstruction(parsePrintStatement());
                break;
            case Token::Type::CurlyBracketOpen :
                auto internalBlock = std::make_unique<StatementBlock>();
                parseStatementBlock(*internalBlock);
                newBlock.addInstruction(std::move(internalBlock));
        }
    }
    // Note: we now exit this block
    currentContext = currentContext->getParentContext();
}

Variable Parser::parseVectorValue() {
    std::vector<int> variables;
    auto addNumberLiteral = [&]() {
        //need to convert value to integer
        variables.push_back(std::stoi(scanner_->getToken().getLiteral()));
    };
    scanner_->parseToken(); // parse token after vec
    expectToken(Token::Type::ParenthesisOpen);
    expectToken(Token::Type::NumberString, addNumberLiteral);
    expectToken(Token::Type::Comma);
    expectToken(Token::Type::NumberString, addNumberLiteral);
    //check if 3 dimensional vector
    //FIXME : could be any dim vector -> while
    if (tryToken(Token::Type::Comma)) {
        expectToken(Token::Type::NumberString, addNumberLiteral);
    }
    expectToken(Token::Type::ParenthesisClose);

    return Variable(std::move(variables));
}

std::unique_ptr<Statement> Parser::parseAssignStatement(std::weak_ptr<Variable> variable) {
    auto rValueParse = [&]() {
        expectToken(Token::Type::Assignment);
        std::unique_ptr<Expression> logicExpr(parseOrExpression());
        expectToken(Token::Type::Semicolon);
        return logicExpr;
    };

    if (tryToken(Token::Type::BracketOpen)) {
        // indexed access identifier[position]
        unsigned val;
        expectToken(Token::Type::NumberString, [&]() {
            // Is there need for range check?
            val = static_cast<unsigned>(std::stoul(scanner_->getToken().getLiteral()));
        });

        return std::make_unique<AssignStatement>(*(variable.lock()), val, rValueParse());
    } else {
        // whole var/vec accesss
        return std::make_unique<AssignStatement>(*(variable.lock()), rValueParse());
    }
}


std::unique_ptr<Statement> Parser::parseInitStatement() {
    scanner_->parseToken();
    Token identifier;
    expectToken(Token::Type::Identifier,
                [&]() { identifier = scanner_->getToken(); });

    if (!currentContext->existVariable(identifier.getLiteral())) {
        std::unique_ptr<AssignStatement> assignStmt;
        currentContext->addVariable(identifier.getLiteral(), Variable());

        if (tryToken(Token::Type::Assignment)) {
            assignStmt = std::make_unique<AssignStatement>(
                    *currentContext->findVariable(identifier.getLiteral(), identifier).lock(),
                    parseOrExpression());
        } else {
            assignStmt = std::make_unique<AssignStatement>(
                    *currentContext->findVariable(identifier.getLiteral(), identifier).lock(),
                    std::make_unique<BaseMathExpr>(std::make_unique<Variable>()));
        }

        expectToken(Token::Type::Semicolon);
        return assignStmt;
    } else {
        throw RedefinedVar(identifier);
    }
}

std::unique_ptr<Statement> Parser::parseIdentifier() {
    std::unique_ptr<Statement> stmt;
    Token identifier = scanner_->getToken();
    scanner_->parseToken();

    if (tryToken(Token::Type::ParenthesisOpen)) {
        //function
        stmt = parseFunctionCall(identifier);
        expectToken(Token::Type::Semicolon);
    } else {
        //variable
        stmt = parseAssignStatement(
                //findVariable checks if Variable exists
                currentContext->findVariable(identifier.getLiteral(), identifier)
        );
    }

    return stmt;
}

std::unique_ptr<Statement> Parser::parseFunctionCall(const Token &function) {
    if (!currentProgram->existFunction(function.getLiteral())) {
        throw UndefinedFun(function);
    }

    Function &fun = currentProgram->findFunction(function.getLiteral());

    std::unique_ptr<FunctionCallStatement> funCall =
            std::make_unique<FunctionCallStatement>(fun);

    if (!tryToken(Token::Type::ParenthesisClose)) {
        do {
            funCall->addArgument(parseOrExpression());
        } while (tryToken(Token::Type::Comma));
        expectToken(Token::Type::ParenthesisClose);
    }

    if (fun.size() == funCall->size()) {
        return funCall;
    } else {
        throw MismachedArgumentsCount(function, fun.size(), funCall->size());
    }
}

std::unique_ptr<Statement> Parser::parseIfStatement() {
    scanner_->parseToken();
    expectToken(Token::Type::ParenthesisOpen);
    std::unique_ptr<Expression> condition = parseOrExpression();
    expectToken(Token::Type::ParenthesisClose);

    std::unique_ptr<IfStatement> ifStmt =
            std::make_unique<IfStatement>(std::move(condition));

    expectToken(Token::Type::CurlyBracketOpen);
    //connect to context
    ifStmt->trueBlock() = StatementBlock(currentContext);
    parseStatementBlock(ifStmt->trueBlock());

    if (tryToken(Token::Type::Else)) {
        expectToken(Token::Type::CurlyBracketOpen);
        //connect to context
        ifStmt->falseBlock() = StatementBlock(currentContext);
        parseStatementBlock(ifStmt->falseBlock());
    }

    return ifStmt;
}

std::unique_ptr<Statement> Parser::parseWhileStatement() {
    scanner_->parseToken();
    expectToken(Token::Type::ParenthesisOpen);
    std::unique_ptr<Expression> condition = parseOrExpression();
    expectToken(Token::Type::ParenthesisClose);

    std::unique_ptr<WhileStatement> whileStmt =
            std::make_unique<WhileStatement>(std::move(condition));

    expectToken(Token::Type::CurlyBracketOpen);
    //connect to context
    whileStmt->getWhileBody() = StatementBlock(currentContext);
    parseStatementBlock(whileStmt->getWhileBody());

    return whileStmt;
}

std::unique_ptr<Statement> Parser::parseReturnStatement() {
    scanner_->parseToken();
    std::unique_ptr<ReturnStatement> returnStmt =
            std::make_unique<ReturnStatement>(parseOrExpression());
    expectToken(Token::Type::Semicolon);
    return returnStmt;
}

std::unique_ptr<Statement> Parser::parsePrintStatement() {
    scanner_->parseToken();
    expectToken(Token::Type::ParenthesisOpen);
    std::unique_ptr<PrintStatement> printStmt = std::make_unique<PrintStatement>(out_);
    do {
        if (!tryToken(Token::Type::CharacterString, [&]() {
                printStmt->addString(scanner_->getToken().getLiteral());
            })) {
            printStmt->addExpression(parseOrExpression());
        }
    } while (tryToken(Token::Type::Comma));
    expectToken(Token::Type::ParenthesisClose);
    expectToken(Token::Type::Semicolon);
    return printStmt;
}

std::unique_ptr<Expression> Parser::parseOrExpression() {
    std::unique_ptr<OrLogicExpr> orExpr =
            std::make_unique<OrLogicExpr>(parseAndExpression());

    while (tryToken(Token::Type::Or)) {
        // add operands until other token will appear
        orExpr->addOperand(parseRelationalExpression());
    }

    return orExpr;
}

std::unique_ptr<Expression> Parser::parseAndExpression() {
    std::unique_ptr<AndLogicExpr> andExpr =
            std::make_unique<AndLogicExpr>(parseRelationalExpression());

    while (tryToken(Token::Type::And)) {
        // add operands until other token will appear
        andExpr->addOperand(parseRelationalExpression());
    }

    return andExpr;
}

std::unique_ptr<Expression> Parser::parseRelationalExpression() {
    std::unique_ptr<Expression> lValue = parseBaseLogicExpression();

    Token token = scanner_->getToken();
    switch (token.getType()) {
        case Token::Type::Equality:
            scanner_->parseToken();
            return std::make_unique<RelationExpr>(std::move(lValue),
                                                  RelationExpr::OperatorType::Equal,
                                                  parseBaseLogicExpression());
        case Token::Type::Inequality:
            scanner_->parseToken();
            return std::make_unique<RelationExpr>(std::move(lValue),
                                                  RelationExpr::OperatorType::NotEqual,
                                                  parseBaseLogicExpression());
        case Token::Type::Less:
            scanner_->parseToken();
            return std::make_unique<RelationExpr>(std::move(lValue),
                                                  RelationExpr::OperatorType::Less,
                                                  parseBaseLogicExpression());
        case Token::Type::Greater:
            scanner_->parseToken();
            return std::make_unique<RelationExpr>(std::move(lValue),
                                                  RelationExpr::OperatorType::Greater,
                                                  parseBaseLogicExpression());
        case Token::Type::LessOrEqual:
            scanner_->parseToken();
            return std::make_unique<RelationExpr>(std::move(lValue),
                                                  RelationExpr::OperatorType::LessOrEqual,
                                                  parseBaseLogicExpression());
        case Token::Type::GreaterOrEqual:
            scanner_->parseToken();
            return std::make_unique<RelationExpr>(std::move(lValue),
                                                  RelationExpr::OperatorType::GreaterOrEqual,
                                                  parseBaseLogicExpression());
        default:
            // Not an Relation => just PassValue
            return std::make_unique<RelationExpr>(std::move(lValue),
                                                  RelationExpr::OperatorType::PassValue,
                                                  std::unique_ptr<Expression>(nullptr));
    }
}

std::unique_ptr<Expression> Parser::parseBaseLogicExpression() {
    // return negated if Token: Negation occured
    return std::make_unique<BaseLogicExpr>(parseAdditiveExpression(),
                                           tryToken(Token::Type::Negation));
}

std::unique_ptr<Expression> Parser::parseAdditiveExpression() {
    std::unique_ptr<AddExpr> addExpr =
            std::make_unique<AddExpr>(parseMultiplyExpression());

    Token token = scanner_->getToken();
    switch (token.getType()) {
        case Token::Type::Plus:
            scanner_->parseToken();
            //TODO : token.pos -> for math exception
            addExpr->addOperand(parseMultiplyExpression(),
                                AddExpr::OperatorType::Add);
            break;
        case Token::Type::Minus:
            scanner_->parseToken();
            //TODO : token.pos -> for math exception
            addExpr->addOperand(parseMultiplyExpression(),
                                AddExpr::OperatorType::Substract);
            break;
        default:
            //NOTE: to silence warning
            break;
    }

    return addExpr;
}

std::unique_ptr<Expression> Parser::parseMultiplyExpression() {
    std::unique_ptr<MultiplyExpr> multiExpr =
            std::make_unique<MultiplyExpr>(parseBaseMathExpression());

    Token token = scanner_->getToken();
    switch (token.getType()) {
        case Token::Type::Divide:
            scanner_->parseToken();
            //TODO : token.pos -> for math exception
            multiExpr->addOperand(parseMultiplyExpression(),
                                  MultiplyExpr::OperatorType::Divide);
            break;
        case Token::Type::Modulo:
            scanner_->parseToken();
            //TODO : token.pos -> for math exception
            multiExpr->addOperand(parseMultiplyExpression(),
                                  MultiplyExpr::OperatorType::Modulo);
            break;
        case Token::Type::Multiply:
            scanner_->parseToken();
            //TODO : token.pos -> for math exception
            multiExpr->addOperand(parseMultiplyExpression(),
                                  MultiplyExpr::OperatorType::Multiply);
            break;
        default:
            //NOTE: to silence warning
            break;
    }

    return multiExpr;
}

std::unique_ptr<Expression> Parser::parseBaseMathExpression() {
    bool unaryMathOp = tryToken(Token::Type::Minus);

    Token token = scanner_->getToken();
    switch (token.getType()) {
        case Token::Type::NumberString:
            scanner_->parseToken();
            return std::make_unique<BaseMathExpr>(
                    std::make_unique<Variable>(Variable({
                                                                std::stoi(token.getLiteral())
                                                        })), unaryMathOp);

        case Token::Type::Vec:
            return std::make_unique<BaseMathExpr>(
                    std::make_unique<Variable>(parseVectorValue()), unaryMathOp);

        case Token::Type::Identifier:
            return parseIdentifierValue(unaryMathOp);

        case Token::Type::ParenthesisOpen:
            return std::make_unique<BaseMathExpr>(
                    parseOrExpression(), unaryMathOp);

        default:
            throw UnexpectedToken(scanner_->getToken(), {
                    Token::Type::NumberString,
                    Token::Type::Vec,
                    Token::Type::Identifier,
                    Token::Type::ParenthesisOpen
            });

    }
}

std::unique_ptr<Expression> Parser::parseIdentifierValue(const bool &unaryMathOp) {
    Token identifier = scanner_->getToken();
    scanner_->parseToken();
    if (tryToken(Token::Type::ParenthesisOpen)) {
        //funCall
        return std::make_unique<BaseMathExpr>(
                parseFunctionCall(identifier), unaryMathOp);
    } else {
        //variable
        // NOTE : checking of variable existance is done in findVariable
        if (tryToken(Token::Type::BracketOpen)) {
            unsigned val;
            expectToken(Token::Type::NumberString, [&]() {
                // Is there need for range check?
                val = static_cast<unsigned>(std::stoul(scanner_->getToken().getLiteral()));
            });

            return std::make_unique<BaseMathExpr>(
                    currentContext->findVariable(
                            identifier.getLiteral(),
                            identifier).lock().get(),
                    val, unaryMathOp);
        } else {
            return std::make_unique<BaseMathExpr>(
                    currentContext->findVariable(
                            identifier.getLiteral(),
                            identifier).lock().get(),
                    unaryMathOp);
        }
    }
}
