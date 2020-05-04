//
// Created by przemek on 17.03.2020.
//

#include <boost/lexical_cast.hpp>
#include <error/exeception.h>
#include <scanner/scanner.h>

using namespace vecc;
//
// Scanner::Scanner(std::unique_ptr<Reader> reader, const LogLevel &logLevel,
//                 std::ostream &out)
//    : Reader(std::cin), out_(out) {}

Scanner::Scanner(std::istream &input, const LogLevel &logLevel,
                 std::ostream &out)
    : Reader(input), logLevel_(logLevel), out_(out) {}

Scanner::Scanner(Reader reader, const LogLevel &logLevel, std::ostream &out)
    : Reader(std::move(reader)), logLevel_(logLevel), out_(out) {}

Token Scanner::parseToken() {

  currentToken = Token(this->getCurrentPos());

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
}

Token Scanner::getToken() { return currentToken; }

void Scanner::tryToken() {
  while (std::isspace(this->peek()) && !this->isEoF()) this->get();

  if (this->isEoF()) {
    currentToken = Token(this->getCurrentPos(), Token::Type::EoF);
  } else {
    if (isdigit(this->peek())) {
      tryNumberString(this->getCurrentPos());
    } else if (this->peek() == '"') {
      tryCharString(this->getCurrentPos());
    } else if (isalnum(this->peek())) {
      tryKeywordOrIdentifier(this->getCurrentPos());
    } else {
      tryOperatorOrBracket(this->getCurrentPos());
    }
  }
}

void Scanner::tryCharString(const Position &tokenStartPos) {
  this->get(); // consume first ' " '
  std::string buf;

  while ((std::isprint(this->peek()) || std::isspace(this->peek()))
         && this->peek() != '"' && !this->isEoF()) {
    if (this->peek() == '\\') {
      this->get();
      // check for escaped ' " ' character -> \"
      if (this->peek() == '"') {
        // consume escaped ' " '
        buf.push_back(this->get());
      } else if (this->peek() == 'n') {
        this->get();
        buf.push_back('\n');
      } else {
        // push back ' \ ' character
        buf.push_back('\\');
      }
    } else {
      buf.push_back(this->get());
    }
  }

  // check for closing ' " '
  if (this->peek() == '"') {
    // consume last ' " '
    this->get();
    currentToken = Token(buf, tokenStartPos, Token::Type::CharacterString);
  } else {
    // not properly closed
    currentToken = Token(buf, tokenStartPos, Token::Type::NaT);
  }
}

void Scanner::tryNumberString(const Position &tokenStartPos) {
  std::string buf;
  buf.push_back(this->get());

  while (std::isdigit(this->peek())) { buf.push_back(this->get()); }

  unsigned val;
  try {
    val = boost::lexical_cast<int>(buf);
  } catch (const boost::bad_lexical_cast &ex) {
    throw error::InvalidNumberLiteral(Token(buf, tokenStartPos));
  }

  currentToken = Token(val, tokenStartPos);
}

void Scanner::tryOperatorOrBracket(const Position &tokenStartPos) {
  std::string buf;
  buf.push_back(this->get());
  auto firstSymbolType = Token::findSymbolType(buf.front());
  if (firstSymbolType != Token::Type::NaT) {
    auto testForTwoSymbol = Token::checkSecondSecond(buf.front(), this->peek());
    if (testForTwoSymbol != Token::Type::NaT) {
      // consume
      buf.push_back(this->get());
      currentToken = Token(buf, tokenStartPos, testForTwoSymbol);
    } else {
      // orginal one-symbol type untouched, reader in same pos
      currentToken = Token(buf, tokenStartPos, firstSymbolType);
    }
  } else {
    // else invalid operator
    currentToken = Token(buf, tokenStartPos, Token::Type::NaT);
  }
}

void Scanner::tryKeywordOrIdentifier(const Position &tokenStartPos) {
  std::string buf;
  while (!this->isEoF()
         && (std::isalnum(this->peek()) || this->peek() == '_')) {
    buf.push_back(this->get());
  }

  auto tokType = Token::findKeywordType(buf);

  if (tokType != Token::Type::NaT) {
    currentToken = Token(buf, tokenStartPos, tokType);
  } else {
    currentToken = Token(buf, tokenStartPos, Token::Type::Identifier);
  }
}