//
// Created by przemek on 13.03.2020.
//

#include "scanner/reader.h"
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(Reader_Test_Suite)

BOOST_AUTO_TEST_CASE(ReadMultiLine_UsingGet_1) {
  std::string example = "12345\n"
                        "abcde\n"
                        "3_6_9\n\r"
                        "qw(er)ty\n\r"
                        "1410\r\n"
                        "e-bazarek\r\n";
  std::stringstream input(example);
  vecc::Reader reader(input);
  for (auto &val : example) { BOOST_CHECK_EQUAL(val, reader.get()); }
  BOOST_CHECK(vecc::Position(7, 0) == reader.getCurrentPos());
}

BOOST_AUTO_TEST_CASE(ReadMultiLine_UsingPeek_1) {
  std::string example = "12345\n"
                        "abcde\n"
                        "3_6_9\n\r"
                        "qw(er)ty\n\r"
                        "1410\r\n"
                        "e-bazarek\r\n";
  std::stringstream input(example);
  vecc::Reader reader(input);
  for (auto &val : example) {
    BOOST_CHECK_EQUAL(val, reader.peek());
    reader.get();
  }
  BOOST_CHECK(vecc::Position(7, 0) == reader.getCurrentPos());
}

BOOST_AUTO_TEST_CASE(AfterReadMultiLine_EofIsEncountered) {
  std::string example = "12345\n"
                        "abcde\n"
                        "3_6_9\n\r"
                        "qw(er)ty\n\r"
                        "1410\r\n"
                        "e-bazarek\r\n";
  std::stringstream input(example);
  vecc::Reader reader(input);
  BOOST_CHECK(!reader.isEoF());
  for (auto &val : example) {
    reader.get();
    (void)val;
  }
  // try to read next
  reader.peek();
  BOOST_CHECK(reader.isEoF());
}

BOOST_AUTO_TEST_SUITE_END()