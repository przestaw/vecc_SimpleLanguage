//
// Created by przemek on 27.03.2020.
//

#include <AST/expression/additive_expr.h>
#include <AST/expression/base_math_expr.h>
#include <boost/test/unit_test.hpp>
#include <error/exeception.h>

using namespace vecc;
using namespace vecc::error;
using namespace vecc::ast;

using std::make_unique;
using std::move;
using std::unique_ptr;

BOOST_AUTO_TEST_SUITE(AST_Test_Suite)

BOOST_AUTO_TEST_SUITE(Add_Expr_Test_Suite)

BOOST_AUTO_TEST_CASE(GivenMathExpr_ValueIsCorrect) {
  Variable var = Variable({1, 2, 3});

  AdditiveExpr expr(make_unique<BaseMathExpr>(var));

  BOOST_CHECK_EQUAL(expr.calculate(), var);
}

BOOST_AUTO_TEST_CASE(GivenAdd_ValueIsCorrect) {
  Variable var = Variable({1});

  AdditiveExpr expr(make_unique<BaseMathExpr>(var));
  expr.addOperand(make_unique<BaseMathExpr>((Variable({4}))),
                  AdditiveExpr::OperatorType::Add);

  BOOST_CHECK_EQUAL(expr.calculate(), Variable({5}));
}

BOOST_AUTO_TEST_CASE(GivenSubstract_ValueIsCorrect) {
  Variable var = Variable({1});

  AdditiveExpr expr(make_unique<BaseMathExpr>(var));
  expr.addOperand(make_unique<BaseMathExpr>((Variable({3}))),
                  AdditiveExpr::OperatorType::Substract);

  BOOST_CHECK_EQUAL(expr.calculate(), Variable({-2}));
}

BOOST_AUTO_TEST_CASE(GivenVec2Add_ValueIsCorrect) {
  Variable var = Variable({1, 2});

  AdditiveExpr expr(make_unique<BaseMathExpr>(var));
  expr.addOperand(make_unique<BaseMathExpr>((Variable({-2, 2}))),
                  AdditiveExpr::OperatorType::Add);

  BOOST_CHECK_EQUAL(expr.calculate(), Variable({-1, 4}));
}

BOOST_AUTO_TEST_CASE(GivenVec2Substract_ValueIsCorrect) {
  Variable var = Variable({1, 2});

  AdditiveExpr expr(make_unique<BaseMathExpr>(var));
  expr.addOperand(make_unique<BaseMathExpr>((Variable({-1, 2}))),
                  AdditiveExpr::OperatorType::Substract);

  BOOST_CHECK_EQUAL(expr.calculate(), Variable({2, 0}));
}

BOOST_AUTO_TEST_CASE(GivenVal_ToStringCorrect) {
  Variable var = Variable({1, 2});

  AdditiveExpr expr(make_unique<BaseMathExpr>(var));

  BOOST_CHECK_EQUAL(expr.toString(), "vec[1, 2]");
}

BOOST_AUTO_TEST_CASE(GivenAdd_ToStringCorrect) {
  Variable var = Variable({1, 2});

  AdditiveExpr expr(make_unique<BaseMathExpr>(var));
  expr.addOperand(make_unique<BaseMathExpr>((Variable({-2, 2}))),
                  AdditiveExpr::OperatorType::Add);

  BOOST_CHECK_EQUAL(expr.toString(), "(vec[1, 2]+vec[-2, 2])");
}

BOOST_AUTO_TEST_CASE(GivenMultiple_ToStringCorrect) {
  Variable var = Variable({1, 2});

  AdditiveExpr expr(make_unique<BaseMathExpr>(var));
  expr.addOperand(make_unique<BaseMathExpr>((Variable({-1, 2}))),
                  AdditiveExpr::OperatorType::Substract);
  expr.addOperand(make_unique<BaseMathExpr>((Variable({-2, 2}))),
                  AdditiveExpr::OperatorType::Add);

  BOOST_CHECK_EQUAL(expr.toString(), "(vec[1, 2]-vec[-1, 2]+vec[-2, 2])");
}

BOOST_AUTO_TEST_CASE(GivenVec3Add_ValueIsCorrect) {
  Variable var = Variable({1, 2, 3});

  AdditiveExpr expr(make_unique<BaseMathExpr>(var));
  expr.addOperand(make_unique<BaseMathExpr>((Variable({2, 2, 2}))),
                  AdditiveExpr::OperatorType::Add);

  BOOST_CHECK_EQUAL(expr.calculate(), Variable({3, 4, 5}));
}

BOOST_AUTO_TEST_CASE(Givenvec3Substract_ValueIsCorrect) {
  Variable var = Variable({1, 2, 3});

  AdditiveExpr expr(make_unique<BaseMathExpr>(var));
  expr.addOperand(make_unique<BaseMathExpr>((Variable({3, 2, 1}))),
                  AdditiveExpr::OperatorType::Substract);

  BOOST_CHECK_EQUAL(expr.calculate(), Variable({-2, 0, 2}));
}

BOOST_AUTO_TEST_CASE(GivenWrongDimAdd_Throws) {
  Variable var = Variable({1, 2, 3});

  AdditiveExpr expr(make_unique<BaseMathExpr>(var));
  expr.addOperand(make_unique<BaseMathExpr>((Variable({2, 2}))),
                  AdditiveExpr::OperatorType::Add);
  Variable temp;
  BOOST_CHECK_THROW(temp = expr.calculate(), MathException);
}

BOOST_AUTO_TEST_CASE(GivenWrongDimSubstract_Throws) {
  Variable var = Variable({1, 2, 3});

  AdditiveExpr expr(make_unique<BaseMathExpr>(var));
  expr.addOperand(make_unique<BaseMathExpr>((Variable({2, 2}))),
                  AdditiveExpr::OperatorType::Substract);
  Variable temp;
  BOOST_CHECK_THROW(temp = expr.calculate(), MathException);
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()