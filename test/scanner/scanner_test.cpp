//
// Created by przemek on 13.03.2020.
//

#include <boost/test/unit_test.hpp>

#include "error/exeception.h"
#include "scanner/scanner.h"

using namespace vecc;
using namespace vecc::error;

BOOST_AUTO_TEST_SUITE(Lexer_Test_Suite)

BOOST_AUTO_TEST_CASE(ScannerWithoutReader_Throws2) {
  std::stringstream stream;

  Scanner scanner(std::make_unique<Reader>(stream));
  scanner.setReader(nullptr);
  BOOST_CHECK_THROW(scanner.parseToken(), NoInputStream);
}

BOOST_AUTO_TEST_CASE(ScannerWithReader_GivenEmptyReturnEoF) {
  std::stringstream stream("");

  Scanner scanner(std::make_unique<Reader>(stream));
  scanner.parseToken();
  BOOST_CHECK(scanner.getToken().getType() == Token::Type::EoF);
}

BOOST_AUTO_TEST_CASE(ScannerWithReader_GivenSpacesReturnEoF) {
  std::stringstream stream("  \t");

  Scanner scanner(std::make_unique<Reader>(stream));
  scanner.parseToken();
  BOOST_CHECK(scanner.getToken().getType() == Token::Type::EoF);
}

BOOST_AUTO_TEST_CASE(ScannerWithReader_GivenEmptyMultilineReturnEoF1) {
  std::stringstream stream("  \n  \r \t");

  Scanner scanner(std::make_unique<Reader>(stream));
  scanner.parseToken();
  BOOST_CHECK(scanner.getToken().getType() == Token::Type::EoF);
}

BOOST_AUTO_TEST_CASE(ScannerWithReader_GivenEmptyMultilineReturnEoF2) {
  std::stringstream stream("  \n\r  \t\r\r ");

  Scanner scanner(std::make_unique<Reader>(stream));
  scanner.parseToken();
  BOOST_CHECK(scanner.getToken().getType() == Token::Type::EoF);
}

BOOST_AUTO_TEST_CASE(ScannerGivenSpecialCharacterString_ReturnsTokens1) {
  std::string streamValue = "( "
                            ") "
                            "[ "
                            "] "
                            "{ "
                            "} "
                            ", "
                            "= "
                            "; "
                            "! ";

  std::istringstream istream(streamValue);
  Scanner scanner(std::make_unique<Reader>(istream));
  scanner.parseToken();
  BOOST_CHECK(scanner.getToken().getType() == Token::Type::ParenthesisOpen);
  scanner.parseToken();
  BOOST_CHECK(scanner.getToken().getType() == Token::Type::ParenthesisClose);
  scanner.parseToken();
  BOOST_CHECK(scanner.getToken().getType() == Token::Type::BracketOpen);
  scanner.parseToken();
  BOOST_CHECK(scanner.getToken().getType() == Token::Type::BracketClose);
  scanner.parseToken();
  BOOST_CHECK(scanner.getToken().getType() == Token::Type::CurlyBracketOpen);
  scanner.parseToken();
  BOOST_CHECK(scanner.getToken().getType() == Token::Type::CurlyBracketClose);
  scanner.parseToken();
  BOOST_CHECK(scanner.getToken().getType() == Token::Type::Comma);
  scanner.parseToken();
  BOOST_CHECK(scanner.getToken().getType() == Token::Type::Assignment);
  scanner.parseToken();
  BOOST_CHECK(scanner.getToken().getType() == Token::Type::Semicolon);
  scanner.parseToken();
  BOOST_CHECK(scanner.getToken().getType() == Token::Type::Negation);
  scanner.parseToken();
  BOOST_CHECK(scanner.getToken().getType() == Token::Type::EoF);
}

BOOST_AUTO_TEST_CASE(ScannerGivenSpecialCharacterString_ReturnsTokens2) {
  std::string streamValue = "== "
                            "!= "
                            "< "
                            "> "
                            "<= "
                            ">= "
                            "+ "
                            "- "
                            "* "
                            "/ "
                            "% ";

  std::istringstream istream(streamValue);
  Scanner scanner(std::make_unique<Reader>(istream));
  scanner.parseToken();
  BOOST_CHECK(scanner.getToken().getType() == Token::Type::Equality);
  scanner.parseToken();
  BOOST_CHECK(scanner.getToken().getType() == Token::Type::Inequality);
  scanner.parseToken();
  BOOST_CHECK(scanner.getToken().getType() == Token::Type::Less);
  scanner.parseToken();
  BOOST_CHECK(scanner.getToken().getType() == Token::Type::Greater);
  scanner.parseToken();
  BOOST_CHECK(scanner.getToken().getType() == Token::Type::LessOrEqual);
  scanner.parseToken();
  BOOST_CHECK(scanner.getToken().getType() == Token::Type::GreaterOrEqual);
  scanner.parseToken();
  BOOST_CHECK(scanner.getToken().getType() == Token::Type::Plus);
  scanner.parseToken();
  BOOST_CHECK(scanner.getToken().getType() == Token::Type::Minus);
  scanner.parseToken();
  BOOST_CHECK(scanner.getToken().getType() == Token::Type::Multiply);
  scanner.parseToken();
  BOOST_CHECK(scanner.getToken().getType() == Token::Type::Divide);
  scanner.parseToken();
  BOOST_CHECK(scanner.getToken().getType() == Token::Type::Modulo);
  scanner.parseToken();
  BOOST_CHECK(scanner.getToken().getType() == Token::Type::EoF);
}

