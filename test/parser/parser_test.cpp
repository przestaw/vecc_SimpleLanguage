//
// Created by przemek on 31.03.2020.
//

#include <boost/test/unit_test.hpp>
#include <parser/parser.h>

using namespace vecc;

BOOST_AUTO_TEST_SUITE(Parser_Test_Suite)

    BOOST_AUTO_TEST_CASE(EmptyParser_Throws) {
        Parser parser;

        BOOST_CHECK_THROW(parser.parse(), NoInputStream);
    }

    BOOST_AUTO_TEST_CASE(EmptyStreamInParser_DoesNotThrow) {
        std::stringstream stream;
        Parser parser(std::make_unique<Reader>(stream));

        BOOST_CHECK_NO_THROW(parser.parse());
    }

    BOOST_AUTO_TEST_SUITE(Invalid_Examples_Test_Suite)

        BOOST_AUTO_TEST_CASE(NoFunctionDef_Throws_1) {
            std::stringstream stream;
            stream << " var\n";
            Parser parser(std::make_unique<Reader>(stream));

            BOOST_CHECK_THROW(parser.parse(), UnexpectedToken);
        }

        BOOST_AUTO_TEST_CASE(NoFunctionDef_Throws_2) {
            std::stringstream stream;
            stream << "\nvec(1,2)";
            Parser parser(std::make_unique<Reader>(stream));

            BOOST_CHECK_THROW(parser.parse(), UnexpectedToken);
        }

        BOOST_AUTO_TEST_CASE(NoFunctionDef_Throws_3) {
            std::stringstream stream;
            stream << " while(1){}";
            Parser parser(std::make_unique<Reader>(stream));

            BOOST_CHECK_THROW(parser.parse(), UnexpectedToken);
        }

        BOOST_AUTO_TEST_CASE(NoFunctionDef_Throws_4) {
            std::stringstream stream;
            stream << "fun";
            Parser parser(std::make_unique<Reader>(stream));

            BOOST_CHECK_THROW(parser.parse(), UnexpectedToken);
        }

        BOOST_AUTO_TEST_CASE(InvalidFunctionDef_Throws_1) {
            std::stringstream stream;
            stream << "fun{}";
            Parser parser(std::make_unique<Reader>(stream));

            BOOST_CHECK_THROW(parser.parse(), UnexpectedToken);
        }

        BOOST_AUTO_TEST_CASE(InvalidFunctionDef_Throws_2) {
            std::stringstream stream;
            stream << "fun main";
            Parser parser(std::make_unique<Reader>(stream));

            BOOST_CHECK_THROW(parser.parse(), UnexpectedToken);
        }

        BOOST_AUTO_TEST_CASE(InvalidFunctionDef_Throws_3) {
            std::stringstream stream;
            stream << "fun main()";
            Parser parser(std::make_unique<Reader>(stream));

            BOOST_CHECK_THROW(parser.parse(), UnexpectedToken);
        }

        BOOST_AUTO_TEST_CASE(InvalidFunctionDef_Throws_4) {
            std::stringstream stream;
            stream << "fun main(a, f)";
            Parser parser(std::make_unique<Reader>(stream));

            BOOST_CHECK_THROW(parser.parse(), UnexpectedToken);
        }

        BOOST_AUTO_TEST_CASE(InvalidFunctionDef_Throws_5) {
            std::stringstream stream;
            stream << "fun main(){";
            Parser parser(std::make_unique<Reader>(stream));

            BOOST_CHECK_THROW(parser.parse(), UnexpectedToken);
        }

        BOOST_AUTO_TEST_CASE(InvalidFunctionDef_Throws_6) {
            std::stringstream stream;
            stream << "fun main(a){";
            Parser parser(std::make_unique<Reader>(stream));

            BOOST_CHECK_THROW(parser.parse(), UnexpectedToken);
        }

        BOOST_AUTO_TEST_CASE(InvalidFunctionDef_Throws_7) {
            std::stringstream stream;
            stream << "fun main()[]";
            Parser parser(std::make_unique<Reader>(stream));

            BOOST_CHECK_THROW(parser.parse(), UnexpectedToken);
        }

        BOOST_AUTO_TEST_CASE(InvalidFunctionDef_Throws_8) {
            std::stringstream stream;
            stream << "fun main[]{}";
            Parser parser(std::make_unique<Reader>(stream));

            BOOST_CHECK_THROW(parser.parse(), UnexpectedToken);
        }

        BOOST_AUTO_TEST_CASE(NoMainFunction_Throws_1) {
            std::stringstream stream;
            stream << "fun kotek(){}";
            Parser parser(std::make_unique<Reader>(stream));

            std::unique_ptr<Program> program;
            BOOST_CHECK_NO_THROW(parser.parse());
            BOOST_CHECK_NO_THROW(program = parser.getProgram());

            BOOST_CHECK_THROW(program->run(), UndefinedMain);
        }

        BOOST_AUTO_TEST_CASE(NoMainFunction_Throws_2) {
            std::stringstream stream;
            stream << "fun kotek(a,b,c){}";
            Parser parser(std::make_unique<Reader>(stream));

            std::unique_ptr<Program> program;
            BOOST_CHECK_NO_THROW(parser.parse());
            BOOST_CHECK_NO_THROW(program = parser.getProgram());

            BOOST_CHECK_THROW(program->run(), UndefinedMain);
        }

        BOOST_AUTO_TEST_CASE(InvalidVariableInit_Throws_1) {
            // no identifier
            std::stringstream stream;
            stream << "fun func() {"
                      "var"
                      "}";
            Parser parser(std::make_unique<Reader>(stream));

            std::unique_ptr<Program> program;
            BOOST_CHECK_THROW(parser.parse(), UnexpectedToken);
        }

        BOOST_AUTO_TEST_CASE(InvalidVariableInit_Throws_2) {
            // no semicolon
            std::stringstream stream;
            stream << "fun func() {"
                      "var a"
                      "}";
            Parser parser(std::make_unique<Reader>(stream));

            std::unique_ptr<Program> program;
            BOOST_CHECK_THROW(parser.parse(), UnexpectedToken);
        }

        BOOST_AUTO_TEST_CASE(InvalidVariableInit_Throws_3) {
            // no value ;
            std::stringstream stream;
            stream << "fun func() {"
                      "var a ="
                      "}";
            Parser parser(std::make_unique<Reader>(stream));

            std::unique_ptr<Program> program;
            BOOST_CHECK_THROW(parser.parse(), UnexpectedToken);
        }

        BOOST_AUTO_TEST_CASE(InvalidVariableInit_Throws_4) {
            // no semicolon
            std::stringstream stream;
            stream << "fun func() {"
                      "var a = 2"
                      "}";
            Parser parser(std::make_unique<Reader>(stream));

            std::unique_ptr<Program> program;
            BOOST_CHECK_THROW(parser.parse(), UnexpectedToken);
        }

        BOOST_AUTO_TEST_CASE(VariableRedefinition_Throws_1) {
            std::stringstream stream;
            stream << "fun main() {"
                      "var a;"
                      "var a;"
                      "}";
            Parser parser(std::make_unique<Reader>(stream));

            std::unique_ptr<Program> program;
            BOOST_CHECK_THROW(parser.parse(), RedefinedVar);
        }

        BOOST_AUTO_TEST_CASE(VariableRedefinition_Throws_2) {
            std::stringstream stream;
            stream << "fun main() {"
                      "var a = 2;"
                      "var a;"
                      "}";
            Parser parser(std::make_unique<Reader>(stream));

            std::unique_ptr<Program> program;
            BOOST_CHECK_THROW(parser.parse(), RedefinedVar);
        }

        BOOST_AUTO_TEST_CASE(VariableRedefinition_Throws_3) {
            std::stringstream stream;
            stream << "fun main() {"
                      "var a;"
                      "var a = 2;"
                      "}";
            Parser parser(std::make_unique<Reader>(stream));

            std::unique_ptr<Program> program;
            BOOST_CHECK_THROW(parser.parse(), RedefinedVar);
        }

        // TODO : logic & relation

        // TODO : code block

        // TODO : Vec & Var & =

        BOOST_AUTO_TEST_CASE(InvalidIf_Throws_1) {
            std::stringstream stream;
            stream << "fun func() {"
                      "if()";
            Parser parser(std::make_unique<Reader>(stream));

            std::unique_ptr<Program> program;
            BOOST_CHECK_THROW(parser.parse(), UnexpectedToken);
        }

        BOOST_AUTO_TEST_CASE(InvalidIf_Throws_2) {
            std::stringstream stream;
            stream << "fun func() {"
                      "if("
                      "}";
            Parser parser(std::make_unique<Reader>(stream));

            std::unique_ptr<Program> program;
            BOOST_CHECK_THROW(parser.parse(), UnexpectedToken);
        }

        BOOST_AUTO_TEST_CASE(InvalidIf_Throws_3) {
            std::stringstream stream;
            stream << "fun func() {"
                      "if(2"
                      "}";
            Parser parser(std::make_unique<Reader>(stream));

            std::unique_ptr<Program> program;
            BOOST_CHECK_THROW(parser.parse(), UnexpectedToken);
        }

        BOOST_AUTO_TEST_CASE(InvalidIf_Throws_4) {
            std::stringstream stream;
            stream << "fun func() {"
                      "if(if"
                      "}";
            Parser parser(std::make_unique<Reader>(stream));

            std::unique_ptr<Program> program;
            BOOST_CHECK_THROW(parser.parse(), UnexpectedToken);
        }

        BOOST_AUTO_TEST_CASE(InvalidIf_Throws_5) {
            std::stringstream stream;
            stream << "fun func() {"
                      "if(2)"
                      "}";
            Parser parser(std::make_unique<Reader>(stream));

            std::unique_ptr<Program> program;
            BOOST_CHECK_THROW(parser.parse(), UnexpectedToken);
        }

        BOOST_AUTO_TEST_CASE(InvalidIf_Throws_6) {
            std::stringstream stream;
            stream << "fun func() {"
                      "if(2 > 1){"
                      "}";
            Parser parser(std::make_unique<Reader>(stream));

            std::unique_ptr<Program> program;
            BOOST_CHECK_THROW(parser.parse(), UnexpectedToken);
        }

        BOOST_AUTO_TEST_CASE(InvalidIf_Throws_7) {
            std::stringstream stream;
            stream << "fun func() {"
                      "if(0){123}"
                      "}";
            Parser parser(std::make_unique<Reader>(stream));

            std::unique_ptr<Program> program;
            BOOST_CHECK_THROW(parser.parse(), UnexpectedToken);
        }

        BOOST_AUTO_TEST_CASE(InvalidIf_Throws_8) {
            std::stringstream stream;
            stream << "fun func() {"
                      "if(1){}"
                      "else"
                      "}";
            Parser parser(std::make_unique<Reader>(stream));

            std::unique_ptr<Program> program;
            BOOST_CHECK_THROW(parser.parse(), UnexpectedToken);
        }

        BOOST_AUTO_TEST_CASE(InvalidIf_Throws_9) {
            std::stringstream stream;
            stream << "fun func() {"
                      "if(1){}"
                      "else{var"
                      "}";
            Parser parser(std::make_unique<Reader>(stream));

            std::unique_ptr<Program> program;
            BOOST_CHECK_THROW(parser.parse(), UnexpectedToken);
        }

        // TODO : While

        // TODO : FunctionCall

        // TODO : Print

        // TODO : math : multiplicative & additive

        // TODO : return

    BOOST_AUTO_TEST_SUITE_END()


    BOOST_AUTO_TEST_SUITE(Valid_Examples_Test_Suite)

        BOOST_AUTO_TEST_CASE(FunctionDef_Works_1) {
            std::stringstream stream;
            stream << "fun kotek(){}";
            Parser parser(std::make_unique<Reader>(stream));

            std::unique_ptr<Program> program;
            BOOST_CHECK_NO_THROW(parser.parse());
            BOOST_CHECK_NO_THROW(program = parser.getProgram());

            BOOST_CHECK_EQUAL(true, program->existFunction("kotek"));
        }

        BOOST_AUTO_TEST_CASE(FunctionDef_Works_2) {
            std::stringstream stream;
            stream << "fun kotek(a,b,c){}";
            Parser parser(std::make_unique<Reader>(stream));

            std::unique_ptr<Program> program;
            BOOST_CHECK_NO_THROW(parser.parse());
            BOOST_CHECK_NO_THROW(program = parser.getProgram());

            BOOST_REQUIRE_EQUAL(true, program->existFunction("kotek"));

            BOOST_CHECK_EQUAL(3, program->findFunction("kotek").size());
        }

        BOOST_AUTO_TEST_CASE(MultipleFunctionDef_Works_1) {
            std::stringstream stream;
            stream << "fun kotek(){}\n"
                      "fun barka(){}\n"
                      "fun karmelek(){}\n"
                      "fun main(){"
                      "  kotek();"
                      "  barka();"
                      "  karmelek();"
                      "}";
            Parser parser(std::make_unique<Reader>(stream));

            std::unique_ptr<Program> program;
            BOOST_CHECK_NO_THROW(parser.parse());
            BOOST_CHECK_NO_THROW(program = parser.getProgram());

            BOOST_CHECK_EQUAL(true, program->existFunction("kotek"));
            BOOST_CHECK_EQUAL(true, program->existFunction("barka"));
            BOOST_CHECK_EQUAL(true, program->existFunction("karmelek"));
            BOOST_CHECK_EQUAL(true, program->existFunction("main"));
        }

        BOOST_AUTO_TEST_CASE(VariableDef_Works_1) {
            std::stringstream stream;
            stream << "fun main() {"
                      "var a;"
                      "}";
            Parser parser(std::make_unique<Reader>(stream));

            std::unique_ptr<Program> program;
            BOOST_CHECK_NO_THROW(parser.parse());
            BOOST_CHECK_NO_THROW(program = parser.getProgram());
        }

        BOOST_AUTO_TEST_CASE(VariableDef_Works_2) {
            std::stringstream stream;
            stream << "fun main() {"
                      "var a = 2;"
                      "}";
            Parser parser(std::make_unique<Reader>(stream));

            std::unique_ptr<Program> program;
            BOOST_CHECK_NO_THROW(parser.parse());
            BOOST_CHECK_NO_THROW(program = parser.getProgram());
        }

        BOOST_AUTO_TEST_CASE(VariableDef_Works_3) {
            std::stringstream stream;
            stream << "fun main() {"
                      "var b = 2;"
                      "var a = b;"
                      "}";
            Parser parser(std::make_unique<Reader>(stream));

            std::unique_ptr<Program> program;
            BOOST_CHECK_NO_THROW(parser.parse());
            BOOST_CHECK_NO_THROW(program = parser.getProgram());
        }

        // TODO : logic & relation

        // TODO : code block

        // TODO : Vec & Var & =

        BOOST_AUTO_TEST_CASE(IfDef_Works_1) {
            std::stringstream stream;
            stream << "fun main() {"
                      "var a;"
                      "if(1){"
                      "  a = 2;"
                      "}"
                      "}";
            Parser parser(std::make_unique<Reader>(stream));

            std::unique_ptr<Program> program;
            BOOST_CHECK_NO_THROW(parser.parse());
            BOOST_CHECK_NO_THROW(program = parser.getProgram());
        }

        BOOST_AUTO_TEST_CASE(IfDef_Works_2) {
            std::stringstream stream;
            stream << "fun main() {"
                      "var a;"
                      "if(1){"
                      "  a = 2; "
                      "} else {"
                      " a = 6;"
                      "}"
                      "}";
            Parser parser(std::make_unique<Reader>(stream));

            std::unique_ptr<Program> program;
            BOOST_CHECK_NO_THROW(parser.parse());
            BOOST_CHECK_NO_THROW(program = parser.getProgram());
        }

        BOOST_AUTO_TEST_CASE(IfDef_Works_3) {
            std::stringstream stream;
            stream << "fun main() {"
                      "var a = 1;"
                      "if(a < 1){"
                      "  a = 2; "
                      "} else {"
                      " a = 6;"
                      "}"
                      "}";
            Parser parser(std::make_unique<Reader>(stream));

            std::unique_ptr<Program> program;
            BOOST_CHECK_NO_THROW(parser.parse());
            BOOST_CHECK_NO_THROW(program = parser.getProgram());
        }

        // TODO : While

        // TODO : FunctionCall

        // TODO : Print

        // TODO : math : multiplicative & additive

        // TODO : return

    BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()