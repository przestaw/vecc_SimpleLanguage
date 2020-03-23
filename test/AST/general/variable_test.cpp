//
// Created by przemek on 23.03.2020.
//

#include <boost/test/unit_test.hpp>
#include <AST/general/variable.h>
#include <error/exeception.h>

using vecc::Variable;
using vecc::MathException;

BOOST_AUTO_TEST_SUITE(AST_Test_Suite)

BOOST_AUTO_TEST_SUITE(Variable_Test_Suite)

    BOOST_AUTO_TEST_CASE(GivenVariables_BoolOperatorWorks) {
        Variable var0({0});
        Variable var1({2});

        Variable var2({0, 0});
        Variable var3({2, 6});
        
        BOOST_CHECK(!static_cast<bool>(var0));
        BOOST_CHECK(static_cast<bool>(var1));

        BOOST_CHECK(!static_cast<bool>(var2));
        BOOST_CHECK(static_cast<bool>(var3));
    }

    BOOST_AUTO_TEST_CASE(GivenVariables_OrOperatorWorks) {
        Variable var0({0});
        Variable var1({2});

        Variable var2({0, 0});
        Variable var3({2, 6});

        BOOST_CHECK(!static_cast<bool>(var0 || var2));
        BOOST_CHECK(static_cast<bool>(var1 || var0));
        BOOST_CHECK(static_cast<bool>(var3 || var1));
    }

    BOOST_AUTO_TEST_CASE(GivenVariables_AndOperatorWorks) {
        Variable var0({0});
        Variable var1({2});

        Variable var2({0, 0});
        Variable var3({2, 6});

        BOOST_CHECK(!static_cast<bool>(var2 && var0));
        BOOST_CHECK(!static_cast<bool>(var2 && var1));
        BOOST_CHECK(static_cast<bool>(var3 && var1));
    }

    BOOST_AUTO_TEST_CASE(GivenOneVariable_EqualityWorks) {
        Variable var1({2});

        BOOST_CHECK(static_cast<bool>(var1 == var1));
        BOOST_CHECK(!(static_cast<bool>(var1 != var1)));
    }

    BOOST_AUTO_TEST_CASE(GivenTwoVariables_EquaityWorks1) {
        Variable var1({2});
        Variable var2({2, 3});

        BOOST_CHECK(!(static_cast<bool>(var1 == var2)));
        BOOST_CHECK(!(static_cast<bool>(var2 == var1)));
    }

    BOOST_AUTO_TEST_CASE(GivenTwoVariables_InequalityWorks1) {
        Variable var1({2});
        Variable var2({2, 3});

        BOOST_CHECK(static_cast<bool>(var1 != var2));
        BOOST_CHECK(static_cast<bool>(var2 != var1));
    }

    BOOST_AUTO_TEST_CASE(GivenTwoVariables_AdditionThrows) {
        Variable var1({2});
        Variable var2({2, 3});

        BOOST_CHECK_THROW(var1 + var2, MathException);
        BOOST_CHECK_THROW(var2 + var1, MathException);
    }

    BOOST_AUTO_TEST_CASE(GivenTwoVariables_SubstractionThrows) {
        Variable var1({2});
        Variable var2({2, 3});

        BOOST_CHECK_THROW(var1 - var2, MathException);
        BOOST_CHECK_THROW(var2 - var1, MathException);
    }

    BOOST_AUTO_TEST_CASE(GivenTwoVariables_MultiplicationWorks) {
        Variable var1({2});
        Variable var2({2, 3});

        BOOST_CHECK(static_cast<bool>(var2 * var1 == Variable({4, 6})));

        BOOST_CHECK(static_cast<bool>(var1 * var2 == Variable({4, 6})));
    }

    BOOST_AUTO_TEST_CASE(GivenTwoVariables_DivisionThrows) {
        Variable var1({2});
        Variable var2({2, 3});

        BOOST_CHECK_THROW(var1 / var2, MathException);
    }


    BOOST_AUTO_TEST_CASE(GivenTwoVariables_DivisionWorks) {
        Variable var1({2});
        Variable var2({2, 4});

        BOOST_CHECK(static_cast<bool>(var2 / var1 == Variable({1, 2})));
    }

    BOOST_AUTO_TEST_CASE(GivenTwoVariables_ModuloWorks) {
        Variable var1({2});
        Variable var2({2, 3});

        BOOST_CHECK_THROW(var1 % var2, MathException);
        BOOST_CHECK(static_cast<bool>(var2 % var1 == Variable({0, 1})));
    }

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()