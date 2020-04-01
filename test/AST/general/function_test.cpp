//
// Created by przemek on 01.04.2020.
//

#include <boost/test/unit_test.hpp>
#include <AST/general/function.h>
#include <AST/statement/assign_stmt.h>
#include <AST/expression/base_math_expr.h>
#include <AST/statement/return_stmt.h>

using namespace vecc;

BOOST_AUTO_TEST_SUITE(AST_Test_Suite)

    BOOST_AUTO_TEST_SUITE(Function_Test_Suite)

        BOOST_AUTO_TEST_CASE(FunctionArgs_CorrectCount) {
            Function fun("kotek");

            BOOST_CHECK_EQUAL(0, fun.size());

            fun.addParameter("bananek");

            BOOST_CHECK_EQUAL(1, fun.size());
            BOOST_CHECK_EQUAL(true, fun.getFunctionBody().getContext().existVariable("bananek"));

            fun.addParameter("koluszki");

            BOOST_CHECK_EQUAL(2, fun.size());
            BOOST_CHECK_EQUAL(true, fun.getFunctionBody().getContext().existVariable("koluszki"));
        }

        BOOST_AUTO_TEST_CASE(EmptyFun_ReturnsNone) {
            Function fun("kotek");

            BOOST_CHECK_EQUAL(true, static_cast<bool>(Return::Type::Noting == fun.run().type_));
        }

        BOOST_AUTO_TEST_CASE(AddedStmt_IsExecuted) {
            Function fun("kotek");
            Variable before({0});
            Variable after({3});

            fun.getFunctionBody().getContext().addVariable("kotitka", before);

            fun.getFunctionBody().addInstruction(
                    std::make_unique<AssignStatement>(
                            *fun.getFunctionBody().findVariable("kotitka"),
                            std::make_unique<BaseMathExpr>(BaseMathExpr(std::make_unique<Variable>(after)))));
            fun.getFunctionBody().addInstruction(
                    std::make_unique<ReturnStatement>(
                            std::make_unique<BaseMathExpr>(fun.getFunctionBody().findVariable("kotitka"))));

            BOOST_CHECK_EQUAL(true, static_cast<bool>(*fun.getFunctionBody().findVariable("kotitka") == before));
            BOOST_CHECK_EQUAL(true, static_cast<bool>(fun.run().variable_ == after));
            BOOST_CHECK_EQUAL(true, static_cast<bool>(*fun.getFunctionBody().findVariable("kotitka") == before));
        }

        BOOST_AUTO_TEST_CASE(ArgPassedToFun_ReturnsCorrect) {
            Function fun("kotek");

            fun.addParameter("kotitka");

            fun.getFunctionBody().addInstruction(
                    std::make_unique<ReturnStatement>(
                            std::make_unique<BaseMathExpr>(fun.getFunctionBody().findVariable("kotitka"))));

            BOOST_CHECK_EQUAL(true, static_cast<bool>(Variable({5}) == fun.run({Variable({5})}).variable_));
        }

    BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()