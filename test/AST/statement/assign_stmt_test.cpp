//
// Created by przemek on 23.03.2020.
//

#include <boost/test/unit_test.hpp>
#include <AST/statement/assign_stmt.h>
#include <AST/expression/base_math_expr.h>

using namespace vecc;

BOOST_AUTO_TEST_SUITE(AST_Test_Suite)

    BOOST_AUTO_TEST_SUITE(Assign_Stmt_Test_Suite)

        BOOST_AUTO_TEST_CASE(DummyTest) {
            Variable before({0, 1, 2});
            auto variable = std::make_shared<Variable>(before);
            Variable after({3, 3, 3});
            AssignStatement(*variable,
                    std::make_unique<BaseMathExpr>(BaseMathExpr(std::make_unique<Variable>(after))));

        }

    BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()