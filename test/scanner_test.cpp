//
// Created by przemek on 13.03.2020.
//

#include <boost/test/unit_test.hpp>

#include "scanner/scanner.h"

BOOST_AUTO_TEST_SUITE(Lexer_Test_Suite)

BOOST_AUTO_TEST_CASE(Dummy_Test) {

        BOOST_CHECK_EQUAL(12, 12);
        BOOST_CHECK(297 == (3*99));
        BOOST_CHECK_NE(10, 20);
}

BOOST_AUTO_TEST_SUITE_END()