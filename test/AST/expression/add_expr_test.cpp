//
// Created by przemek on 27.03.2020.
//

#include <boost/test/unit_test.hpp>
#include <error/exeception.h>
#include <AST/expression/base_math_expr.h>
#include <AST/expression/additive_expr.h>

using vecc::AddExpr;
using vecc::BaseMathExpr;
using vecc::Variable;

using std::move;
using std::unique_ptr;
using std::make_unique;

BOOST_AUTO_TEST_SUITE(AST_Test_Suite)

    BOOST_AUTO_TEST_SUITE(Add_Expr_Test_Suite)

        BOOST_AUTO_TEST_CASE(GivenMathExpr_ValueIsCorrect) {
            Variable var = Variable({1, 2, 3});
            unique_ptr<Variable> variable =
                    make_unique<Variable>(var);
            AddExpr expr(make_unique<BaseMathExpr>(move(variable)));

            BOOST_CHECK(static_cast<bool>(expr.calculate() == var));
        }

        BOOST_AUTO_TEST_CASE(GivenAdd_ValueIsCorrect) {
            Variable var = Variable({1});
            unique_ptr<Variable> variable =
                    make_unique<Variable>(var);
            AddExpr expr(make_unique<BaseMathExpr>(move(variable)));
            expr.addOperand(make_unique<BaseMathExpr>(make_unique<Variable>(Variable({4}))),
                            AddExpr::OperatorType::Add);

            BOOST_CHECK(static_cast<bool>(expr.calculate() == Variable({5})));
        }

        BOOST_AUTO_TEST_CASE(GivenSubstract_ValueIsCorrect) {
            Variable var = Variable({1});
            unique_ptr<Variable> variable =
                    make_unique<Variable>(var);
            AddExpr expr(make_unique<BaseMathExpr>(move(variable)));
            expr.addOperand(make_unique<BaseMathExpr>(make_unique<Variable>(Variable({3}))),
                            AddExpr::OperatorType::Substract);

            BOOST_CHECK(static_cast<bool>(expr.calculate() == Variable({-2})));
        }

        BOOST_AUTO_TEST_CASE(GivenVec2Add_ValueIsCorrect) {
            Variable var = Variable({1, 2});
            unique_ptr<Variable> variable =
                    make_unique<Variable>(var);
            AddExpr expr(make_unique<BaseMathExpr>(move(variable)));
            expr.addOperand(make_unique<BaseMathExpr>(make_unique<Variable>(Variable({-2, 2}))),
                            AddExpr::OperatorType::Add);

            BOOST_CHECK(static_cast<bool>(expr.calculate() == Variable({-1, 4})));
        }

        BOOST_AUTO_TEST_CASE(GivenVec2Substract_ValueIsCorrect) {
            Variable var = Variable({1, 2});
            unique_ptr<Variable> variable =
                    make_unique<Variable>(var);
            AddExpr expr(make_unique<BaseMathExpr>(move(variable)));
            expr.addOperand(make_unique<BaseMathExpr>(make_unique<Variable>(Variable({-1, 2}))),
                            AddExpr::OperatorType::Substract);

            BOOST_CHECK(static_cast<bool>(expr.calculate() == Variable({2, 0})));
        }

        BOOST_AUTO_TEST_CASE(GivenVec3Add_ValueIsCorrect) {
            Variable var = Variable({1, 2, 3});
            unique_ptr<Variable> variable =
                    make_unique<Variable>(var);
            AddExpr expr(make_unique<BaseMathExpr>(move(variable)));
            expr.addOperand(make_unique<BaseMathExpr>(make_unique<Variable>(Variable({2, 2, 2}))),
                            AddExpr::OperatorType::Add);

            BOOST_CHECK(static_cast<bool>(expr.calculate() == Variable({3, 4, 5})));
        }

        BOOST_AUTO_TEST_CASE(Givenvec3Substract_ValueIsCorrect) {
            Variable var = Variable({1, 2, 3});
            unique_ptr<Variable> variable =
                    make_unique<Variable>(var);
            AddExpr expr(make_unique<BaseMathExpr>(move(variable)));
            expr.addOperand(make_unique<BaseMathExpr>(make_unique<Variable>(Variable({3, 2, 1}))),
                            AddExpr::OperatorType::Substract);

            BOOST_CHECK(static_cast<bool>(expr.calculate() == Variable({-2, 0, 2})));
        }

        BOOST_AUTO_TEST_CASE(GivenWrongDimAdd_Throws) {
            Variable var = Variable({1, 2, 3});
            unique_ptr<Variable> variable =
                    make_unique<Variable>(var);
            AddExpr expr(make_unique<BaseMathExpr>(move(variable)));
            expr.addOperand(make_unique<BaseMathExpr>(make_unique<Variable>(Variable({2, 2}))),
                            AddExpr::OperatorType::Add);
            Variable temp;
            BOOST_CHECK_THROW(temp = expr.calculate(), vecc::MathException);
        }

        BOOST_AUTO_TEST_CASE(GivenWrongDimSubstract_Throws) {
            Variable var = Variable({1, 2, 3});
            unique_ptr<Variable> variable =
                    make_unique<Variable>(var);
            AddExpr expr(make_unique<BaseMathExpr>(move(variable)));
            expr.addOperand(make_unique<BaseMathExpr>(make_unique<Variable>(Variable({2, 2}))),
                            AddExpr::OperatorType::Substract);
            Variable temp;
            BOOST_CHECK_THROW(temp = expr.calculate(), vecc::MathException);
        }

    BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()