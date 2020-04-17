//
// Created by przemek on 01.04.2020.
//

#include <boost/test/unit_test.hpp>
#include <AST/general/program.h>

using namespace vecc;

BOOST_AUTO_TEST_SUITE(AST_Test_Suite)

    BOOST_AUTO_TEST_SUITE(Context_Test_Suite)

        BOOST_AUTO_TEST_CASE(EmptyProgram_Throws) {
            Program program;

            BOOST_CHECK_THROW(program.run(), UndefinedMain);
        }

        BOOST_AUTO_TEST_CASE(ProgramWithoutMain_Throws) {
            Program program;

            program.addFunction(std::make_unique<Function>("kotek"));

            BOOST_CHECK_THROW(program.run(), UndefinedMain);
        }

        BOOST_AUTO_TEST_CASE(ProgramWithMain_DoesNotThrow) {
            Program program;

            program.addFunction(std::make_unique<Function>("main"));

            BOOST_CHECK_NO_THROW(program.run());
        }

        BOOST_AUTO_TEST_CASE(ProgramFindsFunction) {
            Program program;

            BOOST_CHECK_EQUAL(false, program.existFunction("kotek"));

            program.addFunction(std::make_unique<Function>("kotek"));

            BOOST_REQUIRE_EQUAL(true, program.existFunction("kotek"));

            BOOST_CHECK_EQUAL("kotek",program.findFunction("kotek").getIdentifier());
        }

    BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()