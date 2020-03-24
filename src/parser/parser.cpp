//
// Created by przemek on 19.03.2020.
//

#include <parser/parser.h>
#include <AST/statement/return_stmt.h>

using namespace vecc;

Parser::Parser(std::ostream &out) : out_(out), scanner_(std::make_unique<Scanner>(nullptr)) {}

Parser::Parser(std::unique_ptr<Reader> source, std::ostream &out) : out_(out), scanner_(
        std::make_unique<Scanner>(std::move(source))) {}

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
    std::unique_ptr<Program> temp = std::move(currentProgram);
    cleanParser(); // FIXME : needed or not? maybe std::swap?
    return temp;
}

void Parser::cleanParser() {
    this->currentProgram = std::make_unique<Program>();
}

bool Parser::tryToken(const Token::Type type, std::function<void()> ifTrue) {
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
    std::unique_ptr<Function> function;

    expectToken(Token::Type::Identifier, [&]() {
        function = std::make_unique<Function>(scanner_->getToken().getLiteral());
    });

    expectToken(Token::Type::ParenthesisOpen);
    parseParameters(*function);

    expectToken(Token::Type::CurlyBracketOpen);
    parseStatementBlock(function->getFunctionBody());

    currentProgram->addFunction(std::move(function));
}

void Parser::parseParameters(Function &def) {
    if (tryToken(Token::Type::Identifier, [&]() { def.addParameter(scanner_->getToken().getLiteral()); })) {

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
                newBlock.addInstruction(parseAssignStatement());
                break;
            case Token::Type::Identifier :
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
                blockStatementParse(*internalBlock);
                newBlock.addInstruction(std::move(internalBlock));
        }
    }
    // Note: we now exit this block
    currentContext = currentContext->getParentContext();
}

std::unique_ptr<Statement> Parser::parseAssignStatement() {
    return std::unique_ptr<Statement>();
}

std::unique_ptr<Statement> Parser::parseIdentifier(const Token &identifier) {
    return std::unique_ptr<Statement>();
}

std::unique_ptr<Statement> Parser::parseFunctionCall() {
    return std::unique_ptr<Statement>();
}

std::unique_ptr<Statement> Parser::parseIfStatement() {
    return std::unique_ptr<Statement>();
}

std::unique_ptr<Statement> Parser::parseWhileStatement() {
    return std::unique_ptr<Statement>();
}

std::unique_ptr<Statement> Parser::parseReturnStatement() {
    return std::unique_ptr<Statement>();
}

std::unique_ptr<Statement> Parser::parsePrintStatement() {
    return std::unique_ptr<Statement>();
}

Variable Parser::parseVectorValue() {
    return Variable();
}

std::unique_ptr<Expression> Parser::orExpressionParse() {
    return std::unique_ptr<Expression>();
}

std::unique_ptr<Expression> Parser::andExpressionParser() {
    return std::unique_ptr<Expression>();
}

std::unique_ptr<Expression> Parser::relationalExpressionParser() {
    return std::unique_ptr<Expression>();
}

std::unique_ptr<Expression> Parser::baseLogicParser() {
    return std::unique_ptr<Expression>();
}

std::unique_ptr<Expression> Parser::additiveExpressionParser() {
    return std::unique_ptr<Expression>();
}

std::unique_ptr<Expression> Parser::multiplyExpressionParser() {
    return std::unique_ptr<Expression>();
}

std::unique_ptr<Expression> Parser::baseMathExpressionParser() {
    return std::unique_ptr<Expression>();
}