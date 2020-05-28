//
// Created by przemek on 23.03.2020.
//

#include <AST/expression/base_math_expr.h>
#include <boost/test/unit_test.hpp>
#include <mock_expr.h>
#include <mock_stmt.h>

using namespace vecc;
using namespace vecc::ast;
using namespace vecc::test;

BOOST_AUTO_TEST_SUITE(AST_Test_Suite)

BOOST_AUTO_TEST_SUITE(Base_Math_Expr_Test_Suite)

BOOST_AUTO_TEST_CASE(GivenConstatnt_ValueIsCorrect) {
  Variable constant({1, 2, 3});

  BaseMathExpr expr1(constant, false);
  BaseMathExpr expr2(constant, true);

  BOOST_CHECK_EQUAL(expr1.calculate(), Variable({1, 2, 3}));
  BOOST_CHECK_EQUAL(expr2.calculate(), Variable({-1, -2, -3}));
}

BOOST_AUTO_TEST_CASE(GivenVariable_ValueIsCorrect) {
  auto constant = Variable({1, 2, 3});

  BaseMathExpr expr1(constant, false);
  BaseMathExpr expr2(constant, true);

  BOOST_CHECK_EQUAL(expr1.calculate(), Variable({1, 2, 3}));
  BOOST_CHECK_EQUAL(expr2.calculate(), Variable({-1, -2, -3}));
}

BOOST_AUTO_TEST_CASE(GivenVariable_WhenVariableChangesValueIsCorrect) {
  auto variable = Variable({1, 2, 3});

  BaseMathExpr expr1(&variable, false);
  BaseMathExpr expr2(&variable, true);

  variable = variable + Variable({3, 2, 1});

  BOOST_CHECK_EQUAL(expr1.calculate(), Variable({4, 4, 4}));
  BOOST_CHECK_EQUAL(expr2.calculate(), Variable({-4, -4, -4}));
}

BOOST_AUTO_TEST_CASE(GivenVal_ToStringCorrect) {
  Variable var = Variable({1, 2});

  auto constant = Variable({1, 2, 3});

  BaseMathExpr expr1(constant, false);
  BaseMathExpr expr2(constant, true);

  BOOST_CHECK_EQUAL(expr1.toString(), "vec[1, 2, 3]");
  BOOST_CHECK_EQUAL(expr2.toString(), "(-vec[1, 2, 3])");
}

BOOST_AUTO_TEST_CASE(GivenVar_ToStringCorrect) {
  Variable var = Variable({1, 2});

  auto constant = Variable({1, 2, 3});

  constant.setName("kitku");

  BaseMathExpr expr1(&constant, false);
  BaseMathExpr expr2(&constant, true);

  BOOST_CHECK_EQUAL(expr1.toString(), "kitku");
  BOOST_CHECK_EQUAL(expr2.toString(), "(-kitku)");
}

BOOST_AUTO_TEST_CASE(GivenExpr_ToStringCorrect) {
  auto expr = MockExpr();
  BaseMathExpr expr1(std::make_unique<MockExpr>(MockExpr()), false);
  BaseMathExpr expr2(std::make_unique<MockExpr>(MockExpr()), true);

  BOOST_CHECK_EQUAL(expr1.toString(), expr.toString());
  BOOST_CHECK_EQUAL(expr2.toString(), "(-" + expr.toString() + ")");
}

BOOST_AUTO_TEST_CASE(GivenStmt_ToStringCorrect) {
  auto stmt = MockStmt();
  BaseMathExpr expr1(std::make_unique<MockStmt>(MockStmt()), false);
  BaseMathExpr expr2(std::make_unique<MockStmt>(MockStmt()), true);

  BOOST_CHECK_EQUAL(expr1.toString(), stmt.toString());
  BOOST_CHECK_EQUAL(expr2.toString(), "(-" + stmt.toString() + ")");
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()