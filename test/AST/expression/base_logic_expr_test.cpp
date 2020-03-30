//
// Created by przemek on 27.03.2020.
//

#include <boost/test/unit_test.hpp>
#include <error/exeception.h>
#include <AST/expression/base_math_expr.h>
#include <AST/expression/base_logic_expr.h>

using vecc::BaseLogicExpr;
using vecc::BaseMathExpr;
using vecc::Variable;

using std::move;
using std::unique_ptr;
using std::make_unique;

BOOST_AUTO_TEST_SUITE(AST_Test_Suite)

    BOOST_AUTO_TEST_SUITE(Base_Logic_Expr_Test_Suite)

        BOOST_AUTO_TEST_CASE(BaseLogic_ReturnsVal) {
            Variable var = Variable({1, 2, 3});
            unique_ptr<Variable> variable =
                    make_unique<Variable>(var);
            BaseLogicExpr expr(make_unique<BaseMathExpr>(move(variable)));

            BOOST_CHECK(static_cast<bool>(expr.calculate() == var));
        }

        BOOST_AUTO_TEST_CASE(NegatedBaseLogic_ReturnsNegatedVal) {
            Variable var = Variable({1, 2, 3});
            unique_ptr<Variable> variable =
                    make_unique<Variable>(var);
            BaseLogicExpr expr(make_unique<BaseMathExpr>(move(variable)), true);

            BOOST_CHECK(static_cast<bool>(expr.calculate() == !var));
        }

    BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()