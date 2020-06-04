//
// Created by przemek on 01.04.2020.
//
#include <AST/expression/additive_expr.h>
#include <AST/expression/base_math_expr.h>
#include <AST/expression/realtion_expr.h>
#include <AST/statement/assign_stmt.h>
#include <AST/statement/return_stmt.h>
#include <AST/statement/while_stmt.h>
#include <boost/test/unit_test.hpp>
#include <mock_expr.h>
#include <mock_stmt.h>

using namespace vecc;
using namespace vecc::ast;
using namespace vecc::test;

BOOST_AUTO_TEST_SUITE(AST_Test_Suite)

BOOST_AUTO_TEST_SUITE(While_Stmt_Test_Suite)

BOOST_AUTO_TEST_CASE(While_ExecutesAddition) {
  auto var1 = Variable({1});
  auto var2 = Variable({10});
  auto cond = std::make_unique<RelationExpr>(
      std::make_unique<BaseMathExpr>(&var1), RelationExpr::OperatorType::Less,
      std::make_unique<BaseMathExpr>(&var2));

  WhileStatement whileStmt(std::move(cond));

  auto addExpr =
      std::make_unique<AdditiveExpr>(std::make_unique<BaseMathExpr>(&var1));
  addExpr->addOperand(std::make_unique<BaseMathExpr>(Variable({1})),
                      AdditiveExpr::OperatorType::Add);

  whileStmt.getWhileBody().addInstruction(
      std::make_unique<AssignStatement>(var1, std::move(addExpr)));

  BOOST_CHECK(whileStmt.run().type_ == Return::Type::Noting);
  BOOST_CHECK_EQUAL(var1, var2);
  BOOST_CHECK_EQUAL(var1, Variable({10}));
}

// BOOST_AUTO_TEST_CASE(While_ExecutesSubstract) {
//  auto var1 = std::make_shared<Variable>(Variable({10}));
//  auto var2 = std::make_shared<Variable>(Variable({1}));
//  auto cond = std::make_unique<RelationExpr>(
//      std::make_unique<BaseMathExpr>(var1),
//      RelationExpr::OperatorType::Greater,
//      std::make_unique<BaseMathExpr>(var2));
//
//  WhileStatement whileStmt(std::move(cond));
//
//  auto addExpr =
//      std::make_unique<AdditiveExpr>(std::make_unique<BaseMathExpr>(var1));
//  addExpr->addOperand(std::make_unique<BaseMathExpr>(Variable({1})),
//                      AdditiveExpr::OperatorType::Substract);
//
//  whileStmt.getWhileBody().addInstruction(
//      std::make_unique<AssignStatement>(*var1, std::move(addExpr)));
//
//  BOOST_CHECK(whileStmt.run().type_ == Return::Type::Noting);
//  BOOST_CHECK_EQUAL(*var1, *var2);
//  BOOST_CHECK(static_cast<bool>(*var1 == Variable({1})));
//}

BOOST_AUTO_TEST_CASE(While_BrakesOnReturn) {
  auto var1 = Variable({10});
  auto var2 = Variable({1});
  auto cond =
      std::make_unique<RelationExpr>(std::make_unique<BaseMathExpr>(&var1),
                                     RelationExpr::OperatorType::Greater,
                                     std::make_unique<BaseMathExpr>(&var2));

  WhileStatement whileStmt(std::move(cond));

  whileStmt.getWhileBody().addInstruction(std::make_unique<ReturnStatement>(
      std::make_unique<BaseMathExpr>(Variable({123}))));

  auto addExpr =
      std::make_unique<AdditiveExpr>(std::make_unique<BaseMathExpr>(var1));
  addExpr->addOperand(std::make_unique<BaseMathExpr>(Variable({1})),
                      AdditiveExpr::OperatorType::Substract);

  whileStmt.getWhileBody().addInstruction(
      std::make_unique<AssignStatement>(var1, std::move(addExpr)));
  BOOST_CHECK_EQUAL(var1, Variable({10}));
  BOOST_CHECK_EQUAL(var2, Variable({1}));
  BOOST_REQUIRE(whileStmt.run().type_ == Return::Type::Value);
  BOOST_CHECK_EQUAL(whileStmt.run().variable_, Variable({123}));
}

BOOST_AUTO_TEST_CASE(If_ToStringWorks) {
  WhileStatement whileStmt(std::make_unique<MockExpr>("condition"));

  whileStmt.getWhileBody().addInstruction(
      std::make_unique<MockStmt>("statements"));

  BOOST_CHECK_EQUAL(whileStmt.toString(), "while(condition){\nstatements;\n}");
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()