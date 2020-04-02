//
// Created by przemek on 01.04.2020.
//
#include <boost/test/unit_test.hpp>
#include <AST/statement/while_stmt.h>
#include <AST/statement/assign_stmt.h>
#include <AST/expression/realtion_expr.h>
#include <AST/expression/base_math_expr.h>
#include <AST/expression/additive_expr.h>
#include <AST/statement/return_stmt.h>

using namespace vecc;

BOOST_AUTO_TEST_SUITE(AST_Test_Suite)

    BOOST_AUTO_TEST_SUITE(While_Stmt_Test_Suite)

        BOOST_AUTO_TEST_CASE(While_ExecutesAddition) {
            auto var1 = std::make_shared<Variable>(Variable({1}));
            auto var2 = std::make_shared<Variable>(Variable({10}));
            auto cond = std::make_unique<RelationExpr>(
                    std::make_unique<BaseMathExpr>(var1),
                    RelationExpr::OperatorType::Less,
                    std::make_unique<BaseMathExpr>(var2));

            WhileStatement whileStmt(std::move(cond));

            auto addExpr = std::make_unique<AddExpr>(std::make_unique<BaseMathExpr>(var1));
            addExpr->addOperand(std::make_unique<BaseMathExpr>(
                    Variable({1})),
                    AddExpr::OperatorType::Add);

            whileStmt.getWhileBody().addInstruction(
                    std::make_unique<AssignStatement>(
                            *var1,
                            std::move(addExpr)));

            BOOST_CHECK_EQUAL(true, whileStmt.run().type_ == Return::Type::Noting);
            BOOST_CHECK_EQUAL(true, static_cast<bool>(*var1 == *var2));
            BOOST_CHECK_EQUAL(true, static_cast<bool>(*var1 == Variable({10})));
        }

        BOOST_AUTO_TEST_CASE(While_ExecutesSubstract) {
            auto var1 = std::make_shared<Variable>(Variable({10}));
            auto var2 = std::make_shared<Variable>(Variable({1}));
            auto cond = std::make_unique<RelationExpr>(
                    std::make_unique<BaseMathExpr>(var1),
                    RelationExpr::OperatorType::Greater,
                    std::make_unique<BaseMathExpr>(var2));

            WhileStatement whileStmt(std::move(cond));

            auto addExpr = std::make_unique<AddExpr>(std::make_unique<BaseMathExpr>(var1));
            addExpr->addOperand(std::make_unique<BaseMathExpr>(
                    Variable({1})),
                                AddExpr::OperatorType::Substract);

            whileStmt.getWhileBody().addInstruction(
                    std::make_unique<AssignStatement>(
                            *var1,
                            std::move(addExpr)));

            BOOST_CHECK_EQUAL(true, whileStmt.run().type_ == Return::Type::Noting);
            BOOST_CHECK_EQUAL(true, static_cast<bool>(*var1 == *var2));
            BOOST_CHECK_EQUAL(true, static_cast<bool>(*var1 == Variable({1})));
        }

        BOOST_AUTO_TEST_CASE(While_BrakesOnReturn) {
            auto var1 = std::make_shared<Variable>(Variable({10}));
            auto var2 = std::make_shared<Variable>(Variable({1}));
            auto cond = std::make_unique<RelationExpr>(
                    std::make_unique<BaseMathExpr>(var1),
                    RelationExpr::OperatorType::Greater,
                    std::make_unique<BaseMathExpr>(var2));

            WhileStatement whileStmt(std::move(cond));

            whileStmt.getWhileBody().addInstruction(
                    std::make_unique<ReturnStatement>(std::make_unique<BaseMathExpr>(Variable({123}))));

            auto addExpr = std::make_unique<AddExpr>(std::make_unique<BaseMathExpr>(var1));
            addExpr->addOperand(std::make_unique<BaseMathExpr>(
                    Variable({1})),
                                AddExpr::OperatorType::Substract);

            whileStmt.getWhileBody().addInstruction(
                    std::make_unique<AssignStatement>(
                            *var1,
                            std::move(addExpr)));
            BOOST_CHECK_EQUAL(true, static_cast<bool>(*var1 == Variable({10})));
            BOOST_CHECK_EQUAL(true, static_cast<bool>(*var2 == Variable({1})));
            BOOST_REQUIRE_EQUAL(true, whileStmt.run().type_ == Return::Type::Value);
            BOOST_CHECK_EQUAL(true, static_cast<bool>(whileStmt.run().variable_ == Variable({123})));
        }

    BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()