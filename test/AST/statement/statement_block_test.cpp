//
// Created by przemek on 31.03.2020.
//

#include <AST/expression/base_math_expr.h>
#include <AST/statement/assign_stmt.h>
#include <AST/statement/return_stmt.h>
#include <AST/statement/statement_block.h>
#include <boost/test/unit_test.hpp>
#include <mock_stmt.h>

using namespace vecc::test;
using namespace vecc;
using namespace vecc::ast;

BOOST_AUTO_TEST_SUITE(AST_Test_Suite)

BOOST_AUTO_TEST_SUITE(Stmt_Block_Test_Suite)

BOOST_AUTO_TEST_CASE(EmptyStmt_ReturnsNone) {
  StatementBlock stmt;

  BOOST_CHECK_EQUAL(true, Return::Type::Noting == stmt.run().type_);
}

BOOST_AUTO_TEST_CASE(AddedStmt_IsExecuted) {
  Variable before({0});
  auto variable = std::make_shared<Variable>(before);
  Variable after({3});

  StatementBlock stmt;

  stmt.addInstruction(std::make_unique<AssignStatement>(
      *variable, std::make_unique<BaseMathExpr>(BaseMathExpr(after))));

  BOOST_REQUIRE_EQUAL(*variable, before);
  stmt.run();
  BOOST_CHECK_EQUAL(*variable, after);
}

BOOST_AUTO_TEST_CASE(ReturnStmt_IsExecuted) {
  Variable var({3});
  auto variable = Variable(var);

  StatementBlock stmt;
  stmt.getContext().addVariable("vari", var);

  stmt.addInstruction(std::make_unique<ReturnStatement>(
      std::make_unique<BaseMathExpr>(stmt.findVariable("vari"))));

  BOOST_CHECK_EQUAL(variable, stmt.run().variable_);
}

BOOST_AUTO_TEST_CASE(StmtBlock_ToStingWorks) {
  StatementBlock stmt;

  stmt.addInstruction(std::make_unique<MockStmt>("stmt 1"));
  stmt.addInstruction(std::make_unique<MockStmt>("stmt 2"));
  stmt.addInstruction(std::make_unique<MockStmt>("stmt 3"));
  stmt.addInstruction(std::make_unique<MockStmt>("last stmt"));

  BOOST_CHECK_EQUAL(stmt.toString(),
                    "{\nstmt 1;\nstmt 2;\nstmt 3;\nlast stmt;\n}");
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()