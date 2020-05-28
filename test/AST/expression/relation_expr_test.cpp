//
// Created by przemek on 27.03.2020.
//

#include <AST/expression/base_math_expr.h>
#include <AST/expression/realtion_expr.h>
#include <boost/test/unit_test.hpp>
#include <error/exeception.h>

using namespace vecc;
using namespace vecc::error;
using namespace vecc::ast;

using std::make_unique;
using std::move;
using std::unique_ptr;

BOOST_AUTO_TEST_SUITE(AST_Test_Suite)

BOOST_AUTO_TEST_SUITE(Relation_Expr_Test_Suite)

BOOST_AUTO_TEST_CASE(GivenTwoValues_EqualityReturnsCorrectValue) {
  Variable var1 = Variable({1});
  Variable var2 = Variable({2});

  RelationExpr expr1(make_unique<BaseMathExpr>(var1),
                     RelationExpr::OperatorType::Equal,
                     make_unique<BaseMathExpr>(var1));

  RelationExpr expr2(make_unique<BaseMathExpr>(var1),
                     RelationExpr::OperatorType::Equal,
                     make_unique<BaseMathExpr>(var2));

  RelationExpr expr3(make_unique<BaseMathExpr>(var2),
                     RelationExpr::OperatorType::Equal,
                     make_unique<BaseMathExpr>(var2));

  BOOST_CHECK_EQUAL(expr1.calculate(), true);
  BOOST_CHECK_EQUAL(expr2.calculate(), false);
  BOOST_CHECK_EQUAL(expr3.calculate(), true);
}

BOOST_AUTO_TEST_CASE(GivenTwoVecValues_EqualityReturnsCorrectValue) {
  Variable var1 = Variable({1, 1});
  Variable var2 = Variable({2, 2});

  RelationExpr expr1(make_unique<BaseMathExpr>(var1),
                     RelationExpr::OperatorType::Equal,
                     make_unique<BaseMathExpr>(var1));

  RelationExpr expr2(make_unique<BaseMathExpr>(var1),
                     RelationExpr::OperatorType::Equal,
                     make_unique<BaseMathExpr>(var2));

  RelationExpr expr3(make_unique<BaseMathExpr>(var2),
                     RelationExpr::OperatorType::Equal,
                     make_unique<BaseMathExpr>(var2));

  BOOST_CHECK_EQUAL(expr1.calculate(), true);
  BOOST_CHECK_EQUAL(expr2.calculate(), false);
  BOOST_CHECK_EQUAL(expr3.calculate(), true);
}

BOOST_AUTO_TEST_CASE(GivenTwoDiffrentDimVecValues_EqualityThrows) {
  Variable var1 = Variable({1, 1});
  Variable var2 = Variable({2, 2, 3});

  RelationExpr expr(make_unique<BaseMathExpr>(var1),
                    RelationExpr::OperatorType::Equal,
                    make_unique<BaseMathExpr>(var2));

  Variable temp;
  BOOST_CHECK_THROW(temp = expr.calculate(), MathException);
}

BOOST_AUTO_TEST_CASE(GivenTwoValues_InequalityReturnsCorrectValue) {
  Variable var1 = Variable({1});
  Variable var2 = Variable({2});

  RelationExpr expr1(make_unique<BaseMathExpr>(var1),
                     RelationExpr::OperatorType::NotEqual,
                     make_unique<BaseMathExpr>(var1));

  RelationExpr expr2(make_unique<BaseMathExpr>(var1),
                     RelationExpr::OperatorType::NotEqual,
                     make_unique<BaseMathExpr>(var2));

  RelationExpr expr3(make_unique<BaseMathExpr>(var2),
                     RelationExpr::OperatorType::NotEqual,
                     make_unique<BaseMathExpr>(var2));

  BOOST_CHECK_EQUAL(expr1.calculate(), false);
  BOOST_CHECK_EQUAL(expr2.calculate(), true);
  BOOST_CHECK_EQUAL(expr3.calculate(), false);
}

BOOST_AUTO_TEST_CASE(GivenTwoVecValues_InequalityReturnsCorrectValue) {
  Variable var1 = Variable({1, 1});
  Variable var2 = Variable({2, 2});

  RelationExpr expr1(make_unique<BaseMathExpr>(var1),
                     RelationExpr::OperatorType::NotEqual,
                     make_unique<BaseMathExpr>(var1));

  RelationExpr expr2(make_unique<BaseMathExpr>(var1),
                     RelationExpr::OperatorType::NotEqual,
                     make_unique<BaseMathExpr>(var2));

  RelationExpr expr3(make_unique<BaseMathExpr>(var2),
                     RelationExpr::OperatorType::NotEqual,
                     make_unique<BaseMathExpr>(var2));

  BOOST_CHECK_EQUAL(expr1.calculate(), false);
  BOOST_CHECK_EQUAL(expr2.calculate(), true);
  BOOST_CHECK_EQUAL(expr3.calculate(), false);
}

BOOST_AUTO_TEST_CASE(GivenTwoDiffrentDimVecValues_InequalityThrows) {
  Variable var1 = Variable({1, 1});
  Variable var2 = Variable({2, 2, 3});

  RelationExpr expr(make_unique<BaseMathExpr>(var1),
                    RelationExpr::OperatorType::NotEqual,
                    make_unique<BaseMathExpr>(var2));
  Variable temp;
  BOOST_CHECK_THROW(temp = expr.calculate(), MathException);
}