BOOST_AUTO_TEST_CASE(ScannerGivenCharacterString_ReturnsToken) {
  std::string value = "Alan ma Koticzke 123456 @";

  std::istringstream istream("\"" + value + "\"");
  Scanner scanner(std::make_unique<Reader>(istream));
  scanner.parseToken();
  BOOST_CHECK(scanner.getToken().getType() == Token::Type::CharacterString);
  BOOST_CHECK_EQUAL(scanner.getToken().getLiteral(), value);
}

BOOST_AUTO_TEST_CASE(ScannerGivenCharacterStringWithNewline_ReturnsToken) {
  std::string value = "Alan \t ma \rKoticzke\n 123456 \t@\n";

  std::istringstream istream("\"" + value + "\"");
  Scanner scanner(std::make_unique<Reader>(istream));
  scanner.parseToken();
  BOOST_CHECK(scanner.getToken().getType() == Token::Type::CharacterString);
  BOOST_CHECK_EQUAL(scanner.getToken().getLiteral(), value);
}

BOOST_AUTO_TEST_CASE(ScannerGivenInvalidCharacterString_Throws) {
  std::string value = "Alan ma Koticzke 123456 @";

  std::istringstream istream("\"" + value);
  Scanner scanner(std::make_unique<Reader>(istream));
  BOOST_CHECK_THROW(scanner.parseToken(), NotAToken);
  BOOST_CHECK(scanner.getToken().getType() == Token::Type::NaT);
}

BOOST_AUTO_TEST_CASE(ScannerGivenNotDefined_Throws) {
  std::string value = "@|&$#";

  std::istringstream istream(value);
  Scanner scanner(std::make_unique<Reader>(istream));
  for (auto &it : value) {
    BOOST_CHECK_THROW(scanner.parseToken(), NotAToken);
    BOOST_CHECK(scanner.getToken().getType() == Token::Type::NaT);
    std::string check(1, it);
    BOOST_CHECK_EQUAL(scanner.getToken().getLiteral(), check);
  }
}

BOOST_AUTO_TEST_CASE(ScannerGivenKeywords_ReturnsTokens1) {
  std::string streamValue = "fun "
                            "if "
                            "while "
                            "else "
                            "return "
                            "var "
                            "vec "
                            "print ";

  std::istringstream istream(streamValue);
  Scanner scanner(std::make_unique<Reader>(istream));

  scanner.parseToken();
  BOOST_CHECK(scanner.getToken().getType() == Token::Type::Function);
  scanner.parseToken();
  BOOST_CHECK(scanner.getToken().getType() == Token::Type::If);
  scanner.parseToken();
  BOOST_CHECK(scanner.getToken().getType() == Token::Type::While);
  scanner.parseToken();
  BOOST_CHECK(scanner.getToken().getType() == Token::Type::Else);
  scanner.parseToken();
  BOOST_CHECK(scanner.getToken().getType() == Token::Type::Return);
  scanner.parseToken();
  BOOST_CHECK(scanner.getToken().getType() == Token::Type::Var);
  scanner.parseToken();
  BOOST_CHECK(scanner.getToken().getType() == Token::Type::Vec);
  scanner.parseToken();
  BOOST_CHECK(scanner.getToken().getType() == Token::Type::Print);
  scanner.parseToken();
  BOOST_CHECK(scanner.getToken().getType() == Token::Type::EoF);
}

BOOST_AUTO_TEST_CASE(ScannerGivenWords_ReturnsIdentifierTokens) {
  std::string streamValue = "Julka "
                            "kto_tam "
                            "koLanEczko "
                            "Rzecka__ ";

  std::istringstream istream(streamValue);
  Scanner scanner(std::make_unique<Reader>(istream));

  scanner.parseToken();
  BOOST_CHECK(scanner.getToken().getType() == Token::Type::Identifier);
  scanner.parseToken();
  BOOST_CHECK(scanner.getToken().getType() == Token::Type::Identifier);
  scanner.parseToken();
  BOOST_CHECK(scanner.getToken().getType() == Token::Type::Identifier);
  scanner.parseToken();
  BOOST_CHECK(scanner.getToken().getType() == Token::Type::Identifier);
  scanner.parseToken();
  BOOST_CHECK(scanner.getToken().getType() == Token::Type::EoF);
}

