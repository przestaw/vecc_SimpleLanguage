//
// Created by przemek on 23.03.2020.
//

#include <AST/expression/base_math_expr.h>
#include <boost/test/unit_test.hpp>

using namespace vecc;
using namespace vecc::ast;

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

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()