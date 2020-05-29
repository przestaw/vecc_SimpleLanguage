//
// Created by przemek on 27.03.2020.
//

#include <AST/expression/base_math_expr.h>
#include <AST/expression/or_logic_expr.h>
#include <boost/test/unit_test.hpp>
#include <error/exeception.h>

using namespace vecc;
using namespace vecc::ast;

using std::make_unique;
using std::move;
using std::unique_ptr;

BOOST_AUTO_TEST_SUITE(AST_Test_Suite)

BOOST_AUTO_TEST_SUITE(Or_Logic_Expr_Test_Suite)

BOOST_AUTO_TEST_CASE(GivenMathExpr_ValueIsCorrect) {
  Variable var = Variable({1, 2, 3});
  OrLogicExpr expr(make_unique<BaseMathExpr>(var));

  BOOST_CHECK_EQUAL(expr.calculate(), var);
}

BOOST_AUTO_TEST_CASE(GivenTrueAndFalse_ValueIsCorrect) {
  Variable trueVar  = Variable({1, 2, 3});
  Variable falseVar = Variable({0, 0});

  BOOST_REQUIRE_EQUAL(true, trueVar);
  BOOST_REQUIRE_EQUAL(false, falseVar);

  OrLogicExpr expr(make_unique<BaseMathExpr>(trueVar));
  expr.addOperand(make_unique<BaseMathExpr>(falseVar));

  BOOST_CHECK_EQUAL(true, expr.calculate());
}

BOOST_AUTO_TEST_CASE(GivenFalseAndFalse_ValueIsCorrect) {
  Variable falseVar1 = Variable({0, 0, 0});
  Variable falseVar2 = Variable({0, 0});

  BOOST_REQUIRE_EQUAL(false, falseVar1);
  BOOST_REQUIRE_EQUAL(false, falseVar2);

  OrLogicExpr expr(make_unique<BaseMathExpr>(falseVar1));
  expr.addOperand(make_unique<BaseMathExpr>(falseVar2));

  BOOST_CHECK_EQUAL(false, expr.calculate());
}

BOOST_AUTO_TEST_CASE(GivenTrueAndTrue_ValueIsCorrect) {
  Variable trueVar1 = Variable({1, 1, 0});
  Variable trueVar2 = Variable({1, 0});

  BOOST_REQUIRE_EQUAL(true, trueVar1);
  BOOST_REQUIRE_EQUAL(true, trueVar2);

  OrLogicExpr expr(make_unique<BaseMathExpr>(trueVar1));
  expr.addOperand(make_unique<BaseMathExpr>(trueVar2));

  BOOST_CHECK_EQUAL(true, expr.calculate());
}

BOOST_AUTO_TEST_CASE(GivenThreeVals_ValueIsCorrect_1) {
  Variable trueVar1  = Variable({5, 1, 0});
  Variable trueVar2  = Variable({1, -9});
  Variable falseVar1 = Variable({0, 0});

  BOOST_REQUIRE_EQUAL(true, trueVar1);
  BOOST_REQUIRE_EQUAL(true, trueVar2);
  BOOST_REQUIRE_EQUAL(false, falseVar1);

  OrLogicExpr expr1(make_unique<BaseMathExpr>(trueVar1));
  expr1.addOperand(make_unique<BaseMathExpr>(trueVar2));
  expr1.addOperand(make_unique<BaseMathExpr>(falseVar1));

  OrLogicExpr expr2(make_unique<BaseMathExpr>(trueVar2));
  expr2.addOperand(make_unique<BaseMathExpr>(falseVar1));
  expr2.addOperand(make_unique<BaseMathExpr>(trueVar1));

  OrLogicExpr expr3(make_unique<BaseMathExpr>(falseVar1));
  expr3.addOperand(make_unique<BaseMathExpr>(trueVar2));
  expr3.addOperand(make_unique<BaseMathExpr>(trueVar1));

  BOOST_CHECK_EQUAL(true, expr1.calculate());
  BOOST_CHECK_EQUAL(true, expr2.calculate());
  BOOST_CHECK_EQUAL(true, expr3.calculate());
}

BOOST_AUTO_TEST_CASE(GivenThreeVals_ValueIsCorrect_2) {
  Variable trueVar1  = Variable({5, 1, 0});
  Variable falseVar1 = Variable({0, 0, 0});
  Variable falseVar2 = Variable({0, 0});

  BOOST_REQUIRE_EQUAL(true, trueVar1);
  BOOST_REQUIRE_EQUAL(false, falseVar1);
  BOOST_REQUIRE_EQUAL(false, falseVar2);

  OrLogicExpr expr1(make_unique<BaseMathExpr>(trueVar1));
  expr1.addOperand(make_unique<BaseMathExpr>(falseVar1));
  expr1.addOperand(make_unique<BaseMathExpr>(falseVar2));

  OrLogicExpr expr2(make_unique<BaseMathExpr>(falseVar2));
  expr2.addOperand(make_unique<BaseMathExpr>(falseVar1));
  expr2.addOperand(make_unique<BaseMathExpr>(trueVar1));

  OrLogicExpr expr3(make_unique<BaseMathExpr>(falseVar1));
  expr3.addOperand(make_unique<BaseMathExpr>(falseVar2));
  expr3.addOperand(make_unique<BaseMathExpr>(trueVar1));

  BOOST_CHECK_EQUAL(true, expr1.calculate());
  BOOST_CHECK_EQUAL(true, expr2.calculate());
  BOOST_CHECK_EQUAL(true, expr3.calculate());
}

