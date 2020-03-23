//
// Created by przemek on 19.03.2020.
//

#include <parser/parser.h>

using namespace vecc;

Parser::Parser(std::ostream &out) : out_(out), scanner_(std::make_unique<Scanner>(nullptr)){}

Parser::Parser(std::unique_ptr<Reader> source, std::ostream &out) : out_(out), scanner_(std::make_unique<Scanner>(std::move(source))) {}

void Parser::setSource(std::unique_ptr<Reader> source) {
    scanner_->setReader(std::move(source));
}

void Parser::parse() {
    scanner_->parseToken();
    while (scanner_->getToken().getType() != Token::Type::EoF) {
        if (tryToken(Token::Type::Function)) {
            // TODO : parse function
        } else {
            // TODO : throw : expected function declaration
        }
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

void Parser::functionDefParse() {
    std::unique_ptr<Function> function;

    expectToken(Token::Type::Identifier, [&]() {
        function = std::make_unique<Function>(scanner_->getToken().getLiteral());
    });

    expectToken(Token::Type::ParenthesisOpen);
    parametersParse(*function);

    expectToken(Token::Type::CurlyBracketOpen);
    blockStatementParse(function->getFunctionBody());

    currentProgram->addFunction(std::move(function));
}

void Parser::parametersParse(Function &def) {
    if (tryToken(Token::Type::Identifier, [&]() { def.addParameter(scanner_->getToken().getLiteral()); })) {

        while (tryToken(Token::Type::Comma)) {
            expectToken(Token::Type::Identifier, [&]() {
                def.addParameter(scanner_->getToken().getLiteral());
            });
        }
    }
    expectToken(Token::Type::ParenthesisClose);
}

void Parser::blockStatementParse(StatementBlock &newBlock) {
    (void)newBlock;
    //TODO
    while (!tryToken(Token::Type::CurlyBracketClose)) {
        scanner_->parseToken();
    }
}

std::unique_ptr<Statement> Parser::parseAssignStatement() {
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

std::unique_ptr<Statement> Parser::parseStatementBlock() {
    return std::unique_ptr<Statement>();
}

std::unique_ptr<Statement> Parser::parsePrintStatement() {
    return std::unique_ptr<Statement>();
}

Variable Parser::vectorLiteralParse() {
    return Variable();
}

bool Parser::existVariable(Token &tokenId) {
    return false;
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
