//
// Created by przemek on 28.05.2020.
//
#include <AST/statement/print_stmt.h>
#include <boost/test/unit_test.hpp>
#include <mock_expr.h>

using namespace vecc;
using namespace vecc::ast;
using namespace vecc::test;

BOOST_AUTO_TEST_SUITE(AST_Test_Suite)

BOOST_AUTO_TEST_SUITE(Print_Stmt_Test_Suite)

BOOST_AUTO_TEST_CASE(PrintValue_toStringWorks) {
  Variable var         = Variable({5, 2, 1});
  PrintStatement print = PrintStatement();
  print.addString("string");
  print.addExpression(std::make_unique<MockExpr>("stmt-1"));
  print.addString("kotek");
  print.addExpression(std::make_unique<MockExpr>("stmt-2"));
  print.addString("plotek");

  BOOST_CHECK_EQUAL(print.toString(),
                    "print(\"string\", stmt-1, \"kotek\", stmt-2, \"plotek\")");
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()