BOOST_AUTO_TEST_CASE(GivenThreeVals_ValueIsCorrect_3) {
  Variable falseVar1 = Variable({0, 0, 0});
  Variable falseVar2 = Variable({0, 0});
  Variable falseVar3 = Variable({0});

  BOOST_REQUIRE_EQUAL(false, falseVar1);
  BOOST_REQUIRE_EQUAL(false, falseVar2);
  BOOST_REQUIRE_EQUAL(false, falseVar3);

  OrLogicExpr expr1(make_unique<BaseMathExpr>(falseVar1));
  expr1.addOperand(make_unique<BaseMathExpr>(falseVar2));
  expr1.addOperand(make_unique<BaseMathExpr>(falseVar3));

  OrLogicExpr expr2(make_unique<BaseMathExpr>(falseVar3));
  expr2.addOperand(make_unique<BaseMathExpr>(falseVar2));
  expr2.addOperand(make_unique<BaseMathExpr>(falseVar1));

  OrLogicExpr expr3(make_unique<BaseMathExpr>(falseVar2));
  expr3.addOperand(make_unique<BaseMathExpr>(falseVar3));
  expr3.addOperand(make_unique<BaseMathExpr>(falseVar1));

  BOOST_CHECK_EQUAL(false, expr1.calculate());
  BOOST_CHECK_EQUAL(false, expr2.calculate());
  BOOST_CHECK_EQUAL(false, expr3.calculate());
}

BOOST_AUTO_TEST_CASE(GivenFiveValues_ValueIsCorrect_1) {
  Variable falseVar1 = Variable({0, 0, 0});
  Variable falseVar2 = Variable({0, 0});
  Variable falseVar3 = Variable({0});
  Variable trueVar4  = Variable({1, 7});
  Variable trueVar5  = Variable({19, -5});

  BOOST_REQUIRE_EQUAL(false, falseVar1);
  BOOST_REQUIRE_EQUAL(false, falseVar2);
  BOOST_REQUIRE_EQUAL(false, falseVar3);
  BOOST_REQUIRE_EQUAL(true, trueVar4);
  BOOST_REQUIRE_EQUAL(true, trueVar5);

  OrLogicExpr expr(make_unique<BaseMathExpr>(falseVar1));
  expr.addOperand(make_unique<BaseMathExpr>(trueVar4));
  expr.addOperand(make_unique<BaseMathExpr>(falseVar2));
  expr.addOperand(make_unique<BaseMathExpr>(falseVar3));
  expr.addOperand(make_unique<BaseMathExpr>(trueVar5));

  BOOST_CHECK_EQUAL(true, expr.calculate());
}

BOOST_AUTO_TEST_CASE(GivenFiveValues_ValueIsCorrect_2) {
  Variable falseVar1 = Variable({0, 0, 0});
  Variable falseVar2 = Variable({0, 0});
  Variable falseVar3 = Variable({0});
  Variable trueVar1  = Variable({1, 7});
  Variable falseVar4 = Variable({0, 0});

  BOOST_REQUIRE_EQUAL(false, falseVar1);
  BOOST_REQUIRE_EQUAL(false, falseVar2);
  BOOST_REQUIRE_EQUAL(false, falseVar3);
  BOOST_REQUIRE_EQUAL(true, trueVar1);
  BOOST_REQUIRE_EQUAL(false, falseVar4);

  OrLogicExpr expr(make_unique<BaseMathExpr>(falseVar1));
  expr.addOperand(make_unique<BaseMathExpr>(falseVar2));
  expr.addOperand(make_unique<BaseMathExpr>(falseVar3));
  expr.addOperand(make_unique<BaseMathExpr>(trueVar1));
  expr.addOperand(make_unique<BaseMathExpr>(falseVar4));

  BOOST_CHECK_EQUAL(true, expr.calculate());
}

BOOST_AUTO_TEST_CASE(GivenFiveValues_ValueIsCorrect_3) {
  Variable falseVar1 = Variable({0, 0, 0});
  Variable falseVar2 = Variable({0, 0});
  Variable falseVar3 = Variable({0});
  Variable falseVar4 = Variable({0, 0, 0});
  Variable falseVar5 = Variable({0, 0});

  BOOST_REQUIRE_EQUAL(false, falseVar1);
  BOOST_REQUIRE_EQUAL(false, falseVar2);
  BOOST_REQUIRE_EQUAL(false, falseVar3);
  BOOST_REQUIRE_EQUAL(false, falseVar4);
  BOOST_REQUIRE_EQUAL(false, falseVar5);

  OrLogicExpr expr(make_unique<BaseMathExpr>(falseVar1));
  expr.addOperand(make_unique<BaseMathExpr>(falseVar2));
  expr.addOperand(make_unique<BaseMathExpr>(falseVar3));
  expr.addOperand(make_unique<BaseMathExpr>(falseVar4));
  expr.addOperand(make_unique<BaseMathExpr>(falseVar5));

  BOOST_CHECK_EQUAL(false, expr.calculate());
}

BOOST_AUTO_TEST_CASE(GivenVal_ToStringCorrect) {
  Variable var = Variable({1, 2});

  OrLogicExpr expr(make_unique<BaseMathExpr>(var));

  BOOST_CHECK_EQUAL(expr.toString(), "vec(1, 2)");
}

BOOST_AUTO_TEST_CASE(GivenThreeVals_ToStringCorrect) {
  Variable trueVar1  = Variable({5, 1, 0});
  Variable falseVar1 = Variable({0, 0, 0});
  Variable falseVar2 = Variable({0, 0});

  OrLogicExpr expr1(make_unique<BaseMathExpr>(trueVar1));
  expr1.addOperand(make_unique<BaseMathExpr>(falseVar1));
  expr1.addOperand(make_unique<BaseMathExpr>(falseVar2));

  BOOST_CHECK_EQUAL(expr1.toString(),
                    "(vec(5, 1, 0) or vec(0, 0, 0) or vec(0, 0))");
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()