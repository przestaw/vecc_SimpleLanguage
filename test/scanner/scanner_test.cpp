//
// Created by przemek on 13.03.2020.
//

#include <boost/test/unit_test.hpp>

#include "scanner/scanner.h"
#include "error/exeception.h"

BOOST_AUTO_TEST_SUITE(Lexer_Test_Suite)

    BOOST_AUTO_TEST_CASE(ScannerWithoutReader_Throws1) {
        vecc::Scanner scanner;
        BOOST_CHECK_THROW(scanner.parseToken(), vecc::NoInputStream);
    }

    BOOST_AUTO_TEST_CASE(ScannerWithoutReader_Throws2) {
        std::stringstream stream;

        vecc::Scanner scanner(std::make_unique<vecc::Reader>(stream));
        scanner.setReader(nullptr);
        BOOST_CHECK_THROW(scanner.parseToken(), vecc::NoInputStream);
    }

    BOOST_AUTO_TEST_CASE(ScannerWithReader_GivenEmptyReturnEoF) {
        std::stringstream stream("");

        vecc::Scanner scanner(std::make_unique<vecc::Reader>(stream));
        BOOST_CHECK_NO_THROW(scanner.parseToken());
        BOOST_CHECK(scanner.getToken().getType() == vecc::Token::Type::EoF);
    }

    BOOST_AUTO_TEST_CASE(ScannerWithReader_GivenSpacesReturnEoF) {
        std::stringstream stream("  \t");

        vecc::Scanner scanner(std::make_unique<vecc::Reader>(stream));
        BOOST_CHECK_NO_THROW(scanner.parseToken());
        BOOST_CHECK(scanner.getToken().getType() == vecc::Token::Type::EoF);
    }

    BOOST_AUTO_TEST_CASE(ScannerWithReader_GivenEmptyMultilineReturnEoF1) {
        std::stringstream stream("  \n  \r \t");

        vecc::Scanner scanner(std::make_unique<vecc::Reader>(stream));
        BOOST_CHECK_NO_THROW(scanner.parseToken());
        BOOST_CHECK(scanner.getToken().getType() == vecc::Token::Type::EoF);
    }

    BOOST_AUTO_TEST_CASE(ScannerWithReader_GivenEmptyMultilineReturnEoF2) {
        std::stringstream stream("  \n\r  \t\r\r ");

        vecc::Scanner scanner(std::make_unique<vecc::Reader>(stream));
        BOOST_CHECK_NO_THROW(scanner.parseToken());
        BOOST_CHECK(scanner.getToken().getType() == vecc::Token::Type::EoF);
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
        vecc::Scanner scanner(std::make_unique<vecc::Reader>(istream));
        BOOST_CHECK_NO_THROW(scanner.parseToken());
        BOOST_CHECK(scanner.getToken().getType() == vecc::Token::Type::ParenthesisOpen);
        BOOST_CHECK_NO_THROW(scanner.parseToken());
        BOOST_CHECK(scanner.getToken().getType() == vecc::Token::Type::ParenthesisClose);
        BOOST_CHECK_NO_THROW(scanner.parseToken());
        BOOST_CHECK(scanner.getToken().getType() == vecc::Token::Type::BracketOpen);
        BOOST_CHECK_NO_THROW(scanner.parseToken());
        BOOST_CHECK(scanner.getToken().getType() == vecc::Token::Type::BracketClose);
        BOOST_CHECK_NO_THROW(scanner.parseToken());
        BOOST_CHECK(scanner.getToken().getType() == vecc::Token::Type::CurlyBracketOpen);
        BOOST_CHECK_NO_THROW(scanner.parseToken());
        BOOST_CHECK(scanner.getToken().getType() == vecc::Token::Type::CurlyBracketClose);
        BOOST_CHECK_NO_THROW(scanner.parseToken());
        BOOST_CHECK(scanner.getToken().getType() == vecc::Token::Type::Comma);
        BOOST_CHECK_NO_THROW(scanner.parseToken());
        BOOST_CHECK(scanner.getToken().getType() == vecc::Token::Type::Assignment);
        BOOST_CHECK_NO_THROW(scanner.parseToken());
        BOOST_CHECK(scanner.getToken().getType() == vecc::Token::Type::Semicolon);
        BOOST_CHECK_NO_THROW(scanner.parseToken());
        BOOST_CHECK(scanner.getToken().getType() == vecc::Token::Type::Negation);
        BOOST_CHECK_NO_THROW(scanner.parseToken());
        BOOST_CHECK(scanner.getToken().getType() == vecc::Token::Type::EoF);
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
        vecc::Scanner scanner(std::make_unique<vecc::Reader>(istream));
        BOOST_CHECK_NO_THROW(scanner.parseToken());
        BOOST_CHECK(scanner.getToken().getType() == vecc::Token::Type::Equality);
        BOOST_CHECK_NO_THROW(scanner.parseToken());
        BOOST_CHECK(scanner.getToken().getType() == vecc::Token::Type::Inequality);
        BOOST_CHECK_NO_THROW(scanner.parseToken());
        BOOST_CHECK(scanner.getToken().getType() == vecc::Token::Type::Less);
        BOOST_CHECK_NO_THROW(scanner.parseToken());
        BOOST_CHECK(scanner.getToken().getType() == vecc::Token::Type::Greater);
        BOOST_CHECK_NO_THROW(scanner.parseToken());
        BOOST_CHECK(scanner.getToken().getType() == vecc::Token::Type::LessOrEqual);
        BOOST_CHECK_NO_THROW(scanner.parseToken());
        BOOST_CHECK(scanner.getToken().getType() == vecc::Token::Type::GreaterOrEqual);
        BOOST_CHECK_NO_THROW(scanner.parseToken());
        BOOST_CHECK(scanner.getToken().getType() == vecc::Token::Type::Plus);
        BOOST_CHECK_NO_THROW(scanner.parseToken());
        BOOST_CHECK(scanner.getToken().getType() == vecc::Token::Type::Minus);
        BOOST_CHECK_NO_THROW(scanner.parseToken());
        BOOST_CHECK(scanner.getToken().getType() == vecc::Token::Type::Multiply);
        BOOST_CHECK_NO_THROW(scanner.parseToken());
        BOOST_CHECK(scanner.getToken().getType() == vecc::Token::Type::Divide);
        BOOST_CHECK_NO_THROW(scanner.parseToken());
        BOOST_CHECK(scanner.getToken().getType() == vecc::Token::Type::Modulo);
        BOOST_CHECK_NO_THROW(scanner.parseToken());
        BOOST_CHECK(scanner.getToken().getType() == vecc::Token::Type::EoF);
    }

    BOOST_AUTO_TEST_CASE(ScannerGivenCharacterString_ReturnsToken) {
        std::string value = "Alan ma Koticzke 123456 @";

        std::istringstream istream("\"" + value + "\"");
        vecc::Scanner scanner(std::make_unique<vecc::Reader>(istream));
        BOOST_CHECK_NO_THROW(scanner.parseToken());
        BOOST_CHECK(scanner.getToken().getType() == vecc::Token::Type::CharacterString);
        BOOST_CHECK_EQUAL(scanner.getToken().getLiteral(), value);
    }

    BOOST_AUTO_TEST_CASE(ScannerGivenCharacterStringWithNewline_ReturnsToken) {
        std::string value = "Alan \t ma \rKoticzke\n 123456 \t@\n";

        std::istringstream istream("\"" + value + "\"");
        vecc::Scanner scanner(std::make_unique<vecc::Reader>(istream));
        BOOST_CHECK_NO_THROW(scanner.parseToken());
        BOOST_CHECK(scanner.getToken().getType() == vecc::Token::Type::CharacterString);
        BOOST_CHECK_EQUAL(scanner.getToken().getLiteral(), value);
    }

    BOOST_AUTO_TEST_CASE(ScannerGivenInvalidCharacterString_Throws) {
        std::string value = "Alan ma Koticzke 123456 @";

        std::istringstream istream("\"" + value);
        vecc::Scanner scanner(std::make_unique<vecc::Reader>(istream));
        BOOST_CHECK_THROW(scanner.parseToken(), vecc::NotAToken);
        BOOST_CHECK(scanner.getToken().getType() == vecc::Token::Type::NaT);
    }

    BOOST_AUTO_TEST_CASE(ScannerGivenNotDefined_Throws) {
        std::string value = "@|&$#";

        std::istringstream istream(value);
        vecc::Scanner scanner(std::make_unique<vecc::Reader>(istream));
        for (auto &it : value) {
            BOOST_CHECK_THROW(scanner.parseToken(), vecc::NotAToken);
            BOOST_CHECK(scanner.getToken().getType() == vecc::Token::Type::NaT);
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
        vecc::Scanner scanner(std::make_unique<vecc::Reader>(istream));

        BOOST_CHECK_NO_THROW(scanner.parseToken());
        BOOST_CHECK(scanner.getToken().getType() == vecc::Token::Type::Function);
        BOOST_CHECK_NO_THROW(scanner.parseToken());
        BOOST_CHECK(scanner.getToken().getType() == vecc::Token::Type::If);
        BOOST_CHECK_NO_THROW(scanner.parseToken());
        BOOST_CHECK(scanner.getToken().getType() == vecc::Token::Type::While);
        BOOST_CHECK_NO_THROW(scanner.parseToken());
        BOOST_CHECK(scanner.getToken().getType() == vecc::Token::Type::Else);
        BOOST_CHECK_NO_THROW(scanner.parseToken());
        BOOST_CHECK(scanner.getToken().getType() == vecc::Token::Type::Return);
        BOOST_CHECK_NO_THROW(scanner.parseToken());
        BOOST_CHECK(scanner.getToken().getType() == vecc::Token::Type::Var);
        BOOST_CHECK_NO_THROW(scanner.parseToken());
        BOOST_CHECK(scanner.getToken().getType() == vecc::Token::Type::Vec);
        BOOST_CHECK_NO_THROW(scanner.parseToken());
        BOOST_CHECK(scanner.getToken().getType() == vecc::Token::Type::Print);
        BOOST_CHECK_NO_THROW(scanner.parseToken());
        BOOST_CHECK(scanner.getToken().getType() == vecc::Token::Type::EoF);
    }

    BOOST_AUTO_TEST_CASE(ScannerGivenWords_ReturnsIdentifierTokens) {
        std::string streamValue = "Julka "
                                  "kto_tam "
                                  "koLanEczko "
                                  "Rzecka__ ";

        std::istringstream istream(streamValue);
        vecc::Scanner scanner(std::make_unique<vecc::Reader>(istream));

        BOOST_CHECK_NO_THROW(scanner.parseToken());
        BOOST_CHECK(scanner.getToken().getType() == vecc::Token::Type::Identifier);
        BOOST_CHECK_NO_THROW(scanner.parseToken());
        BOOST_CHECK(scanner.getToken().getType() == vecc::Token::Type::Identifier);
        BOOST_CHECK_NO_THROW(scanner.parseToken());
        BOOST_CHECK(scanner.getToken().getType() == vecc::Token::Type::Identifier);
        BOOST_CHECK_NO_THROW(scanner.parseToken());
        BOOST_CHECK(scanner.getToken().getType() == vecc::Token::Type::Identifier);
        BOOST_CHECK_NO_THROW(scanner.parseToken());
        BOOST_CHECK(scanner.getToken().getType() == vecc::Token::Type::EoF);
    }

    BOOST_AUTO_TEST_CASE(ScannerGivenNumbers_ReturnsNumbersTokens) {
        std::string streamValue = "1 "
                                  "123456 "
                                  "009876543 "
                                  "32632462346 ";

        std::istringstream istream(streamValue);
        vecc::Scanner scanner(std::make_unique<vecc::Reader>(istream));

        BOOST_CHECK_NO_THROW(scanner.parseToken());
        BOOST_CHECK(scanner.getToken().getType() == vecc::Token::Type::NumberString);
        BOOST_CHECK_NO_THROW(scanner.parseToken());
        BOOST_CHECK(scanner.getToken().getType() == vecc::Token::Type::NumberString);
        BOOST_CHECK_NO_THROW(scanner.parseToken());
        BOOST_CHECK(scanner.getToken().getType() == vecc::Token::Type::NumberString);
        BOOST_CHECK_NO_THROW(scanner.parseToken());
        BOOST_CHECK(scanner.getToken().getType() == vecc::Token::Type::NumberString);
        BOOST_CHECK_NO_THROW(scanner.parseToken());
        BOOST_CHECK(scanner.getToken().getType() == vecc::Token::Type::EoF);
    }

    BOOST_AUTO_TEST_CASE(ScannerGivenNumbers_ReturnsTokens) {
        std::string streamValue = "(1,"
                                  "123456, "
                                  "009876543 , "
                                  "32632462346)";

        std::istringstream istream(streamValue);
        vecc::Scanner scanner(std::make_unique<vecc::Reader>(istream));

        BOOST_CHECK_NO_THROW(scanner.parseToken());
        BOOST_CHECK(scanner.getToken().getType() == vecc::Token::Type::ParenthesisOpen);
        BOOST_CHECK_NO_THROW(scanner.parseToken());
        BOOST_CHECK(scanner.getToken().getType() == vecc::Token::Type::NumberString);
        BOOST_CHECK_NO_THROW(scanner.parseToken());
        BOOST_CHECK(scanner.getToken().getType() == vecc::Token::Type::Comma);
        BOOST_CHECK_NO_THROW(scanner.parseToken());
        BOOST_CHECK(scanner.getToken().getType() == vecc::Token::Type::NumberString);
        BOOST_CHECK_NO_THROW(scanner.parseToken());
        BOOST_CHECK(scanner.getToken().getType() == vecc::Token::Type::Comma);
        BOOST_CHECK_NO_THROW(scanner.parseToken());
        BOOST_CHECK(scanner.getToken().getType() == vecc::Token::Type::NumberString);
        BOOST_CHECK_NO_THROW(scanner.parseToken());
        BOOST_CHECK(scanner.getToken().getType() == vecc::Token::Type::Comma);
        BOOST_CHECK_NO_THROW(scanner.parseToken());
        BOOST_CHECK(scanner.getToken().getType() == vecc::Token::Type::NumberString);
        BOOST_CHECK_NO_THROW(scanner.parseToken());
        BOOST_CHECK(scanner.getToken().getType() == vecc::Token::Type::ParenthesisClose);
        BOOST_CHECK_NO_THROW(scanner.parseToken());
        BOOST_CHECK(scanner.getToken().getType() == vecc::Token::Type::EoF);
    }

    BOOST_AUTO_TEST_CASE(ScannerGivenKeywords_ReturnsTokens2) {
        std::string streamValue = "if "
                                  "while (condition){}"
                                  "else\n"
                                  "return\n"
                                  "KalOsz";

        std::istringstream istream(streamValue);
        vecc::Scanner scanner(std::make_unique<vecc::Reader>(istream));

        BOOST_CHECK_NO_THROW(scanner.parseToken());
        BOOST_CHECK(scanner.getToken().getType() == vecc::Token::Type::If);
        BOOST_CHECK_NO_THROW(scanner.parseToken());
        BOOST_CHECK(scanner.getToken().getType() == vecc::Token::Type::While);
        BOOST_CHECK_NO_THROW(scanner.parseToken());
        BOOST_CHECK(scanner.getToken().getType() == vecc::Token::Type::ParenthesisOpen);
        BOOST_CHECK_NO_THROW(scanner.parseToken());
        BOOST_CHECK(scanner.getToken().getType() == vecc::Token::Type::Identifier);
        BOOST_CHECK_NO_THROW(scanner.parseToken());
        BOOST_CHECK(scanner.getToken().getType() == vecc::Token::Type::ParenthesisClose);
        BOOST_CHECK_NO_THROW(scanner.parseToken());
        BOOST_CHECK(scanner.getToken().getType() == vecc::Token::Type::CurlyBracketOpen);
        BOOST_CHECK_NO_THROW(scanner.parseToken());
        BOOST_CHECK(scanner.getToken().getType() == vecc::Token::Type::CurlyBracketClose);
        BOOST_CHECK_NO_THROW(scanner.parseToken());
        BOOST_CHECK(scanner.getToken().getType() == vecc::Token::Type::Else);
        BOOST_CHECK_NO_THROW(scanner.parseToken());
        BOOST_CHECK(scanner.getToken().getType() == vecc::Token::Type::Return);
        BOOST_CHECK_NO_THROW(scanner.parseToken());
        BOOST_CHECK(scanner.getToken().getType() == vecc::Token::Type::Identifier);
        BOOST_CHECK_NO_THROW(scanner.parseToken());
        BOOST_CHECK(scanner.getToken().getType() == vecc::Token::Type::EoF);
    }

BOOST_AUTO_TEST_SUITE_END()