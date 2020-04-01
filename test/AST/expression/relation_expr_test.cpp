//
// Created by przemek on 27.03.2020.
//

#include <boost/test/unit_test.hpp>
#include <error/exeception.h>
#include <AST/expression/base_math_expr.h>
#include <AST/expression/realtion_expr.h>

using vecc::RelationExpr;
using vecc::BaseMathExpr;
using vecc::Variable;

using std::move;
using std::unique_ptr;
using std::make_unique;

BOOST_AUTO_TEST_SUITE(AST_Test_Suite)

    BOOST_AUTO_TEST_SUITE(Relation_Expr_Test_Suite)

//        BOOST_AUTO_TEST_CASE(GivenMathExpr_ValueIsCorrect) {
//            Variable var = Variable({1, 2, 3});
//
//            unique_ptr<Variable> variable =
//                    make_unique<Variable>(var);
//
//            RelationExpr expr1(make_unique<BaseMathExpr>(move(variable)),
//                              RelationExpr::OperatorType::PassValue,
//                              unique_ptr<vecc::Expression>(nullptr));
//
//            variable = make_unique<Variable>(var);
//            RelationExpr expr2(make_unique<BaseMathExpr>(move(variable)));
//
//            BOOST_CHECK(static_cast<bool>(expr1.calculate() == var));
//            BOOST_CHECK(static_cast<bool>(expr2.calculate() == var));
//        }

        BOOST_AUTO_TEST_CASE(GivenTwoValues_EqualityReturnsCorrectValue) {
            Variable var1 = Variable({1});
            Variable var2 = Variable({2});

            RelationExpr expr1(make_unique<BaseMathExpr>(make_unique<Variable>(var1)),
                               RelationExpr::OperatorType::Equal,
                               make_unique<BaseMathExpr>(make_unique<Variable>(var1)));

            RelationExpr expr2(make_unique<BaseMathExpr>(make_unique<Variable>(var1)),
                               RelationExpr::OperatorType::Equal,
                               make_unique<BaseMathExpr>(make_unique<Variable>(var2)));

            RelationExpr expr3(make_unique<BaseMathExpr>(make_unique<Variable>(var2)),
                               RelationExpr::OperatorType::Equal,
                               make_unique<BaseMathExpr>(make_unique<Variable>(var2)));

            BOOST_CHECK_EQUAL(static_cast<bool>(expr1.calculate()), true);
            BOOST_CHECK_EQUAL(static_cast<bool>(expr2.calculate()), false);
            BOOST_CHECK_EQUAL(static_cast<bool>(expr3.calculate()), true);
        }

        BOOST_AUTO_TEST_CASE(GivenTwoVecValues_EqualityReturnsCorrectValue) {
            Variable var1 = Variable({1, 1});
            Variable var2 = Variable({2, 2});

            RelationExpr expr1(make_unique<BaseMathExpr>(make_unique<Variable>(var1)),
                               RelationExpr::OperatorType::Equal,
                               make_unique<BaseMathExpr>(make_unique<Variable>(var1)));

            RelationExpr expr2(make_unique<BaseMathExpr>(make_unique<Variable>(var1)),
                               RelationExpr::OperatorType::Equal,
                               make_unique<BaseMathExpr>(make_unique<Variable>(var2)));

            RelationExpr expr3(make_unique<BaseMathExpr>(make_unique<Variable>(var2)),
                               RelationExpr::OperatorType::Equal,
                               make_unique<BaseMathExpr>(make_unique<Variable>(var2)));

            BOOST_CHECK_EQUAL(static_cast<bool>(expr1.calculate()), true);
            BOOST_CHECK_EQUAL(static_cast<bool>(expr2.calculate()), false);
            BOOST_CHECK_EQUAL(static_cast<bool>(expr3.calculate()), true);
        }

        BOOST_AUTO_TEST_CASE(GivenTwoDiffrentDimVecValues_EqualityThrows) {
            Variable var1 = Variable({1, 1});
            Variable var2 = Variable({2, 2, 3});

            RelationExpr expr(make_unique<BaseMathExpr>(make_unique<Variable>(var1)),
                              RelationExpr::OperatorType::Equal,
                              make_unique<BaseMathExpr>(make_unique<Variable>(var2)));

            Variable temp;
            BOOST_CHECK_THROW(temp = expr.calculate(), vecc::MathException);
        }

        BOOST_AUTO_TEST_CASE(GivenTwoValues_InequalityReturnsCorrectValue) {
            Variable var1 = Variable({1});
            Variable var2 = Variable({2});

            RelationExpr expr1(make_unique<BaseMathExpr>(make_unique<Variable>(var1)),
                               RelationExpr::OperatorType::NotEqual,
                               make_unique<BaseMathExpr>(make_unique<Variable>(var1)));

            RelationExpr expr2(make_unique<BaseMathExpr>(make_unique<Variable>(var1)),
                               RelationExpr::OperatorType::NotEqual,
                               make_unique<BaseMathExpr>(make_unique<Variable>(var2)));

            RelationExpr expr3(make_unique<BaseMathExpr>(make_unique<Variable>(var2)),
                               RelationExpr::OperatorType::NotEqual,
                               make_unique<BaseMathExpr>(make_unique<Variable>(var2)));

            BOOST_CHECK_EQUAL(static_cast<bool>(expr1.calculate()), false);
            BOOST_CHECK_EQUAL(static_cast<bool>(expr2.calculate()), true);
            BOOST_CHECK_EQUAL(static_cast<bool>(expr3.calculate()), false);
        }

        BOOST_AUTO_TEST_CASE(GivenTwoVecValues_InequalityReturnsCorrectValue) {
            Variable var1 = Variable({1, 1});
            Variable var2 = Variable({2, 2});

            RelationExpr expr1(make_unique<BaseMathExpr>(make_unique<Variable>(var1)),
                               RelationExpr::OperatorType::NotEqual,
                               make_unique<BaseMathExpr>(make_unique<Variable>(var1)));

            RelationExpr expr2(make_unique<BaseMathExpr>(make_unique<Variable>(var1)),
                               RelationExpr::OperatorType::NotEqual,
                               make_unique<BaseMathExpr>(make_unique<Variable>(var2)));

            RelationExpr expr3(make_unique<BaseMathExpr>(make_unique<Variable>(var2)),
                               RelationExpr::OperatorType::NotEqual,
                               make_unique<BaseMathExpr>(make_unique<Variable>(var2)));

            BOOST_CHECK_EQUAL(static_cast<bool>(expr1.calculate()), false);
            BOOST_CHECK_EQUAL(static_cast<bool>(expr2.calculate()), true);
            BOOST_CHECK_EQUAL(static_cast<bool>(expr3.calculate()), false);
        }

        BOOST_AUTO_TEST_CASE(GivenTwoDiffrentDimVecValues_InequalityThrows) {
            Variable var1 = Variable({1, 1});
            Variable var2 = Variable({2, 2, 3});

            RelationExpr expr(make_unique<BaseMathExpr>(make_unique<Variable>(var1)),
                              RelationExpr::OperatorType::NotEqual,
                              make_unique<BaseMathExpr>(make_unique<Variable>(var2)));
            Variable temp;
            BOOST_CHECK_THROW(temp=expr.calculate(), vecc::MathException);
        }

        BOOST_AUTO_TEST_CASE(GivenTwoValues_LessReturnsCorrectValue) {
            Variable var1 = Variable({1});
            Variable var2 = Variable({2});

            RelationExpr expr1(make_unique<BaseMathExpr>(make_unique<Variable>(var1)),
                               RelationExpr::OperatorType::Less,
                               make_unique<BaseMathExpr>(make_unique<Variable>(var1)));

            RelationExpr expr2(make_unique<BaseMathExpr>(make_unique<Variable>(var1)),
                               RelationExpr::OperatorType::Less,
                               make_unique<BaseMathExpr>(make_unique<Variable>(var2)));

            RelationExpr expr3(make_unique<BaseMathExpr>(make_unique<Variable>(var2)),
                               RelationExpr::OperatorType::Less,
                               make_unique<BaseMathExpr>(make_unique<Variable>(var2)));

            RelationExpr expr4(make_unique<BaseMathExpr>(make_unique<Variable>(var2)),
                               RelationExpr::OperatorType::Less,
                               make_unique<BaseMathExpr>(make_unique<Variable>(var1)));

            BOOST_CHECK_EQUAL(static_cast<bool>(expr1.calculate()), false);
            BOOST_CHECK_EQUAL(static_cast<bool>(expr2.calculate()), true);
            BOOST_CHECK_EQUAL(static_cast<bool>(expr3.calculate()), false);
            BOOST_CHECK_EQUAL(static_cast<bool>(expr4.calculate()), false);
        }

        BOOST_AUTO_TEST_CASE(GivenTwoVecValues_LessThrows) {
            Variable var1 = Variable({1, 1});
            Variable var2 = Variable({2, 2});

            RelationExpr expr1(make_unique<BaseMathExpr>(make_unique<Variable>(var1)),
                               RelationExpr::OperatorType::Less,
                               make_unique<BaseMathExpr>(make_unique<Variable>(var1)));

            RelationExpr expr2(make_unique<BaseMathExpr>(make_unique<Variable>(var1)),
                               RelationExpr::OperatorType::Less,
                               make_unique<BaseMathExpr>(make_unique<Variable>(var2)));

            RelationExpr expr3(make_unique<BaseMathExpr>(make_unique<Variable>(var2)),
                               RelationExpr::OperatorType::Less,
                               make_unique<BaseMathExpr>(make_unique<Variable>(var2)));

            Variable temp;
            BOOST_CHECK_THROW(temp=expr1.calculate(), vecc::MathException);
            BOOST_CHECK_THROW(temp=expr2.calculate(), vecc::MathException);
            BOOST_CHECK_THROW(temp=expr3.calculate(), vecc::MathException);
        }

        BOOST_AUTO_TEST_CASE(GivenTwoValues_LessOrEqualReturnsCorrectValue) {
            Variable var1 = Variable({1});
            Variable var2 = Variable({2});

            RelationExpr expr1(make_unique<BaseMathExpr>(make_unique<Variable>(var1)),
                               RelationExpr::OperatorType::LessOrEqual,
                               make_unique<BaseMathExpr>(make_unique<Variable>(var1)));

            RelationExpr expr2(make_unique<BaseMathExpr>(make_unique<Variable>(var1)),
                               RelationExpr::OperatorType::LessOrEqual,
                               make_unique<BaseMathExpr>(make_unique<Variable>(var2)));

            RelationExpr expr3(make_unique<BaseMathExpr>(make_unique<Variable>(var2)),
                               RelationExpr::OperatorType::LessOrEqual,
                               make_unique<BaseMathExpr>(make_unique<Variable>(var2)));

            RelationExpr expr4(make_unique<BaseMathExpr>(make_unique<Variable>(var2)),
                               RelationExpr::OperatorType::LessOrEqual,
                               make_unique<BaseMathExpr>(make_unique<Variable>(var1)));


            BOOST_CHECK_EQUAL(static_cast<bool>(expr1.calculate()), true);
            BOOST_CHECK_EQUAL(static_cast<bool>(expr2.calculate()), true);
            BOOST_CHECK_EQUAL(static_cast<bool>(expr3.calculate()), true);
            BOOST_CHECK_EQUAL(static_cast<bool>(expr4.calculate()), false);
        }

        BOOST_AUTO_TEST_CASE(GivenTwoVecValues_LessOrEqualThrows) {
            Variable var1 = Variable({1, 1});
            Variable var2 = Variable({2, 2});

            RelationExpr expr1(make_unique<BaseMathExpr>(make_unique<Variable>(var1)),
                               RelationExpr::OperatorType::LessOrEqual,
                               make_unique<BaseMathExpr>(make_unique<Variable>(var1)));

            RelationExpr expr2(make_unique<BaseMathExpr>(make_unique<Variable>(var1)),
                               RelationExpr::OperatorType::LessOrEqual,
                               make_unique<BaseMathExpr>(make_unique<Variable>(var2)));

            RelationExpr expr3(make_unique<BaseMathExpr>(make_unique<Variable>(var2)),
                               RelationExpr::OperatorType::LessOrEqual,
                               make_unique<BaseMathExpr>(make_unique<Variable>(var2)));

            Variable temp;
            BOOST_CHECK_THROW(temp=expr1.calculate(), vecc::MathException);
            BOOST_CHECK_THROW(temp=expr2.calculate(), vecc::MathException);
            BOOST_CHECK_THROW(temp=expr3.calculate(), vecc::MathException);
        }

    BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()