BOOST_AUTO_TEST_CASE(GivenTwoValues_LessReturnsCorrectValue) {
  Variable var1 = Variable({1});
  Variable var2 = Variable({2});

  RelationExpr expr1(make_unique<BaseMathExpr>(var1),
                     RelationExpr::OperatorType::Less,
                     make_unique<BaseMathExpr>(var1));

  RelationExpr expr2(make_unique<BaseMathExpr>(var1),
                     RelationExpr::OperatorType::Less,
                     make_unique<BaseMathExpr>(var2));

  RelationExpr expr3(make_unique<BaseMathExpr>(var2),
                     RelationExpr::OperatorType::Less,
                     make_unique<BaseMathExpr>(var2));

  RelationExpr expr4(make_unique<BaseMathExpr>(var2),
                     RelationExpr::OperatorType::Less,
                     make_unique<BaseMathExpr>(var1));

  BOOST_CHECK_EQUAL(expr1.calculate(), false);
  BOOST_CHECK_EQUAL(expr2.calculate(), true);
  BOOST_CHECK_EQUAL(expr3.calculate(), false);
  BOOST_CHECK_EQUAL(expr4.calculate(), false);
}

BOOST_AUTO_TEST_CASE(GivenTwoVecValues_LessThrows) {
  Variable var1 = Variable({1, 1});
  Variable var2 = Variable({2, 2});

  RelationExpr expr1(make_unique<BaseMathExpr>(var1),
                     RelationExpr::OperatorType::Less,
                     make_unique<BaseMathExpr>(var1));

  RelationExpr expr2(make_unique<BaseMathExpr>(var1),
                     RelationExpr::OperatorType::Less,
                     make_unique<BaseMathExpr>(var2));

  RelationExpr expr3(make_unique<BaseMathExpr>(var2),
                     RelationExpr::OperatorType::Less,
                     make_unique<BaseMathExpr>(var2));

  Variable temp;
  BOOST_CHECK_THROW(temp = expr1.calculate(), MathException);
  BOOST_CHECK_THROW(temp = expr2.calculate(), MathException);
  BOOST_CHECK_THROW(temp = expr3.calculate(), MathException);
}

BOOST_AUTO_TEST_CASE(GivenTwoValues_LessOrEqualReturnsCorrectValue) {
  Variable var1 = Variable({1});
  Variable var2 = Variable({2});

  RelationExpr expr1(make_unique<BaseMathExpr>(var1),
                     RelationExpr::OperatorType::LessOrEqual,
                     make_unique<BaseMathExpr>(var1));

  RelationExpr expr2(make_unique<BaseMathExpr>(var1),
                     RelationExpr::OperatorType::LessOrEqual,
                     make_unique<BaseMathExpr>(var2));

  RelationExpr expr3(make_unique<BaseMathExpr>(var2),
                     RelationExpr::OperatorType::LessOrEqual,
                     make_unique<BaseMathExpr>(var2));

  RelationExpr expr4(make_unique<BaseMathExpr>(var2),
                     RelationExpr::OperatorType::LessOrEqual,
                     make_unique<BaseMathExpr>(var1));

  BOOST_CHECK_EQUAL(expr1.calculate(), true);
  BOOST_CHECK_EQUAL(expr2.calculate(), true);
  BOOST_CHECK_EQUAL(expr3.calculate(), true);
  BOOST_CHECK_EQUAL(expr4.calculate(), false);
}

BOOST_AUTO_TEST_CASE(GivenTwoVecValues_LessOrEqualThrows) {
  Variable var1 = Variable({1, 1});
  Variable var2 = Variable({2, 2});

  RelationExpr expr1(make_unique<BaseMathExpr>(var1),
                     RelationExpr::OperatorType::LessOrEqual,
                     make_unique<BaseMathExpr>(var1));

  RelationExpr expr2(make_unique<BaseMathExpr>(var1),
                     RelationExpr::OperatorType::LessOrEqual,
                     make_unique<BaseMathExpr>(var2));

  RelationExpr expr3(make_unique<BaseMathExpr>(var2),
                     RelationExpr::OperatorType::LessOrEqual,
                     make_unique<BaseMathExpr>(var2));

  Variable temp;
  BOOST_CHECK_THROW(temp = expr1.calculate(), MathException);
  BOOST_CHECK_THROW(temp = expr2.calculate(), MathException);
  BOOST_CHECK_THROW(temp = expr3.calculate(), MathException);
}

class MockExpr : public Expression {
public:
  MockExpr(std::string name) : name_(name) {}
  Variable calculate() const override { return Variable(); }
  std::string toString() const override { return name_; };

  std::string name_;
};

BOOST_AUTO_TEST_CASE(GivenTwoVal_ToStringCorrect) {
  auto expr1 = MockExpr("e1");
  auto expr2 = MockExpr("e2");

  RelationExpr ex1(make_unique<MockExpr>(expr1),
                   RelationExpr::OperatorType::LessOrEqual,
                   make_unique<MockExpr>(expr2));
  RelationExpr ex2(make_unique<MockExpr>(expr1),
                   RelationExpr::OperatorType::Greater,
                   make_unique<MockExpr>(expr2));
  RelationExpr ex3(make_unique<MockExpr>(expr1),
                   RelationExpr::OperatorType::NotEqual,
                   make_unique<MockExpr>(expr2));

  BOOST_CHECK_EQUAL(ex1.toString(), "(e1 <= e2)");
  BOOST_CHECK_EQUAL(ex2.toString(), "(e1 > e2)");
  BOOST_CHECK_EQUAL(ex3.toString(), "(e1 != e2)");
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()