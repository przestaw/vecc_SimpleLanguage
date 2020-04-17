//
// Created by przemek on 01.04.2020.
//

#include <boost/test/unit_test.hpp>
#include <AST/general/context.h>
#include <error/exeception.h>

using namespace vecc;

BOOST_AUTO_TEST_SUITE(AST_Test_Suite)

    BOOST_AUTO_TEST_SUITE(Context_Test_Suite)

        BOOST_AUTO_TEST_CASE(EmptyContext_IsEmpty_1) {
            Context context;

            BOOST_CHECK_EQUAL(false, context.existVariable("a"));
            BOOST_CHECK_EQUAL(false, context.existVariable("kotek"));
        }

        BOOST_AUTO_TEST_CASE(EmptyContext_IsEmpty_2) {
            Context context;

            BOOST_CHECK_THROW(context.findVariable("a", Token()), UndefinedVar);
            BOOST_CHECK_THROW(context.findVariable("varia", Token()), UndefinedVar);
        }

        BOOST_AUTO_TEST_CASE(VariableIsAddedToContext_VariableIsReturned) {
            Context context;

            BOOST_REQUIRE_EQUAL(false, context.existVariable("kotek"));

            context.addVariable("kotek", Variable({3,-3,4}));

            BOOST_CHECK_EQUAL(true, context.existVariable("kotek"));
            BOOST_CHECK_EQUAL(true, static_cast<bool>(*context.findVariable("kotek", Token()) == Variable({3,-3,4})));
        }

        BOOST_AUTO_TEST_CASE(VariableIsAddedToParentContext_VariableIsReturned_1) {
            Context context;

            BOOST_REQUIRE_EQUAL(false, context.existVariable("kotek"));

            context.addVariable("kotek", Variable({3,-3,4}));

            BOOST_REQUIRE_EQUAL(true, context.existVariable("kotek"));

            Context childContext(context);

            BOOST_CHECK_EQUAL(true, childContext.existVariable("kotek"));
            BOOST_CHECK_EQUAL(true, static_cast<bool>(*childContext.findVariable("kotek", Token()) == Variable({3,-3,4})));
        }

        BOOST_AUTO_TEST_CASE(VariableIsAddedToParentContext_VariableIsReturned_2) {
            Context context;

            BOOST_REQUIRE_EQUAL(false, context.existVariable("kotek"));

            context.addVariable("kotek", Variable({3,-3,4}));

            BOOST_REQUIRE_EQUAL(true, context.existVariable("kotek"));

            Context childContext;

            BOOST_CHECK_EQUAL(false, childContext.existVariable("kotek"));

            childContext.setParentContext(&context);

            BOOST_CHECK_EQUAL(true, childContext.existVariable("kotek"));
            BOOST_CHECK_EQUAL(true, static_cast<bool>(*childContext.findVariable("kotek", Token()) == Variable({3,-3,4})));
        }

    BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()