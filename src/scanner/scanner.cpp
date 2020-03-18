//
// Created by przemek on 17.03.2020.
//

#include <scanner/scanner.h>
#include <vecc_exeception.h>

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
        throw vecc::NoInputStream(); // TODO : no reader attached
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
        tryNumberString(newToken);
    } else if (reader_->peek() == '"') {
        tryCharString(newToken);
        // FIXME  : throw if eof before second " ???
    } else if (isalnum(reader_->peek())) {
        tryKeyword(newToken);
        // if not keyword it is Identifier
        if(newToken.getType() == Token::Type::NaT){
            newToken.setType(Token::Type::Identifier);
        }
    } else {
        tryOperatorOrBracket(newToken);
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
    reader_->get(); // consume first ' " '
    std::string buf;

    while ((std::isprint(reader_->peek()) || std::isspace(reader_->peek()))
           && reader_->peek() != '"'
           && !reader_->isEoF()) {
        if (reader_->peek() == '\\') {
            reader_->get();
            // check for escaped ' " ' character -> \"
            if (reader_->peek() == '"') {
                // consume escaped ' " '
                buf.push_back(reader_->get());
            } else {
                // push back ' \ ' character
                buf.push_back('\\');
            }
        } else {
            buf.push_back(reader_->get());
        }
    }

    // check for closing ' " '
    if (reader_->peek() == '"') {
        // consume last ' " '
        reader_->get();
        newToken.setType(Token::Type::CharacterString);
    } else {
        // not properly closed
        newToken.setType(Token::Type::NaT);
    }
    newToken.setLiteral(buf);
}

void Scanner::tryNumberString(Token &newToken) {
    std::string buf;
    buf.push_back(reader_->get());

    while (std::isdigit(reader_->peek())) {
        buf.push_back(reader_->get());
    }

    newToken.setType(Token::Type::NumberString);
    newToken.setLiteral(buf);
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
