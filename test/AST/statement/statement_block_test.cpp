//
// Created by przemek on 31.03.2020.
//

#include <boost/test/unit_test.hpp>
#include <AST/statement/statement_block.h>
#include <AST/expression/base_math_expr.h>
#include <AST/statement/assign_stmt.h>
#include <AST/statement/return_stmt.h>

using namespace vecc;

BOOST_AUTO_TEST_SUITE(AST_Test_Suite)

    BOOST_AUTO_TEST_SUITE(Stmt_Block_Test_Suite)

        BOOST_AUTO_TEST_CASE(EmptyStmt_ReturnsNone) {
            StatementBlock stmt;

            BOOST_CHECK_EQUAL(true, static_cast<bool>(Return::Type::Noting == stmt.run().type_));
        }

        BOOST_AUTO_TEST_CASE(AddedStmt_IsExecuted) {
            Variable before({0});
            auto variable = std::make_shared<Variable>(before);
            Variable after({3});

            StatementBlock stmt;

            stmt.addInstruction(std::make_unique<AssignStatement>(
                    *variable, std::make_unique<BaseMathExpr>(BaseMathExpr(std::make_unique<Variable>(after)))));

            BOOST_REQUIRE_EQUAL(true, static_cast<bool>(*variable == before));
            stmt.run();
            BOOST_CHECK_EQUAL(true, static_cast<bool>(*variable == after));
        }

        BOOST_AUTO_TEST_CASE(ReturnStmt_IsExecuted) {
            Variable var({3});
            auto variable = std::make_shared<Variable>(var);

            StatementBlock stmt;
            stmt.getContext().addVariable("vari", var);

            stmt.addInstruction(std::make_unique<ReturnStatement>(std::make_unique<BaseMathExpr>(stmt.findVariable("vari"))));

            BOOST_CHECK_EQUAL(true, static_cast<bool>(*variable == stmt.run().variable_));
        }

    BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()