//
// Created by przemek on 27.03.2020.
//

#include <boost/test/unit_test.hpp>
#include <error/exeception.h>
#include <AST/expression/base_math_expr.h>
#include <AST/expression/multiply_expr.h>

using vecc::MultiplyExpr;
using vecc::BaseMathExpr;
using vecc::Variable;

using std::move;
using std::unique_ptr;
using std::make_unique;

BOOST_AUTO_TEST_SUITE(AST_Test_Suite)

    BOOST_AUTO_TEST_SUITE(Multiply_Expr_Test_Suite)

        BOOST_AUTO_TEST_CASE(GivenMathExpr_ValueIsCorrect) {
            Variable var = Variable({1, 2, 3});
            MultiplyExpr expr(make_unique<BaseMathExpr>(var));
             

            BOOST_CHECK(static_cast<bool>(expr.calculate() == var));
        }

        BOOST_AUTO_TEST_CASE(GivenMultiply_ValueIsCorrect) {
            Variable var = Variable({-5});
            MultiplyExpr expr(make_unique<BaseMathExpr>(var));
             
            expr.addOperand(make_unique<BaseMathExpr>( Variable({2})),
                            MultiplyExpr::OperatorType::Multiply);

            BOOST_CHECK(static_cast<bool>(expr.calculate() == Variable({-10})));
        }

        BOOST_AUTO_TEST_CASE(GivenModulo_ValueIsCorrect) {
            Variable var = Variable({1});
            MultiplyExpr expr(make_unique<BaseMathExpr>(var));
             
            expr.addOperand(make_unique<BaseMathExpr>( Variable({3})),
                            MultiplyExpr::OperatorType::Modulo);

            BOOST_CHECK(static_cast<bool>(expr.calculate() == Variable({1})));
        }

        BOOST_AUTO_TEST_CASE(GivenDivide_ValueIsCorrect) {
            Variable var = Variable({20});
            MultiplyExpr expr(make_unique<BaseMathExpr>(var));
             
            expr.addOperand(make_unique<BaseMathExpr>( Variable({5})),
                            MultiplyExpr::OperatorType::Divide);

            BOOST_CHECK(static_cast<bool>(expr.calculate() == Variable({4})));
        }

        BOOST_AUTO_TEST_CASE(GivenVec2Multiply_ValueIsCorrect) {
            Variable var = Variable({1, 2});
            MultiplyExpr expr(make_unique<BaseMathExpr>(var));
             
            expr.addOperand(make_unique<BaseMathExpr>( Variable({2})),
                            MultiplyExpr::OperatorType::Multiply);

            BOOST_CHECK(static_cast<bool>(expr.calculate() == Variable({2, 4})));
        }

        BOOST_AUTO_TEST_CASE(GivenVec2Modulo_ValueIsCorrect) {
            Variable var = Variable({1, 2});
            MultiplyExpr expr(make_unique<BaseMathExpr>(var));
             
            expr.addOperand(make_unique<BaseMathExpr>( Variable({3})),
                            MultiplyExpr::OperatorType::Modulo);

            BOOST_CHECK(static_cast<bool>(expr.calculate() == Variable({1, 2})));
        }

        BOOST_AUTO_TEST_CASE(GivenVec2Divide_ValueIsCorrect) {
            Variable var = Variable({2, 5});
            MultiplyExpr expr(make_unique<BaseMathExpr>(var));
             
            expr.addOperand(make_unique<BaseMathExpr>( Variable({2})),
                            MultiplyExpr::OperatorType::Divide);

            BOOST_CHECK(static_cast<bool>(expr.calculate() == Variable({1, 2})));
        }

        BOOST_AUTO_TEST_CASE(GivenVec3Multiply_ValueIsCorrect) {
            Variable var = Variable({1, 2, 3});
            MultiplyExpr expr(make_unique<BaseMathExpr>(var));
             
            expr.addOperand(make_unique<BaseMathExpr>(Variable({2})),
                            MultiplyExpr::OperatorType::Multiply);

            BOOST_CHECK(static_cast<bool>(expr.calculate() == Variable({2, 4, 6})));
        }

        BOOST_AUTO_TEST_CASE(GivenVec3Modulo_ValueIsCorrect) {
            Variable var = Variable({1, 2, 3});
            MultiplyExpr expr(make_unique<BaseMathExpr>(var));
             
            expr.addOperand(make_unique<BaseMathExpr>( Variable({3})),
                            MultiplyExpr::OperatorType::Modulo);

            BOOST_CHECK(static_cast<bool>(expr.calculate() == Variable({1, 2, 0})));
        }

        BOOST_AUTO_TEST_CASE(GivenVec3Divide_ValueIsCorrect) {
            Variable var = Variable({2, 5, 4});
            MultiplyExpr expr(make_unique<BaseMathExpr>(var));
             
            expr.addOperand(make_unique<BaseMathExpr>( Variable({2})),
                            MultiplyExpr::OperatorType::Divide);

            BOOST_CHECK(static_cast<bool>(expr.calculate() == Variable({1, 2, 2})));
        }

        BOOST_AUTO_TEST_CASE(GivenZeroDivision_Throws) {
            Variable var = Variable({1, 2, 3});
            MultiplyExpr expr(make_unique<BaseMathExpr>(var));
             
            expr.addOperand(make_unique<BaseMathExpr>( Variable({0})),
                            MultiplyExpr::OperatorType::Divide);
            Variable temp;
            BOOST_CHECK_THROW(temp = expr.calculate(), vecc::MathException);
        }

        BOOST_AUTO_TEST_CASE(GivenZeroModulo_Throws) {
            Variable var = Variable({1, 2, 3});
            MultiplyExpr expr(make_unique<BaseMathExpr>(var));
             
            expr.addOperand(make_unique<BaseMathExpr>( Variable({0})),
                            MultiplyExpr::OperatorType::Modulo);
            Variable temp;
            BOOST_CHECK_THROW(temp = expr.calculate(), vecc::MathException);
        }

        BOOST_AUTO_TEST_CASE(GivenWrongDimMultiply_Throws) {
            Variable var = Variable({1, 2, 3});
            MultiplyExpr expr(make_unique<BaseMathExpr>(var));
             
            expr.addOperand(make_unique<BaseMathExpr>( Variable({2, 2})),
                            MultiplyExpr::OperatorType::Multiply);
            Variable temp;
            BOOST_CHECK_THROW(temp = expr.calculate(), vecc::MathException);
        }

        BOOST_AUTO_TEST_CASE(GivenWrongDimDivision_Throws) {
            Variable var = Variable({1, 2, 3});
            MultiplyExpr expr(make_unique<BaseMathExpr>(var));
             
            expr.addOperand(make_unique<BaseMathExpr>( Variable({2, 2})),
                            MultiplyExpr::OperatorType::Divide);
            Variable temp;
            BOOST_CHECK_THROW(temp = expr.calculate(), vecc::MathException);
        }

        BOOST_AUTO_TEST_CASE(GivenWrongDimModulo_Throws) {
            Variable var = Variable({1, 2, 3});
            MultiplyExpr expr(make_unique<BaseMathExpr>(var));
             
            expr.addOperand(make_unique<BaseMathExpr>( Variable({2, 2})),
                            MultiplyExpr::OperatorType::Modulo);
            Variable temp;
            BOOST_CHECK_THROW(temp = expr.calculate(), vecc::MathException);
        }

    BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()