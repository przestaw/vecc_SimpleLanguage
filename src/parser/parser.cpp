//
// Created by przemek on 19.03.2020.
//

#include <parser/parser.h>
#include <AST/statement/return_stmt.h>
#include <AST/statement/while_stmt.h>
#include <AST/statement/if_stmt.h>
#include <AST/expression/base_math_expr.h>
#include <AST/expression/additive_expr.h>
#include <AST/expression/multiply_expr.h>
#include <AST/expression/base_logic_expr.h>
#include <AST/expression/realtion_expr.h>
#include <AST/expression/and_logic_expr.h>
#include <AST/expression/or_logic_expr.h>
#include <AST/statement/assign_stmt.h>
#include <AST/statement/function_call.h>

using namespace vecc;

Parser::Parser(std::ostream &out)
      : out_(out), scanner_(std::make_unique<Scanner>(nullptr)) {}

Parser::Parser(std::unique_ptr<Reader> source, std::ostream &out)
      : out_(out), scanner_(std::make_unique<Scanner>(std::move(source))) {}

void Parser::setSource(std::unique_ptr<Reader> source) {
  scanner_->setReader(std::move(source));
}

void Parser::parse() {
  scanner_->parseToken();
  while (scanner_->getToken().getType() != Token::Type::EoF) {
    expectToken(Token::Type::Function, [&]() { parseFunctionDef(); });
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
    parseStatementBlock(function->getFunctionBody());

    currentProgram->addFunction(std::move(function));
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
  newBlock = StatementBlock(currentContext);
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
        newBlock.addInstruction(parseIdentifier(token));
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
  Token identifier;
  expectToken(Token::Type::Identifier,
              [&]() { identifier = scanner_->getToken(); });

  if (!currentContext->existVariable(identifier.getLiteral())) {
    std::unique_ptr<AssignStatement> assign;
    currentContext->addVariable(identifier.getLiteral(), Variable());

    if (tryToken(Token::Type::Assignment)) {
      assign = std::make_unique<AssignStatement>(
            *currentContext->findVariable(identifier.getLiteral(), identifier).lock(),
            parseOrExpression());
    } else {
      assign = std::make_unique<AssignStatement>(
            *currentContext->findVariable(identifier.getLiteral(), identifier).lock(),
            std::make_unique<BaseMathExpr>(std::make_unique<Variable>()));
    }

    expectToken(Token::Type::Semicolon);
    return assign;
  } else {
    throw RedefinedVar(identifier);
  }
}

std::unique_ptr<Statement> Parser::parseIdentifier(const Token &identifier) {
  std::unique_ptr<Statement> statement;

  if (tryToken(Token::Type::ParenthesisOpen)) {
    //function
    statement = parseFunctionCall(identifier);
    expectToken(Token::Type::Semicolon);
  } else {
    //variable
    statement = parseAssignStatement(
          //findVariable checks if Variable exists
          currentContext->findVariable(identifier.getLiteral(), identifier)
    );
  }

  return statement;
}

std::unique_ptr<Statement> Parser::parseFunctionCall(const Token &function) {
  if (!currentProgram->existFunction(function.getLiteral())) {
    throw UndefinedFun(function);
  }
  expectToken(Token::Type::BracketOpen);

  Function &fun = currentProgram->findFunction(function.getLiteral());

  std::unique_ptr<FunctionCallStatement> funCall =
      std::make_unique<FunctionCallStatement>(fun);

  while(tryToken(Token::Type::Comma)){
    funCall->addArgument(parseOrExpression());
  }
  expectToken(Token::Type::BracketClose);

  if(fun.size() == funCall->size()){
    return funCall;
  } else {
    throw MismachedArgumentsCount(function, fun.size(), funCall->size());
  }
}

std::unique_ptr<Statement> Parser::parseIfStatement() {
  expectToken(Token::Type::ParenthesisOpen);
  std::unique_ptr<Expression> condition = parseOrExpression();
  expectToken(Token::Type::ParenthesisClose);

  std::unique_ptr<IfStatement> ifStmt =
        std::make_unique<IfStatement>(std::move(condition));

  expectToken(Token::Type::CurlyBracketOpen);
  parseStatementBlock(ifStmt->trueBlock());

  if (tryToken(Token::Type::Else)) {
    expectToken(Token::Type::CurlyBracketOpen);
    parseStatementBlock(ifStmt->falseBlock());
  }

  return ifStmt;
}

std::unique_ptr<Statement> Parser::parseWhileStatement() {
  expectToken(Token::Type::ParenthesisOpen);
  std::unique_ptr<Expression> condition = parseOrExpression();
  expectToken(Token::Type::ParenthesisClose);

  std::unique_ptr<WhileStatement> whileStmt =
        std::make_unique<WhileStatement>(std::move(condition));

  expectToken(Token::Type::CurlyBracketOpen);
  parseStatementBlock(whileStmt->getWhileBody());

  return whileStmt;
}

std::unique_ptr<Statement> Parser::parseReturnStatement() {
  std::unique_ptr<ReturnStatement> returnStatement =
        std::make_unique<ReturnStatement>(parseOrExpression());
  expectToken(Token::Type::Semicolon);
  return returnStatement;
}

std::unique_ptr<Statement> Parser::parsePrintStatement() {
  //TODO
  throw Exception("TODO : Parser::parsePrintStatement");
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
  std::unique_ptr<AddExpr> mathExpr =
        std::make_unique<AddExpr>(parseMultiplyExpression());

  Token token = scanner_->getToken();
  switch (token.getType()) {
    case Token::Type::Plus:
      scanner_->parseToken();
      //TODO : token.pos -> for math exception
      mathExpr->addOperand(parseMultiplyExpression(),
                           AddExpr::OperatorType::Add);
      break;
    case Token::Type::Minus:
      scanner_->parseToken();
      //TODO : token.pos -> for math exception
      mathExpr->addOperand(parseMultiplyExpression(),
                           AddExpr::OperatorType::Substract);
      break;
    default:
      //NOTE: to silence warning
      break;
  }

  return mathExpr;
}

std::unique_ptr<Expression> Parser::parseMultiplyExpression() {
  std::unique_ptr<MultiplyExpr> mathExpr =
        std::make_unique<MultiplyExpr>(parseBaseMathExpression());

  Token token = scanner_->getToken();
  switch (token.getType()) {
    case Token::Type::Divide:
      scanner_->parseToken();
      //TODO : token.pos -> for math exception
      mathExpr->addOperand(parseMultiplyExpression(),
                           MultiplyExpr::OperatorType::Divide);
      break;
    case Token::Type::Modulo:
      scanner_->parseToken();
      //TODO : token.pos -> for math exception
      mathExpr->addOperand(parseMultiplyExpression(),
                           MultiplyExpr::OperatorType::Modulo);
      break;
    case Token::Type::Multiply:
      scanner_->parseToken();
      //TODO : token.pos -> for math exception
      mathExpr->addOperand(parseMultiplyExpression(),
                           MultiplyExpr::OperatorType::Multiply);
      break;
    default:
      //NOTE: to silence warning
      break;
  }

  return mathExpr;
}

std::unique_ptr<Expression> Parser::parseBaseMathExpression() {
  bool unaryMathOp = tryToken(Token::Type::Minus);

  switch (scanner_->getToken().getType()) {
    case Token::Type::NumberString:
      return std::make_unique<BaseMathExpr>(
            std::make_unique<Variable>(Variable({
                                                      std::stoi(scanner_->getToken().getLiteral())
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
  if (tryToken(Token::Type::ParenthesisOpen)) {
    //funCall
    return std::make_unique<BaseMathExpr>(
          parseFunctionCall(scanner_->getToken()), unaryMathOp);
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
                  scanner_->getToken().getLiteral(),
                  scanner_->getToken()).lock().get(),
            val, unaryMathOp);
    } else {
      return std::make_unique<BaseMathExpr>(
            currentContext->findVariable(
                  scanner_->getToken().getLiteral(),
                  scanner_->getToken()).lock().get(),
            unaryMathOp);
    }
  }
}
