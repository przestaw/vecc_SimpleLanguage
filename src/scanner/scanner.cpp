//
// Created by przemek on 17.03.2020.
//

#include <scanner/scanner.h>

using namespace vecc;

Scanner::Scanner() : reader_(nullptr) {}

Scanner::Scanner(std::unique_ptr<Reader> reader) : reader_(std::move(reader)){}

Token Scanner::getToken() {
    if(canRead()){
        Token newToken(reader_->getCurrentPos());

        tryToken(newToken);

        if(newToken.getType() != Token::Type::NaT){
            return newToken;
        } else {
            throw std::exception(); // invalid token
        }
    } else {
        throw std::exception(); // no reader attached
    }
}

void Scanner::setReader(std::unique_ptr<Reader> reader) {
    reader_ = std::move(reader);
}

void Scanner::tryToken(Token &newToken) {
    if(reader_->isEoF()){
        newToken.setType(Token::Type::EoF);
    } else if (isdigit(reader_->peek())) {
        //Try numberString
    } else if (reader_->peek() == '"') {
        //Try string literal
        // Note : throw if eof before second " ?
    } else if (isalnum(reader_->peek())) {
        //Try keyword
        //Try id
    } else {
        //Try operator or bracket
    }
}
