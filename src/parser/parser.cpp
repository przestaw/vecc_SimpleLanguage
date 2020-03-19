//
// Created by przemek on 19.03.2020.
//

#include <parser/parser.h>

using namespace vecc;

Parser::Parser() : Parser(nullptr){}

Parser::Parser(std::unique_ptr<Reader> source) : scanner_(std::make_unique<Scanner>(std::move(source))) {}

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
