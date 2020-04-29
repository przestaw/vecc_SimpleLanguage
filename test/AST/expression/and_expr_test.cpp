//
// Created by przemek on 27.03.2020.
//

#include <AST/expression/and_logic_expr.h>
#include <AST/expression/base_math_expr.h>
#include <boost/test/unit_test.hpp>
#include <error/exeception.h>

using namespace vecc;
using namespace vecc::ast;

using std::make_unique;
using std::move;
using std::unique_ptr;

BOOST_AUTO_TEST_SUITE(AST_Test_Suite)

BOOST_AUTO_TEST_SUITE(And_Logic_Expr_Test_Suite)

BOOST_AUTO_TEST_CASE(GivenMathExpr_ValueIsCorrect) {
  Variable var = Variable({1, 2, 3});

  AndLogicExpr expr(make_unique<BaseMathExpr>(var));

  BOOST_CHECK(static_cast<bool>(expr.calculate() == var));
}

BOOST_AUTO_TEST_CASE(GivenTrueAndFalse_ValueIsCorrect) {
  Variable trueVar  = Variable({1, 2, 3});
  Variable falseVar = Variable({0, 0});

  BOOST_REQUIRE_EQUAL(true, static_cast<bool>(trueVar));
  BOOST_REQUIRE_EQUAL(false, static_cast<bool>(falseVar));

  AndLogicExpr expr(make_unique<BaseMathExpr>(trueVar));
  expr.addOperand(make_unique<BaseMathExpr>(falseVar));

  BOOST_CHECK_EQUAL(false, static_cast<bool>(expr.calculate()));
}

BOOST_AUTO_TEST_CASE(GivenFalseAndFalse_ValueIsCorrect) {
  Variable falseVar1 = Variable({0, 0, 0});
  Variable falseVar2 = Variable({0, 0});

  BOOST_REQUIRE_EQUAL(false, static_cast<bool>(falseVar1));
  BOOST_REQUIRE_EQUAL(false, static_cast<bool>(falseVar2));

  AndLogicExpr expr(make_unique<BaseMathExpr>(falseVar1));
  expr.addOperand(make_unique<BaseMathExpr>(falseVar2));

  BOOST_CHECK_EQUAL(false, static_cast<bool>(expr.calculate()));
}

BOOST_AUTO_TEST_CASE(GivenTrueAndTrue_ValueIsCorrect) {
  Variable trueVar1 = Variable({1, 1, 0});
  Variable trueVar2 = Variable({1, 0});

  BOOST_REQUIRE_EQUAL(true, static_cast<bool>(trueVar1));
  BOOST_REQUIRE_EQUAL(true, static_cast<bool>(trueVar2));

  AndLogicExpr expr(make_unique<BaseMathExpr>(trueVar1));
  expr.addOperand(make_unique<BaseMathExpr>(trueVar2));

  BOOST_CHECK_EQUAL(true, static_cast<bool>(expr.calculate()));
}

BOOST_AUTO_TEST_CASE(GivenThreeVals_ValueIsCorrect_1) {
  Variable trueVar1  = Variable({5, 1, 0});
  Variable trueVar2  = Variable({1, -9});
  Variable falseVar1 = Variable({0, 0});

  BOOST_REQUIRE_EQUAL(true, static_cast<bool>(trueVar1));
  BOOST_REQUIRE_EQUAL(true, static_cast<bool>(trueVar2));
  BOOST_REQUIRE_EQUAL(false, static_cast<bool>(falseVar1));

  AndLogicExpr expr1(make_unique<BaseMathExpr>(trueVar1));
  expr1.addOperand(make_unique<BaseMathExpr>(trueVar2));
  expr1.addOperand(make_unique<BaseMathExpr>(falseVar1));

  AndLogicExpr expr2(make_unique<BaseMathExpr>(trueVar2));
  expr2.addOperand(make_unique<BaseMathExpr>(falseVar1));
  expr2.addOperand(make_unique<BaseMathExpr>(trueVar1));

  AndLogicExpr expr3(make_unique<BaseMathExpr>(falseVar1));
  expr3.addOperand(make_unique<BaseMathExpr>(trueVar2));
  expr3.addOperand(make_unique<BaseMathExpr>(trueVar1));

  BOOST_CHECK_EQUAL(false, static_cast<bool>(expr1.calculate()));
  BOOST_CHECK_EQUAL(false, static_cast<bool>(expr2.calculate()));
  BOOST_CHECK_EQUAL(false, static_cast<bool>(expr3.calculate()));
}

