//
// Created by przemek on 17.03.2020.
//

#include <error/exeception.h>
#include <scanner/scanner.h>

using namespace vecc;

Scanner::Scanner(std::unique_ptr<Reader> reader, const LogLevel &logLevel,
                 std::ostream &out)
    : logLevel_(logLevel), out_(out), reader_(std::move(reader)) {}

bool Scanner::canRead() { return static_cast<bool>(reader_); }

Token Scanner::parseToken() {
  if (canRead()) {
    currentToken = Token(reader_->getCurrentPos());

    tryToken(); // Note:  Handles EOF as first possible case

    if (currentToken.getType() != Token::Type::NaT) {
      if (logLevel_ >= LogLevel::ParsedTokens) {
        out_ << FCYN(BOLD("Token Log : \n")) "Parsed token : "
                    + currentToken.toString() + "\n";
      }

      return currentToken;
    } else {
      throw error::NotAToken(currentToken);
    }
  } else {
    throw error::NoInputStream();
  }
}

Token Scanner::getToken() { return currentToken; }

void Scanner::setReader(std::unique_ptr<Reader> reader) {
  reader_ = std::move(reader);
}

void Scanner::tryToken() {
  while (std::isspace(reader_->peek()) && !reader_->isEoF()) reader_->get();

  currentToken = Token(reader_->getCurrentPos());

  if (reader_->isEoF()) {
    currentToken.setType(Token::Type::EoF);
  } else if (isdigit(reader_->peek())) {
    tryNumberString();
  } else if (reader_->peek() == '"') {
    tryCharString();
  } else if (isalnum(reader_->peek())) {
    tryKeywordOrIdentifier();
  } else {
    tryOperatorOrBracket();
  }
}

void Scanner::tryCharString() {
  reader_->get(); // consume first ' " '
  std::string buf;

  while ((std::isprint(reader_->peek()) || std::isspace(reader_->peek()))
         && reader_->peek() != '"' && !reader_->isEoF()) {
    if (reader_->peek() == '\\') {
      reader_->get();
      // check for escaped ' " ' character -> \"
      if (reader_->peek() == '"') {
        // consume escaped ' " '
        buf.push_back(reader_->get());
      } else if (reader_->peek() == 'n') {
        reader_->get();
        buf.push_back('\n');
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
    currentToken.setType(Token::Type::CharacterString);
  } else {
    // not properly closed
    currentToken.setType(Token::Type::NaT);
  }
  currentToken.setLiteral(buf);
}

void Scanner::tryNumberString() {
  std::string buf;
  buf.push_back(reader_->get());

  while (std::isdigit(reader_->peek())) { buf.push_back(reader_->get()); }

  currentToken.setType(Token::Type::NumberString);
  currentToken.setLiteral(buf);
}

void Scanner::tryOperatorOrBracket() {
  std::string buf;
  buf.push_back(reader_->get());
  currentToken.setType(Token::findSymbolType(buf.front()));
  if (currentToken.getType() != Token::Type::NaT) {
    Token::Type testForTwoSymbol =
        Token::checkSecondSecond(buf.front(), reader_->peek());
    if (testForTwoSymbol != Token::Type::NaT) {
      buf.push_back(reader_->get());
      currentToken.setType(testForTwoSymbol);
    } // orginal one-symbol type untouched, reader in same pos
  }   // else invalid operator
  currentToken.setLiteral(buf);
}

void Scanner::tryKeywordOrIdentifier() {
  std::string buf;
  while (!reader_->isEoF()
         && (std::isalnum(reader_->peek()) || reader_->peek() == '_')) {
    buf.push_back(reader_->get());
  }

  currentToken.setLiteral(buf);
  currentToken.setType(Token::findKeywordType(buf));

  if (currentToken.getType() == Token::Type::NaT) {
    currentToken.setType(Token::Type::Identifier);
  }
}
