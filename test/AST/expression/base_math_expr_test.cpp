//
// Created by przemek on 23.03.2020.
//

#include <boost/test/unit_test.hpp>
#include <AST/expression/base_math_expr.h>

using vecc::BaseMathExpr;
using vecc::Variable;

BOOST_AUTO_TEST_SUITE(AST_Test_Suite)

    BOOST_AUTO_TEST_SUITE(Base_Math_Expr_Test_Suite)

        BOOST_AUTO_TEST_CASE(GivenConstatnt_ValueIsCorrect) {
            Variable constant({1, 2, 3});

            BaseMathExpr expr1(std::make_unique<Variable>(constant), false);
            BaseMathExpr expr2(std::make_unique<Variable>(constant), true);

            BOOST_CHECK(static_cast<bool>(expr1.calculate() == Variable({1, 2, 3})));
            BOOST_CHECK(static_cast<bool>(expr2.calculate() == Variable({-1, -2, -3})));
        }

        BOOST_AUTO_TEST_CASE(GivenVariable_ValueIsCorrect) {
            Variable constant({1, 2, 3});

            BaseMathExpr expr1(&constant, false);
            BaseMathExpr expr2(&constant, true);

            BOOST_CHECK(static_cast<bool>(expr1.calculate() == Variable({1, 2, 3})));
            BOOST_CHECK(static_cast<bool>(expr2.calculate() == Variable({-1, -2, -3})));
        }

        BOOST_AUTO_TEST_CASE(GivenVariable_WhenVariableChangesValueIsCorrect) {
            Variable constant({1, 2, 3});

            BaseMathExpr expr1(&constant, false);
            BaseMathExpr expr2(&constant, true);

            constant = constant + Variable({3, 2, 1});

            BOOST_CHECK(static_cast<bool>(expr1.calculate() == Variable({4, 4, 4})));
            BOOST_CHECK(static_cast<bool>(expr2.calculate() == Variable({-4, -4, -4})));
        }

    BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()