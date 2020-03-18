//
// Created by przemek on 13.03.2020.
//

#include <boost/test/unit_test.hpp>

#include "scanner/scanner.h"

BOOST_AUTO_TEST_SUITE(Lexer_Test_Suite)

    BOOST_AUTO_TEST_CASE(ScannerWithoutReader_Throws1) {
        vecc::Scanner scanner;
        //BOOST_CHECK_THROW(scanner.getToken());
    }

    BOOST_AUTO_TEST_CASE(ScannerWithoutReader_Throws2) {
        std::stringstream stream;

        vecc::Scanner scanner(std::make_unique<vecc::Reader>(stream));
        scanner.setReader(nullptr);
        //BOOST_CHECK_THROW(scanner.getToken());
    }

    BOOST_AUTO_TEST_CASE(ScannerWithReader_GivenEmptyReturnEoF) {
        std::stringstream stream("");

        vecc::Scanner scanner(std::make_unique<vecc::Reader>(stream));

        BOOST_CHECK(scanner.getToken().getType() == vecc::Token::Type::EoF);
    }

    BOOST_AUTO_TEST_CASE(ScannerWithReader_GivenSpacesReturnEoF) {
        std::stringstream stream("  \t");

        vecc::Scanner scanner(std::make_unique<vecc::Reader>(stream));

        BOOST_CHECK(scanner.getToken().getType() == vecc::Token::Type::EoF);
    }

    BOOST_AUTO_TEST_CASE(ScannerWithReader_GivenEmptyMultilineReturnEoF1) {
        std::stringstream stream("  \n  \r \t");

        vecc::Scanner scanner(std::make_unique<vecc::Reader>(stream));

        BOOST_CHECK(scanner.getToken().getType() == vecc::Token::Type::EoF);
    }

    BOOST_AUTO_TEST_CASE(ScannerWithReader_GivenEmptyMultilineReturnEoF2) {
        std::stringstream stream("  \n\r  \t\r\r ");

        vecc::Scanner scanner(std::make_unique<vecc::Reader>(stream));

        BOOST_CHECK(scanner.getToken().getType() == vecc::Token::Type::EoF);
    }

BOOST_AUTO_TEST_SUITE_END()