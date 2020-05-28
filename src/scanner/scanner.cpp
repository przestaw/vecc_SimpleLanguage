//
// Created by przemek on 17.03.2020.
//

#include <boost/lexical_cast.hpp>
#include <error/exeception.h>
#include <scanner/scanner.h>

using namespace vecc;

Scanner::Scanner(std::istream &input, const LogLevel &logLevel,
                 std::ostream &out)
    : reader_(std::make_unique<Reader>(input)), logLevel_(logLevel), out_(out) {
}

Scanner::Scanner(std::unique_ptr<Reader> reader, const LogLevel &logLevel,
                 std::ostream &out)
    : reader_(std::move(reader)), logLevel_(logLevel), out_(out) {
}

Token Scanner::readToken() {

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
}

Token Scanner::getToken() { return currentToken; }

void Scanner::tryToken() {
  while (std::isspace(reader_->peek()) && !reader_->isEoF()) reader_->get();

  if (reader_->isEoF()) {
    currentToken = Token(reader_->getCurrentPos(), Token::Type::EoF);
  } else {
    if (isdigit(reader_->peek())) {
      tryNumberString(reader_->getCurrentPos());
    } else if (reader_->peek() == '"') {
      tryCharString(reader_->getCurrentPos());
    } else if (isalnum(reader_->peek())) {
      tryKeywordOrIdentifier(reader_->getCurrentPos());
    } else {
      tryOperatorOrBracket(reader_->getCurrentPos());
    }
  }
}

void Scanner::tryCharString(const Position &tokenStartPos) {
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
    currentToken = Token(buf, tokenStartPos, Token::Type::CharacterString);
  } else {
    // not properly closed
    currentToken = Token(buf, tokenStartPos, Token::Type::NaT);
  }
}

void Scanner::tryNumberString(const Position &tokenStartPos) {
  std::string buf;
  buf.push_back(reader_->get());

  while (std::isdigit(reader_->peek())) { buf.push_back(reader_->get()); }

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
  buf.push_back(reader_->get());
  auto firstSymbolType = Token::findSymbolType(buf.front());
  if (firstSymbolType != Token::Type::NaT) {
    auto testForTwoSymbol =
        Token::checkSecondSecond(buf.front(), reader_->peek());
    if (testForTwoSymbol != Token::Type::NaT) {
      // consume
      buf.push_back(reader_->get());
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
  while (!reader_->isEoF()
         && (std::isalnum(reader_->peek()) || reader_->peek() == '_')) {
    buf.push_back(reader_->get());
  }

  auto tokType = Token::findKeywordType(buf);

  if (tokType != Token::Type::NaT) {
    currentToken = Token(buf, tokenStartPos, tokType);
  } else {
    currentToken = Token(buf, tokenStartPos, Token::Type::Identifier);
  }
}