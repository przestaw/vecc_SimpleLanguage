//
// Created by przemek on 02.04.2020.
//

#include <boost/test/unit_test.hpp>
#include <parser/parser.h>
#include <vecc_include.h>

using namespace vecc;
using namespace vecc::error;
using namespace vecc::ast;

BOOST_AUTO_TEST_SUITE(Language_Test_Suite)

BOOST_AUTO_TEST_CASE(VeccLibrary_NoThrow) {
  std::stringstream stream;
  stream << libraries::veccLibrary;
  Parser parser = Parser(std::make_unique<Reader>(stream));

  std::unique_ptr<Program> program;
  BOOST_CHECK_NO_THROW(parser.parse());
  BOOST_CHECK_NO_THROW(program = parser.getProgram());
}

BOOST_AUTO_TEST_CASE(VeccLibraryTestProduct2_Works_1) {
  std::stringstream stream;
  stream << libraries::veccLibrary;
  stream << "fun main(){"
            "  return product2(vec(1,2),vec(2,1));"
            "}";

  Parser parser = Parser(std::make_unique<Reader>(stream));

  std::unique_ptr<Program> program;
  BOOST_REQUIRE_NO_THROW(parser.parse());
  BOOST_REQUIRE_NO_THROW(program = parser.getProgram());

  BOOST_CHECK_EQUAL(
      true, static_cast<bool>(program->run().variable_ == Variable({0, 5})));
}

BOOST_AUTO_TEST_CASE(VeccLibraryTestProduct2_Works_2) {
  std::stringstream stream;
  stream << libraries::veccLibrary;
  stream << "fun main(){"
            "  return product2(vec(1,2),vec(3,4));"
            "}";

  Parser parser = Parser(std::make_unique<Reader>(stream));

  std::unique_ptr<Program> program;
  BOOST_REQUIRE_NO_THROW(parser.parse());
  BOOST_REQUIRE_NO_THROW(program = parser.getProgram());

  BOOST_CHECK_EQUAL(
      true, static_cast<bool>(program->run().variable_ == Variable({-5, 10})));
}

BOOST_AUTO_TEST_CASE(VeccLibraryTestProduct3_Works_1) {
  std::stringstream stream;
  stream << libraries::veccLibrary;
  stream << "fun main(){"
            "  return product3(vec(1,2,3),vec(1,2,3));"
            "}";

  Parser parser = Parser(std::make_unique<Reader>(stream));

  std::unique_ptr<Program> program;
  BOOST_REQUIRE_NO_THROW(parser.parse());
  BOOST_REQUIRE_NO_THROW(program = parser.getProgram());

  BOOST_CHECK_EQUAL(
      true, static_cast<bool>(program->run().variable_ == Variable({0, 0, 0})));
}

BOOST_AUTO_TEST_CASE(VeccLibraryTestProduct3_Works_2) {
  std::stringstream stream;
  stream << libraries::veccLibrary;
  stream << "fun main(){"
            "  return product3(vec(1,2,3),vec(3,4,5));"
            "}";

  Parser parser = Parser(std::make_unique<Reader>(stream));

  std::unique_ptr<Program> program;
  BOOST_REQUIRE_NO_THROW(parser.parse());
  BOOST_REQUIRE_NO_THROW(program = parser.getProgram());

  BOOST_CHECK_EQUAL(true, static_cast<bool>(program->run().variable_
                                            == Variable({-2, 4, -2})));
}

BOOST_AUTO_TEST_CASE(VeccLibraryTestProduct3_Works_3) {
  std::stringstream stream;
  stream << libraries::veccLibrary;
  stream << "fun main(){"
            "  return product3(vec(1,2,3),vec(0,0,0));"
            "}";

  Parser parser = Parser(std::make_unique<Reader>(stream));

  std::unique_ptr<Program> program;
  BOOST_REQUIRE_NO_THROW(parser.parse());
  BOOST_REQUIRE_NO_THROW(program = parser.getProgram());

  BOOST_CHECK_EQUAL(
      true, static_cast<bool>(program->run().variable_ == Variable({0, 0, 0})));
}

BOOST_AUTO_TEST_CASE(FibLibrary_NoThrow) {
  std::stringstream stream;
  stream << libraries::fibLibrary;
  Parser parser = Parser(std::make_unique<Reader>(stream));

  std::unique_ptr<Program> program;
  BOOST_CHECK_NO_THROW(parser.parse());
  BOOST_CHECK_NO_THROW(program = parser.getProgram());
}

BOOST_AUTO_TEST_CASE(FibLibraryTestIt_Works_1) {
  std::stringstream stream;
  stream << libraries::fibLibrary;
  stream << "fun main(){"
            "  return fib_it(10);"
            "}";

  Parser parser = Parser(std::make_unique<Reader>(stream));

  std::unique_ptr<Program> program;
  BOOST_REQUIRE_NO_THROW(parser.parse());
  BOOST_REQUIRE_NO_THROW(program = parser.getProgram());

  BOOST_CHECK_EQUAL(
      true, static_cast<bool>(program->run().variable_ == Variable({89})));
}

BOOST_AUTO_TEST_CASE(FibLibraryTestIt_Works_2) {
  std::stringstream stream;
  stream << libraries::fibLibrary;
  stream << "fun main(){"
            "  return fib_it(20);"
            "}";

  Parser parser = Parser(std::make_unique<Reader>(stream));

  std::unique_ptr<Program> program;
  BOOST_REQUIRE_NO_THROW(parser.parse());
  BOOST_REQUIRE_NO_THROW(program = parser.getProgram());

  BOOST_CHECK_EQUAL(
      true, static_cast<bool>(program->run().variable_ == Variable({10946})));
}

BOOST_AUTO_TEST_CASE(FibLibraryTestRec_Works_1) {
  std::stringstream stream;
  stream << libraries::fibLibrary;
  stream << "fun main(){"
            "  return fib_rec(10);"
            "}";

  Parser parser = Parser(std::make_unique<Reader>(stream));

  std::unique_ptr<Program> program;
  BOOST_REQUIRE_NO_THROW(parser.parse());
  BOOST_REQUIRE_NO_THROW(program = parser.getProgram());

  BOOST_CHECK_EQUAL(
      true, static_cast<bool>(program->run().variable_ == Variable({89})));
}

BOOST_AUTO_TEST_CASE(FibLibraryTestRec_Works_2) {
  std::stringstream stream;
  stream << libraries::fibLibrary;
  stream << "fun main(){"
            "  return fib_rec(20);"
            "}";

  Parser parser = Parser(std::make_unique<Reader>(stream));

  std::unique_ptr<Program> program;
  BOOST_REQUIRE_NO_THROW(parser.parse());
  BOOST_REQUIRE_NO_THROW(program = parser.getProgram());

  BOOST_CHECK_EQUAL(
      true, static_cast<bool>(program->run().variable_ == Variable({10946})));
}

BOOST_AUTO_TEST_SUITE_END()