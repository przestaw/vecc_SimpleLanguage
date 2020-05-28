//
// Created by przemek on 01.04.2020.
//
#include <AST/expression/base_math_expr.h>
#include <AST/expression/realtion_expr.h>
#include <AST/statement/assign_stmt.h>
#include <AST/statement/if_stmt.h>
#include <AST/statement/return_stmt.h>
#include <boost/test/unit_test.hpp>
#include <mock_expr.h>
#include <mock_stmt.h>

using namespace vecc;
using namespace vecc::ast;
using namespace vecc::test;

BOOST_AUTO_TEST_SUITE(AST_Test_Suite)

BOOST_AUTO_TEST_SUITE(If_Stmt_Test_Suite)

BOOST_AUTO_TEST_CASE(IfTest_NoThrow) {
  auto cond = std::make_unique<BaseMathExpr>(Variable());

  IfStatement ifStmt(std::move(cond));

  Return temp;
  BOOST_CHECK_NO_THROW(temp = ifStmt.run());
}

BOOST_AUTO_TEST_CASE(IfTrueTest_TrueBlockRun) {
  auto var1 = Variable({1});
  auto var2 = Variable({10});
  auto cond = std::make_unique<RelationExpr>(
      std::make_unique<BaseMathExpr>(&var1), RelationExpr::OperatorType::Less,
      std::make_unique<BaseMathExpr>(&var2));

  IfStatement ifStmt(std::move(cond));

  ifStmt.falseBlock().addInstruction(std::make_unique<AssignStatement>(
      var2, std::make_unique<BaseMathExpr>(Variable({99}))));

  ifStmt.trueBlock().addInstruction(std::make_unique<AssignStatement>(
      var1, std::make_unique<BaseMathExpr>(Variable({99}))));

  BOOST_CHECK_EQUAL(true, ifStmt.run().type_ == Return::Type::Noting);
  BOOST_CHECK_EQUAL(var1, Variable({99}));
  BOOST_CHECK_EQUAL(var2, Variable({10}));
}

BOOST_AUTO_TEST_CASE(IfFalseTest_FalseBlockRun) {
  auto var1 = Variable({1});
  auto var2 = Variable({10});
  auto cond =
      std::make_unique<RelationExpr>(std::make_unique<BaseMathExpr>(&var1),
                                     RelationExpr::OperatorType::GreaterOrEqual,
                                     std::make_unique<BaseMathExpr>(&var2));

  IfStatement ifStmt(std::move(cond));

  ifStmt.falseBlock().addInstruction(std::make_unique<AssignStatement>(
      var2, std::make_unique<BaseMathExpr>(Variable({99}))));

  ifStmt.trueBlock().addInstruction(std::make_unique<AssignStatement>(
      var1, std::make_unique<BaseMathExpr>(Variable({99}))));

  BOOST_CHECK_EQUAL(true, ifStmt.run().type_ == Return::Type::Noting);
  BOOST_CHECK_EQUAL(var1, Variable({1}));
  BOOST_CHECK_EQUAL(var2, Variable({99}));
}

BOOST_AUTO_TEST_CASE(IfTrueTest_TrueBlockReturn) {
  auto cond = std::make_unique<BaseMathExpr>(Variable({1}));

  BOOST_REQUIRE_EQUAL(true, cond->calculate());

  IfStatement ifStmt(std::move(cond));

  ifStmt.trueBlock().addInstruction(std::make_unique<ReturnStatement>(
      std::make_unique<BaseMathExpr>(Variable({99}))));

  ifStmt.falseBlock().addInstruction(std::make_unique<ReturnStatement>(
      std::make_unique<BaseMathExpr>(Variable({22}))));

  BOOST_CHECK_EQUAL(true, ifStmt.run().type_ == Return::Type::Value);
  BOOST_CHECK_EQUAL(ifStmt.run().variable_, Variable({99}));
}

BOOST_AUTO_TEST_CASE(IfFalseTest_FalseBlockReturn) {
  auto cond = std::make_unique<BaseMathExpr>(Variable({0}));

  BOOST_REQUIRE_EQUAL(false, cond->calculate());

  IfStatement ifStmt(std::move(cond));

  ifStmt.trueBlock().addInstruction(std::make_unique<ReturnStatement>(
      std::make_unique<BaseMathExpr>(Variable({99}))));

  ifStmt.falseBlock().addInstruction(std::make_unique<ReturnStatement>(
      std::make_unique<BaseMathExpr>(Variable({22}))));

  BOOST_CHECK_EQUAL(true, ifStmt.run().type_ == Return::Type::Value);
  BOOST_CHECK_EQUAL(ifStmt.run().variable_, Variable({22}));
}

BOOST_AUTO_TEST_CASE(If_ToStringWorks) {
  IfStatement ifStmt(std::make_unique<MockExpr>("condition"));

  ifStmt.trueBlock().addInstruction(std::make_unique<MockStmt>("true block"));

  ifStmt.falseBlock().addInstruction(std::make_unique<MockStmt>("false block"));

  BOOST_CHECK_EQUAL(ifStmt.toString(),
                    "if(condition){\ntrue block;\n}else{\nfalse block;\n}");
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()