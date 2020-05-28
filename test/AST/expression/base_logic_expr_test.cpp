//
// Created by przemek on 27.03.2020.
//

#include <AST/expression/base_logic_expr.h>
#include <AST/expression/base_math_expr.h>
#include <boost/test/unit_test.hpp>
#include <error/exeception.h>

using namespace vecc;
using namespace vecc::ast;

using std::make_unique;
using std::move;
using std::unique_ptr;

BOOST_AUTO_TEST_SUITE(AST_Test_Suite)

BOOST_AUTO_TEST_SUITE(Base_Logic_Expr_Test_Suite)

BOOST_AUTO_TEST_CASE(BaseLogic_ReturnsVal) {
  Variable var = Variable({1, 2, 3});

  BaseLogicExpr expr(make_unique<BaseMathExpr>(var));

  BOOST_CHECK(expr.calculate() == var);
}

BOOST_AUTO_TEST_CASE(NegatedBaseLogic_ReturnsNegatedVal) {
  Variable var = Variable({1, 2, 3});

  BaseLogicExpr expr(make_unique<BaseMathExpr>(var), true);

  BOOST_CHECK(expr.calculate() == !var);
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()