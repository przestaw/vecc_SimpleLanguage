//
// Created by przemek on 17.03.2020.
//

#include <scanner/scanner.h>
#include <exeception.h>

using namespace vecc;

Scanner::Scanner() : reader_(nullptr) {}

Scanner::Scanner(std::unique_ptr<Reader> reader) : reader_(std::move(reader)){}

Token Scanner::getToken() {
    if(canRead()){
        Token newToken(reader_->getCurrentPos());

        tryToken(newToken); // Note:  Handles EOF as first possible case

        if(newToken.getType() != Token::Type::NaT){
            return newToken;
        } else {
            throw vecc::Exception("invalid"); // TODO : invalid token
        }
    } else {
        throw std::exception(); // TODO : no reader attached
    }
}

void Scanner::setReader(std::unique_ptr<Reader> reader) {
    reader_ = std::move(reader);
}

void Scanner::tryToken(Token &newToken) {
    while (std::isspace(reader_->peek()) && !reader_->isEoF())
        reader_->get();

    if(reader_->isEoF()){
        newToken.setType(Token::Type::EoF);
    } else if (isdigit(reader_->peek())) {
        tryNumberString(newToken); //TODO
    } else if (reader_->peek() == '"') {
        tryCharString(newToken); //TODO
        // Note : throw if eof before second " ?
    } else if (isalnum(reader_->peek())) {
        tryKeyword(newToken);
        if(newToken.getType() == Token::Type::NaT){
            newToken.setType(Token::Type::Identifier);
        }
    } else {
        //Try operator or bracket
        tryOperatorOrBracket(newToken);
        // TODO
    }
}

void Scanner::tryKeyword(Token &newToken) {
    std::string buf;
    while (!reader_->isEoF() && (std::isalnum(reader_->peek()) || reader_->peek() == '_')) {
        buf.push_back(reader_->get());
    }
    newToken.setLiteral(buf);
    newToken.setType(Token::findKeywordType(buf));
}

void Scanner::tryCharString(Token &newToken) {
    //TODO
}

void Scanner::tryNumberString(Token &newToken) {
    //TODO
}

void Scanner::tryOperatorOrBracket(Token &newToken) {
    std::string buf;
    buf.push_back(reader_->get());
    newToken.setType(Token::findSymbolType(buf.front()));
    if(newToken.getType() != Token::Type::NaT){
        Token::Type testForTwoSymbol = Token::checkSecondSecond(buf.front(), reader_->peek());
        if(testForTwoSymbol != Token::Type::NaT){
            buf.push_back(reader_->get());
            newToken.setType(testForTwoSymbol);
        } // orginal one-symbol type untouched, reader in same pos
        newToken.setLiteral(buf);
    } // else invalid operator
}