BOOST_AUTO_TEST_CASE(GivenThreeVals_ValueIsCorrect_2) {
  Variable trueVar1  = Variable({5, 1, 0});
  Variable falseVar1 = Variable({0, 0, 0});
  Variable falseVar2 = Variable({0, 0});

  BOOST_REQUIRE_EQUAL(true, static_cast<bool>(trueVar1));
  BOOST_REQUIRE_EQUAL(false, static_cast<bool>(falseVar1));
  BOOST_REQUIRE_EQUAL(false, static_cast<bool>(falseVar2));

  AndLogicExpr expr1(make_unique<BaseMathExpr>(trueVar1));
  expr1.addOperand(make_unique<BaseMathExpr>(falseVar1));
  expr1.addOperand(make_unique<BaseMathExpr>(falseVar2));

  AndLogicExpr expr2(make_unique<BaseMathExpr>(falseVar2));
  expr2.addOperand(make_unique<BaseMathExpr>(falseVar1));
  expr2.addOperand(make_unique<BaseMathExpr>(trueVar1));

  AndLogicExpr expr3(make_unique<BaseMathExpr>(falseVar1));
  expr3.addOperand(make_unique<BaseMathExpr>(falseVar2));
  expr3.addOperand(make_unique<BaseMathExpr>(trueVar1));

  BOOST_CHECK_EQUAL(false, static_cast<bool>(expr1.calculate()));
  BOOST_CHECK_EQUAL(false, static_cast<bool>(expr2.calculate()));
  BOOST_CHECK_EQUAL(false, static_cast<bool>(expr3.calculate()));
}

BOOST_AUTO_TEST_CASE(GivenThreeVals_ValueIsCorrect_3) {
  Variable trueVar1 = Variable({5, 1, 0});
  Variable trueVar2 = Variable({1, -9});
  Variable trueVar3 = Variable({-99});

  BOOST_REQUIRE_EQUAL(true, static_cast<bool>(trueVar1));
  BOOST_REQUIRE_EQUAL(true, static_cast<bool>(trueVar2));
  BOOST_REQUIRE_EQUAL(true, static_cast<bool>(trueVar3));

  AndLogicExpr expr1(make_unique<BaseMathExpr>(trueVar1));
  expr1.addOperand(make_unique<BaseMathExpr>(trueVar2));
  expr1.addOperand(make_unique<BaseMathExpr>(trueVar3));

  AndLogicExpr expr2(make_unique<BaseMathExpr>(trueVar1));
  expr2.addOperand(make_unique<BaseMathExpr>(trueVar3));
  expr2.addOperand(make_unique<BaseMathExpr>(trueVar2));

  AndLogicExpr expr3(make_unique<BaseMathExpr>(trueVar2));
  expr3.addOperand(make_unique<BaseMathExpr>(trueVar1));
  expr3.addOperand(make_unique<BaseMathExpr>(trueVar3));

  BOOST_CHECK_EQUAL(true, static_cast<bool>(expr1.calculate()));
  BOOST_CHECK_EQUAL(true, static_cast<bool>(expr2.calculate()));
  BOOST_CHECK_EQUAL(true, static_cast<bool>(expr3.calculate()));
}

BOOST_AUTO_TEST_CASE(GivenFiveValues_ValueIsCorrect_1) {
  Variable trueVar1 = Variable({-1, 1, 0});
  Variable trueVar2 = Variable({1, 9});
  Variable trueVar3 = Variable({0, -2});
  Variable trueVar4 = Variable({1, 7});
  Variable trueVar5 = Variable({19, -5});

  BOOST_REQUIRE_EQUAL(true, static_cast<bool>(trueVar1));
  BOOST_REQUIRE_EQUAL(true, static_cast<bool>(trueVar2));
  BOOST_REQUIRE_EQUAL(true, static_cast<bool>(trueVar3));
  BOOST_REQUIRE_EQUAL(true, static_cast<bool>(trueVar4));
  BOOST_REQUIRE_EQUAL(true, static_cast<bool>(trueVar5));

  AndLogicExpr expr(make_unique<BaseMathExpr>(trueVar1));
  expr.addOperand(make_unique<BaseMathExpr>(trueVar2));
  expr.addOperand(make_unique<BaseMathExpr>(trueVar3));
  expr.addOperand(make_unique<BaseMathExpr>(trueVar4));
  expr.addOperand(make_unique<BaseMathExpr>(trueVar5));

  BOOST_CHECK_EQUAL(true, static_cast<bool>(expr.calculate()));
}

BOOST_AUTO_TEST_CASE(GivenFiveValues_ValueIsCorrect_2) {
  Variable trueVar1  = Variable({-1, 1, 0});
  Variable trueVar2  = Variable({1, 9});
  Variable trueVar3  = Variable({0, -2});
  Variable trueVar4  = Variable({1, 7});
  Variable falseVar1 = Variable({0, 0});

  BOOST_REQUIRE_EQUAL(true, static_cast<bool>(trueVar1));
  BOOST_REQUIRE_EQUAL(true, static_cast<bool>(trueVar2));
  BOOST_REQUIRE_EQUAL(true, static_cast<bool>(trueVar3));
  BOOST_REQUIRE_EQUAL(true, static_cast<bool>(trueVar4));
  BOOST_REQUIRE_EQUAL(false, static_cast<bool>(falseVar1));

  AndLogicExpr expr(make_unique<BaseMathExpr>(trueVar1));
  expr.addOperand(make_unique<BaseMathExpr>(trueVar2));
  expr.addOperand(make_unique<BaseMathExpr>(trueVar3));
  expr.addOperand(make_unique<BaseMathExpr>(trueVar4));
  expr.addOperand(make_unique<BaseMathExpr>(falseVar1));

  BOOST_CHECK_EQUAL(false, static_cast<bool>(expr.calculate()));
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()