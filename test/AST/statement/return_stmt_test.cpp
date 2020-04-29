//
// Created by przemek on 01.04.2020.
//
#include <AST/expression/base_math_expr.h>
#include <AST/statement/return_stmt.h>
#include <boost/test/unit_test.hpp>

using namespace vecc;
using namespace vecc::ast;

BOOST_AUTO_TEST_SUITE(AST_Test_Suite)

BOOST_AUTO_TEST_SUITE(Return_Stmt_Test_Suite)

BOOST_AUTO_TEST_CASE(ReturnNothing) {
  ReturnStatement ret;

  BOOST_CHECK_EQUAL(true,
                    static_cast<bool>(ret.run().type_ == Return::Type::Noting));
}

BOOST_AUTO_TEST_CASE(ReturnValue) {
  Variable var = Variable({5, 2, 1});
  ReturnStatement ret(std::make_unique<BaseMathExpr>(var));

  BOOST_REQUIRE_EQUAL(
      true, static_cast<bool>(ret.run().type_ == Return::Type::Value));
  BOOST_CHECK_EQUAL(true, static_cast<bool>(ret.run().variable_ == var));
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()