BOOST_AUTO_TEST_CASE(ScannerGivenNumbers_ReturnsNumbersTokens) {
  std::string streamValue = "1 "
                            "123456 "
                            "009876543 "
                            "3263246 ";

  std::istringstream istream(streamValue);
  Scanner scanner(std::make_unique<Reader>(istream));

  scanner.parseToken();
  BOOST_CHECK(scanner.getToken().getType() == Token::Type::NumberString);
  scanner.parseToken();
  BOOST_CHECK(scanner.getToken().getType() == Token::Type::NumberString);
  scanner.parseToken();
  BOOST_CHECK(scanner.getToken().getType() == Token::Type::NumberString);
  scanner.parseToken();
  BOOST_CHECK(scanner.getToken().getType() == Token::Type::NumberString);
  scanner.parseToken();
  BOOST_CHECK(scanner.getToken().getType() == Token::Type::EoF);
}

  BOOST_AUTO_TEST_CASE(ScannerGivenLargeNumbers_Throws) {
    std::string streamValue = "10000000000000000 "
                              "9010203040506 ";

    std::istringstream istream(streamValue);
    Scanner scanner(std::make_unique<Reader>(istream));

    BOOST_CHECK_THROW(scanner.parseToken(), InvalidNumberLiteral);
    BOOST_CHECK_THROW(scanner.parseToken(), InvalidNumberLiteral);
    scanner.parseToken();
    BOOST_CHECK(scanner.getToken().getType() == Token::Type::EoF);
  }

BOOST_AUTO_TEST_CASE(ScannerGivenNumbers_ReturnsTokens) {
  std::string streamValue = "(1,"
                            "123456, "
                            "009876543 , "
                            "326346)";

  std::istringstream istream(streamValue);
  Scanner scanner(std::make_unique<Reader>(istream));

  scanner.parseToken();
  BOOST_CHECK(scanner.getToken().getType() == Token::Type::ParenthesisOpen);
  scanner.parseToken();
  BOOST_CHECK(scanner.getToken().getType() == Token::Type::NumberString);
  scanner.parseToken();
  BOOST_CHECK(scanner.getToken().getType() == Token::Type::Comma);
  scanner.parseToken();
  BOOST_CHECK(scanner.getToken().getType() == Token::Type::NumberString);
  scanner.parseToken();
  BOOST_CHECK(scanner.getToken().getType() == Token::Type::Comma);
  scanner.parseToken();
  BOOST_CHECK(scanner.getToken().getType() == Token::Type::NumberString);
  scanner.parseToken();
  BOOST_CHECK(scanner.getToken().getType() == Token::Type::Comma);
  scanner.parseToken();
  BOOST_CHECK(scanner.getToken().getType() == Token::Type::NumberString);
  scanner.parseToken();
  BOOST_CHECK(scanner.getToken().getType() == Token::Type::ParenthesisClose);
  scanner.parseToken();
  BOOST_CHECK(scanner.getToken().getType() == Token::Type::EoF);
}

BOOST_AUTO_TEST_CASE(ScannerGivenKeywords_ReturnsTokens2) {
  std::string streamValue = "if "
                            "while (condition){}"
                            "else\n"
                            "return\n"
                            "KalOsz";

  std::istringstream istream(streamValue);
  Scanner scanner(std::make_unique<Reader>(istream));

  scanner.parseToken();
  BOOST_CHECK(scanner.getToken().getType() == Token::Type::If);
  scanner.parseToken();
  BOOST_CHECK(scanner.getToken().getType() == Token::Type::While);
  scanner.parseToken();
  BOOST_CHECK(scanner.getToken().getType() == Token::Type::ParenthesisOpen);
  scanner.parseToken();
  BOOST_CHECK(scanner.getToken().getType() == Token::Type::Identifier);
  scanner.parseToken();
  BOOST_CHECK(scanner.getToken().getType() == Token::Type::ParenthesisClose);
  scanner.parseToken();
  BOOST_CHECK(scanner.getToken().getType() == Token::Type::CurlyBracketOpen);
  scanner.parseToken();
  BOOST_CHECK(scanner.getToken().getType() == Token::Type::CurlyBracketClose);
  scanner.parseToken();
  BOOST_CHECK(scanner.getToken().getType() == Token::Type::Else);
  scanner.parseToken();
  BOOST_CHECK(scanner.getToken().getType() == Token::Type::Return);
  scanner.parseToken();
  BOOST_CHECK(scanner.getToken().getType() == Token::Type::Identifier);
  scanner.parseToken();
  BOOST_CHECK(scanner.getToken().getType() == Token::Type::EoF);
}

BOOST_AUTO_TEST_SUITE_END()