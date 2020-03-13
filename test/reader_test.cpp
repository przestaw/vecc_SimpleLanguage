//
// Created by przemek on 13.03.2020.
//

#include <boost/test/unit_test.hpp>
#include "scanner/reader.h"

BOOST_AUTO_TEST_SUITE(Reader_Test_Suite)

    BOOST_AUTO_TEST_CASE(ReadMultiLine_UsingGet_1) {
        std::string example = "12345\n"
                              "abcde\n"
                              "3_6_9\n\r"
                              "qw(er)ty\n\r"
                              "1410\r\n"
                              "e-bazarek\r\n";
        std::stringstream input (example);
        vecc::Reader reader(input);
        for (auto &val : example){
            BOOST_CHECK_EQUAL(val, reader.get());
        }
        BOOST_CHECK_EQUAL(7, reader.getCurrentPos().lineNo);
    }

    BOOST_AUTO_TEST_CASE(ReadMultiLine_UsingPeek_1) {
        std::string example = "12345\n"
                              "abcde\n"
                              "3_6_9\n\r"
                              "qw(er)ty\n\r"
                              "1410\r\n"
                              "e-bazarek\r\n";
        std::stringstream input (example);
        vecc::Reader reader(input);
        for (auto &val : example){
            BOOST_CHECK_EQUAL(val, reader.peek());
            reader.get();
        }
        BOOST_CHECK_EQUAL(7, reader.getCurrentPos().lineNo);
    }


BOOST_AUTO_TEST_SUITE_END()