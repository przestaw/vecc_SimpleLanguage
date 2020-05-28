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

class MockExpr : public Expression {
public:
  Variable calculate() const override { return Variable(); }
  std::string toString() const override { return "expression"; };
};

BOOST_AUTO_TEST_CASE(GivenExpr_ToStringCorrect) {
  auto expr = MockExpr();
  BaseLogicExpr expr1(std::make_unique<MockExpr>(MockExpr()), false);
  BaseLogicExpr expr2(std::make_unique<MockExpr>(MockExpr()), true);

  BOOST_CHECK_EQUAL(expr1.toString(), expr.toString());
  BOOST_CHECK_EQUAL(expr2.toString(), "(not " + expr.toString() + ")");
}
BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()