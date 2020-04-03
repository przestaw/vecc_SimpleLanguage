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

        BOOST_AUTO_TEST_CASE(InvalidRelationExpr_Throws_1) {
            std::stringstream stream;
            stream << "fun main() {"
                      "12 > var;"
                      "}";
            Parser parser(std::make_unique<Reader>(stream));

            std::unique_ptr<Program> program;
            BOOST_CHECK_THROW(parser.parse(), UnexpectedToken);
        }

        BOOST_AUTO_TEST_CASE(InvalidRelationExpr_Throws_2) {
            std::stringstream stream;
            stream << "fun main() {"
                      "12 ==;"
                      "}";
            Parser parser(std::make_unique<Reader>(stream));

            std::unique_ptr<Program> program;
            BOOST_CHECK_THROW(parser.parse(), UnexpectedToken);
        }

        BOOST_AUTO_TEST_CASE(NotClosedStmtBlock_Throws_1) {
            std::stringstream stream;
            stream << "fun main() {"
                      "{ var a;"
                      "}";
            Parser parser(std::make_unique<Reader>(stream));

            std::unique_ptr<Program> program;
            BOOST_CHECK_THROW(parser.parse(), UnexpectedToken);
        }

        BOOST_AUTO_TEST_CASE(InvalidVec_Throws_1) {
            std::stringstream stream;
            stream << "fun main() {"
                      "  var a = vec();"
                      "}";
            Parser parser(std::make_unique<Reader>(stream));

            std::unique_ptr<Program> program;
            BOOST_CHECK_THROW(parser.parse(), UnexpectedToken);
        }

        BOOST_AUTO_TEST_CASE(InvalidVec_Throws_2) {
            std::stringstream stream;
            stream << "fun main() {"
                      "  var a = vec(1);"
                      "}";
            Parser parser(std::make_unique<Reader>(stream));

            std::unique_ptr<Program> program;
            BOOST_CHECK_THROW(parser.parse(), UnexpectedToken);
        }

        BOOST_AUTO_TEST_CASE(InvalidVec_Throws_3) {
            std::stringstream stream;
            stream << "fun main() {"
                      "  var a = vec(1 2);"
                      "}";
            Parser parser(std::make_unique<Reader>(stream));

            std::unique_ptr<Program> program;
            BOOST_CHECK_THROW(parser.parse(), UnexpectedToken);
        }

        BOOST_AUTO_TEST_CASE(InvalidVec_Throws_4) {
            std::stringstream stream;
            stream << "fun main() {"
                      "  var a = vec(1, );"
                      "}";
            Parser parser(std::make_unique<Reader>(stream));

            std::unique_ptr<Program> program;
            BOOST_CHECK_THROW(parser.parse(), UnexpectedToken);
        }

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

        BOOST_AUTO_TEST_CASE(InvalidWhile_Throws_1) {
            std::stringstream stream;
            stream << "fun func() {"
                      "while(1)"
                      "}";
            Parser parser(std::make_unique<Reader>(stream));

            std::unique_ptr<Program> program;
            BOOST_CHECK_THROW(parser.parse(), UnexpectedToken);
        }

        BOOST_AUTO_TEST_CASE(InvalidWhile_Throws_2) {
            std::stringstream stream;
            stream << "fun func() {"
                      "while{"
                      "}"
                      "}";
            Parser parser(std::make_unique<Reader>(stream));

            std::unique_ptr<Program> program;
            BOOST_CHECK_THROW(parser.parse(), UnexpectedToken);
        }

        BOOST_AUTO_TEST_CASE(InvalidWhile_Throws_3) {
            std::stringstream stream;
            stream << "fun func() {"
                      "while(){"
                      "}"
                      "}";
            Parser parser(std::make_unique<Reader>(stream));

            std::unique_ptr<Program> program;
            BOOST_CHECK_THROW(parser.parse(), UnexpectedToken);
        }

        BOOST_AUTO_TEST_CASE(InvalidFunctionCall_Throws_1) {
            std::stringstream stream;
            stream << "fun func() {"
                      "}"
                      "fun main(){"
                      "func(1,23);"
                      "}";
            Parser parser(std::make_unique<Reader>(stream));

            std::unique_ptr<Program> program;
            BOOST_CHECK_THROW(parser.parse(), MismachedArgumentsCount);
        }

        BOOST_AUTO_TEST_CASE(InvalidFunctionCall_Throws_2) {
            std::stringstream stream;
            stream << "fun func(a,b) {"
                      "}"
                      "fun main(){"
                      "func(1);"
                      "}";
            Parser parser(std::make_unique<Reader>(stream));

            std::unique_ptr<Program> program;
            BOOST_CHECK_THROW(parser.parse(), MismachedArgumentsCount);
        }

        BOOST_AUTO_TEST_CASE(InvalidMath_Throws_1) {
            std::stringstream stream;
            stream << "fun main(){"
                      "var a = 1+;"
                      "}";
            Parser parser(std::make_unique<Reader>(stream));

            std::unique_ptr<Program> program;
            BOOST_CHECK_THROW(parser.parse(), UnexpectedToken);
        }

        BOOST_AUTO_TEST_CASE(InvalidMath_Throws_2) {
            std::stringstream stream;
            stream << "fun main(){"
                      "var a = 1-;"
                      "}";
            Parser parser(std::make_unique<Reader>(stream));

            std::unique_ptr<Program> program;
            BOOST_CHECK_THROW(parser.parse(), UnexpectedToken);
        }
        BOOST_AUTO_TEST_CASE(InvalidMath_Throws_3) {
            std::stringstream stream;
            stream << "fun main(){"
                      "var a = 1*;"
                      "}";
            Parser parser(std::make_unique<Reader>(stream));

            std::unique_ptr<Program> program;
            BOOST_CHECK_THROW(parser.parse(), UnexpectedToken);
        }

        BOOST_AUTO_TEST_CASE(InvalidMath_Throws_4) {
            std::stringstream stream;
            stream << "fun main(){"
                      "var a = 1/;"
                      "}";
            Parser parser(std::make_unique<Reader>(stream));

            std::unique_ptr<Program> program;
            BOOST_CHECK_THROW(parser.parse(), UnexpectedToken);
        }
        BOOST_AUTO_TEST_CASE(InvalidMath_Throws_5) {
            std::stringstream stream;
            stream << "fun main(){"
                      "var a = 1%;"
                      "}";
            Parser parser(std::make_unique<Reader>(stream));

            std::unique_ptr<Program> program;
            BOOST_CHECK_THROW(parser.parse(), UnexpectedToken);
        }

        BOOST_AUTO_TEST_CASE(InvalidMath_Throws_6) {
            std::stringstream stream;
            stream << "fun main(){"
                      "var a = 1+1*;"
                      "}";
            Parser parser(std::make_unique<Reader>(stream));

            std::unique_ptr<Program> program;
            BOOST_CHECK_THROW(parser.parse(), UnexpectedToken);
        }

        BOOST_AUTO_TEST_CASE(InvalidMath_Throws_7) {
            std::stringstream stream;
            stream << "fun main(){"
                      "var a = 1+1-;"
                      "}";
            Parser parser(std::make_unique<Reader>(stream));

            std::unique_ptr<Program> program;
            BOOST_CHECK_THROW(parser.parse(), UnexpectedToken);
        }

        BOOST_AUTO_TEST_CASE(InvalidMath_Throws_8) {
            std::stringstream stream;
            stream << "fun main(){"
                      "var a = 1-1+;"
                      "}";
            Parser parser(std::make_unique<Reader>(stream));

            std::unique_ptr<Program> program;
            BOOST_CHECK_THROW(parser.parse(), UnexpectedToken);
        }

        BOOST_AUTO_TEST_CASE(InvalidMath_Throws_9) {
            std::stringstream stream;
            stream << "fun main(){"
                      "var a = 1*1+;"
                      "}";
            Parser parser(std::make_unique<Reader>(stream));

            std::unique_ptr<Program> program;
            BOOST_CHECK_THROW(parser.parse(), UnexpectedToken);
        }

        BOOST_AUTO_TEST_CASE(InvalidMath_Throws_10) {
            std::stringstream stream;
            stream << "fun main(){"
                      "var a = 1*1/;"
                      "}";
            Parser parser(std::make_unique<Reader>(stream));

            std::unique_ptr<Program> program;
            BOOST_CHECK_THROW(parser.parse(), UnexpectedToken);
        }

        BOOST_AUTO_TEST_CASE(InvalidMath_Throws_11) {
            std::stringstream stream;
            stream << "fun main(){"
                      "var a = (1*(5/3);"
                      "}";
            Parser parser(std::make_unique<Reader>(stream));

            std::unique_ptr<Program> program;
            BOOST_CHECK_THROW(parser.parse(), UnexpectedToken);
        }

        BOOST_AUTO_TEST_CASE(InvalidMath_Throws_12) {
            std::stringstream stream;
            stream << "fun main(){"
                      "var a = (1*(5/3)+);"
                      "}";
            Parser parser(std::make_unique<Reader>(stream));

            std::unique_ptr<Program> program;
            BOOST_CHECK_THROW(parser.parse(), UnexpectedToken);
        }

        BOOST_AUTO_TEST_CASE(InvalidMath_Throws_13) {
            std::stringstream stream;
            stream << "fun main(){"
                      "var a = (1*(5/3)%9;"
                      "}";
            Parser parser(std::make_unique<Reader>(stream));

            std::unique_ptr<Program> program;
            BOOST_CHECK_THROW(parser.parse(), UnexpectedToken);
        }

        BOOST_AUTO_TEST_CASE(InvalidMath_Throws_14) {
            std::stringstream stream;
            stream << "fun main(){"
                      "var a = 1*(5+3)%9);"
                      "}";
            Parser parser(std::make_unique<Reader>(stream));

            std::unique_ptr<Program> program;
            BOOST_CHECK_THROW(parser.parse(), UnexpectedToken);
        }

        BOOST_AUTO_TEST_CASE(InvalidMath_Throws_15) {
            std::stringstream stream;
            stream << "fun main(){"
                      "var a = (1*(5/3)%9+5-%7)*(1+2);"
                      "}";
            Parser parser(std::make_unique<Reader>(stream));

            std::unique_ptr<Program> program;
            BOOST_CHECK_THROW(parser.parse(), UnexpectedToken);
        }

        BOOST_AUTO_TEST_CASE(InvalidVecMath_Throws_1) {
            std::stringstream stream;
            stream << "fun main(){"
                      "var a = vec(1,2)+vec(1,2)-;"
                      "}";
            Parser parser(std::make_unique<Reader>(stream));

            std::unique_ptr<Program> program;
            BOOST_CHECK_THROW(parser.parse(), UnexpectedToken);
        }

        BOOST_AUTO_TEST_CASE(InvalidVecMath_Throws_2) {
            std::stringstream stream;
            stream << "fun main(){"
                      "var a = (vec(1,2)+vec(1,2))-vec(3,4));"
                      "}";
            Parser parser(std::make_unique<Reader>(stream));

            std::unique_ptr<Program> program;
            BOOST_CHECK_THROW(parser.parse(), UnexpectedToken);
        }

        BOOST_AUTO_TEST_CASE(InvalidLogic_Throws_1) {
            std::stringstream stream;
            stream << "fun main(){"
                      "if(1 and){}"
                      "}";
            Parser parser(std::make_unique<Reader>(stream));

            std::unique_ptr<Program> program;
            BOOST_CHECK_THROW(parser.parse(), UnexpectedToken);
        }

        BOOST_AUTO_TEST_CASE(InvalidLogic_Throws_2) {
            std::stringstream stream;
            stream << "fun main(){"
                      "if(and 4){}"
                      "}";
            Parser parser(std::make_unique<Reader>(stream));

            std::unique_ptr<Program> program;
            BOOST_CHECK_THROW(parser.parse(), UnexpectedToken);
        }

        BOOST_AUTO_TEST_CASE(InvalidLogic_Throws_3) {
            std::stringstream stream;
            stream << "fun main(){"
                      "if(1 or){}"
                      "}";
            Parser parser(std::make_unique<Reader>(stream));

            std::unique_ptr<Program> program;
            BOOST_CHECK_THROW(parser.parse(), UnexpectedToken);
        }

        BOOST_AUTO_TEST_CASE(InvalidLogic_Throws_4) {
            std::stringstream stream;
            stream << "fun main(){"
                      "if(or !4){}"
                      "}";
            Parser parser(std::make_unique<Reader>(stream));

            std::unique_ptr<Program> program;
            BOOST_CHECK_THROW(parser.parse(), UnexpectedToken);
        }

        BOOST_AUTO_TEST_CASE(InvalidLogic_Throws_5) {
            std::stringstream stream;
            stream << "fun main(){"
                      "if(1 and 2 or ){}"
                      "}";
            Parser parser(std::make_unique<Reader>(stream));

            std::unique_ptr<Program> program;
            BOOST_CHECK_THROW(parser.parse(), UnexpectedToken);
        }

        BOOST_AUTO_TEST_CASE(InvalidLogic_Throws_6) {
            std::stringstream stream;
            stream << "fun main(){"
                      "if(2 and !4 or ){}"
                      "}";
            Parser parser(std::make_unique<Reader>(stream));

            std::unique_ptr<Program> program;
            BOOST_CHECK_THROW(parser.parse(), UnexpectedToken);
        }

        BOOST_AUTO_TEST_CASE(InvalidLogic_Throws_7) {
            std::stringstream stream;
            stream << "fun main(){"
                      "if(2 and (!4 or) ){}"
                      "}";
            Parser parser(std::make_unique<Reader>(stream));

            std::unique_ptr<Program> program;
            BOOST_CHECK_THROW(parser.parse(), UnexpectedToken);
        }

        BOOST_AUTO_TEST_CASE(InvalidLogic_Throws_8) {
            std::stringstream stream;
            stream << "fun main(){"
                      "if((1 and 2 == 3) or ){}"
                      "}";
            Parser parser(std::make_unique<Reader>(stream));

            std::unique_ptr<Program> program;
            BOOST_CHECK_THROW(parser.parse(), UnexpectedToken);
        }

        BOOST_AUTO_TEST_CASE(InvalidLogic_Throws_9) {
            std::stringstream stream;
            stream << "fun main(){"
                      "if(1 or (and 4) or 12 > 9){}"
                      "}";
            Parser parser(std::make_unique<Reader>(stream));

            std::unique_ptr<Program> program;
            BOOST_CHECK_THROW(parser.parse(), UnexpectedToken);
        }

        BOOST_AUTO_TEST_CASE(InvalidLogic_Throws_10) {
            std::stringstream stream;
            stream << "fun main(){"
                      "if(1 or (12 > 9) and !==4){}"
                      "}";
            Parser parser(std::make_unique<Reader>(stream));

            std::unique_ptr<Program> program;
            BOOST_CHECK_THROW(parser.parse(), UnexpectedToken);
        }

        BOOST_AUTO_TEST_CASE(InvalidPrint_Throws_1) {
            std::stringstream stream;
            stream << "fun main(){"
                      "print(\"string\",);"
                      "}";
            Parser parser(std::make_unique<Reader>(stream));

            std::unique_ptr<Program> program;
            BOOST_CHECK_THROW(parser.parse(), UnexpectedToken);
        }

        BOOST_AUTO_TEST_CASE(InvalidReturn_Throws_1) {
            std::stringstream stream;
            stream << "fun main(){"
                      "return;"
                      "}";
            Parser parser(std::make_unique<Reader>(stream));

            std::unique_ptr<Program> program;
            BOOST_CHECK_THROW(parser.parse(), UnexpectedToken);
        }

        BOOST_AUTO_TEST_CASE(InvalidReturn_Throws_2) {
            std::stringstream stream;
            stream << "fun func(a,b) {"
                      "}"
                      "fun main(){"
                      "return 6"
                      "}";
            Parser parser(std::make_unique<Reader>(stream));

            std::unique_ptr<Program> program;
            BOOST_CHECK_THROW(parser.parse(), UnexpectedToken);
        }

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

        BOOST_AUTO_TEST_CASE(StmtBlock_Works_1) {
            std::stringstream stream;
            stream << "fun main() {"
                      "{"
                      "var b = 2;"
                      "var a = b;"
                      "}"
                      "}";
            Parser parser(std::make_unique<Reader>(stream));

            std::unique_ptr<Program> program;
            BOOST_CHECK_NO_THROW(parser.parse());
            BOOST_CHECK_NO_THROW(program = parser.getProgram());
        }

        BOOST_AUTO_TEST_CASE(StmtBlock_Works_2) {
            std::stringstream stream;
            stream << "fun main() {"
                      "{"
                      "var b = 2;"
                      "{"
                      "var a = b;"
                      "}"
                      "}"
                      "}";
            Parser parser(std::make_unique<Reader>(stream));

            std::unique_ptr<Program> program;
            BOOST_CHECK_NO_THROW(parser.parse());
            BOOST_CHECK_NO_THROW(program = parser.getProgram());
        }

        BOOST_AUTO_TEST_CASE(Relational_Works_1) {
            std::stringstream stream;
            stream << "fun main() {"
                      "var a = 1;"
                      "if(12 == a){}"
                      "}";
            Parser parser(std::make_unique<Reader>(stream));

            std::unique_ptr<Program> program;
            BOOST_CHECK_NO_THROW(parser.parse());
            BOOST_CHECK_NO_THROW(program = parser.getProgram());
        }

        BOOST_AUTO_TEST_CASE(Relational_Works_2) {
            std::stringstream stream;
            stream << "fun main() {"
                      "var a = 1;"
                      "if(12 != a){}"
                      "}";
            Parser parser(std::make_unique<Reader>(stream));

            std::unique_ptr<Program> program;
            BOOST_CHECK_NO_THROW(parser.parse());
            BOOST_CHECK_NO_THROW(program = parser.getProgram());
        }

        BOOST_AUTO_TEST_CASE(Relational_Works_3) {
            std::stringstream stream;
            stream << "fun main() {"
                      "var a = 1;"
                      "if(12 < a){}"
                      "}";
            Parser parser(std::make_unique<Reader>(stream));

            std::unique_ptr<Program> program;
            BOOST_CHECK_NO_THROW(parser.parse());
            BOOST_CHECK_NO_THROW(program = parser.getProgram());
        }

        BOOST_AUTO_TEST_CASE(Relational_Works_4) {
            std::stringstream stream;
            stream << "fun main() {"
                      "var a = 1;"
                      "if(12 <= a){}"
                      "}";
            Parser parser(std::make_unique<Reader>(stream));

            std::unique_ptr<Program> program;
            BOOST_CHECK_NO_THROW(parser.parse());
            BOOST_CHECK_NO_THROW(program = parser.getProgram());
        }

        BOOST_AUTO_TEST_CASE(Relational_Works_5) {
            std::stringstream stream;
            stream << "fun main() {"
                      "var a = 1;"
                      "if(12 > a){}"
                      "}";
            Parser parser(std::make_unique<Reader>(stream));

            std::unique_ptr<Program> program;
            BOOST_CHECK_NO_THROW(parser.parse());
            BOOST_CHECK_NO_THROW(program = parser.getProgram());
        }

        BOOST_AUTO_TEST_CASE(Relational_Works_6) {
            std::stringstream stream;
            stream << "fun main() {"
                      "var a = 1;"
                      "if(12 >= a){}"
                      "}";
            Parser parser(std::make_unique<Reader>(stream));

            std::unique_ptr<Program> program;
            BOOST_CHECK_NO_THROW(parser.parse());
            BOOST_CHECK_NO_THROW(program = parser.getProgram());
        }

        BOOST_AUTO_TEST_CASE(VecNoThrow_1) {
            std::stringstream stream;
            stream << "fun main() {"
                      "  var a = vec(1, 1);"
                      "}";
            Parser parser(std::make_unique<Reader>(stream));

            std::unique_ptr<Program> program;
            BOOST_CHECK_NO_THROW(parser.parse());
            BOOST_CHECK_NO_THROW(program = parser.getProgram());
        }

        BOOST_AUTO_TEST_CASE(VecNoThrow_2) {
            std::stringstream stream;
            stream << "fun main() {"
                      "  var a = vec(1, 1, 2);"
                      "}";
            Parser parser(std::make_unique<Reader>(stream));

            std::unique_ptr<Program> program;
            BOOST_CHECK_NO_THROW(parser.parse());
            BOOST_CHECK_NO_THROW(program = parser.getProgram());
        }

        BOOST_AUTO_TEST_CASE(VecNoThrow_3) {
            std::stringstream stream;
            stream << "fun main() {"
                      "  var a = vec(-1, 0);"
                      "}";
            Parser parser(std::make_unique<Reader>(stream));

            std::unique_ptr<Program> program;
            (parser.parse());
            BOOST_CHECK_NO_THROW(program = parser.getProgram());
        }

        BOOST_AUTO_TEST_CASE(VecNoThrow_4) {
            std::stringstream stream;
            stream << "fun main() {"
                      "  var a = vec(-99, 0, 22);"
                      "}";
            Parser parser(std::make_unique<Reader>(stream));

            std::unique_ptr<Program> program;
            (parser.parse());
            BOOST_CHECK_NO_THROW(program = parser.getProgram());
        }

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

        BOOST_AUTO_TEST_CASE(WhileDef_Works_1) {
            std::stringstream stream;
            stream << "fun main() {"
                      "var a = 1;"
                      "while(a < 1){"
                      "  a = 2; "
                      "}"
                      "}";
            Parser parser(std::make_unique<Reader>(stream));

            std::unique_ptr<Program> program;
            BOOST_CHECK_NO_THROW(parser.parse());
            BOOST_CHECK_NO_THROW(program = parser.getProgram());
        }

        BOOST_AUTO_TEST_CASE(WhileDef_Works_2) {
            std::stringstream stream;
            stream << "fun main() {"
                      "var a = 1;"
                      "while(a == 1){"
                      "  a = a * 2 + 2; "
                      "}"
                      "}";
            Parser parser(std::make_unique<Reader>(stream));

            std::unique_ptr<Program> program;
            BOOST_CHECK_NO_THROW(parser.parse());
            BOOST_CHECK_NO_THROW(program = parser.getProgram());
        }

        BOOST_AUTO_TEST_CASE(FunctionCall_Works_1) {
            std::stringstream stream;
            stream << "fun func() {"
                      "}"
                      "fun main(){"
                      "func();"
                      "}";
            Parser parser(std::make_unique<Reader>(stream));

            std::unique_ptr<Program> program;
            BOOST_CHECK_NO_THROW(parser.parse());
            BOOST_CHECK_NO_THROW(program = parser.getProgram());
        }

        BOOST_AUTO_TEST_CASE(FunctionCall_Works_2) {
            std::stringstream stream;
            stream << "fun func(a,b) {"
                      "}"
                      "fun main(){"
                      "func(1,2);"
                      "}";
            Parser parser(std::make_unique<Reader>(stream));

            std::unique_ptr<Program> program;
            BOOST_CHECK_NO_THROW(parser.parse());
            BOOST_CHECK_NO_THROW(program = parser.getProgram());
        }

        BOOST_AUTO_TEST_CASE(Print_Works_1) {
            std::stringstream stream;
            stream << "fun func() {"
                      "}"
                      "fun main(){"
                      "print(\"func = \", func());"
                      "}";
            Parser parser(std::make_unique<Reader>(stream));

            std::unique_ptr<Program> program;
            BOOST_CHECK_NO_THROW(parser.parse());
            BOOST_CHECK_NO_THROW(program = parser.getProgram());
        }

        BOOST_AUTO_TEST_CASE(Print_Works_2) {
            std::stringstream stream;
            stream << "fun main(){"
                      "print(\"func = \", 77);"
                      "}";
            Parser parser(std::make_unique<Reader>(stream));

            std::unique_ptr<Program> program;
            BOOST_CHECK_NO_THROW(parser.parse());
            BOOST_CHECK_NO_THROW(program = parser.getProgram());
        }

        BOOST_AUTO_TEST_CASE(Math_Works_1) {
            std::stringstream stream;
            stream << "fun main(){"
                      "var a = 1+3;"
                      "}";
            Parser parser(std::make_unique<Reader>(stream));

            std::unique_ptr<Program> program;
            BOOST_CHECK_NO_THROW(parser.parse());
            BOOST_CHECK_NO_THROW(program = parser.getProgram());
        }

        BOOST_AUTO_TEST_CASE(Math_Works_2) {
            std::stringstream stream;
            stream << "fun main(){"
                      "var a = 1-3;"
                      "}";
            Parser parser(std::make_unique<Reader>(stream));

            std::unique_ptr<Program> program;
            BOOST_CHECK_NO_THROW(parser.parse());
            BOOST_CHECK_NO_THROW(program = parser.getProgram());
        }
        BOOST_AUTO_TEST_CASE(Math_Works_3) {
            std::stringstream stream;
            stream << "fun main(){"
                      "var a = 1*3;"
                      "}";
            Parser parser(std::make_unique<Reader>(stream));

            std::unique_ptr<Program> program;
            BOOST_CHECK_NO_THROW(parser.parse());
            BOOST_CHECK_NO_THROW(program = parser.getProgram());
        }

        BOOST_AUTO_TEST_CASE(Math_Works_4) {
            std::stringstream stream;
            stream << "fun main(){"
                      "var a = 1/3;"
                      "}";
            Parser parser(std::make_unique<Reader>(stream));

            std::unique_ptr<Program> program;
            BOOST_CHECK_NO_THROW(parser.parse());
            BOOST_CHECK_NO_THROW(program = parser.getProgram());
        }
        BOOST_AUTO_TEST_CASE(Math_Works_5) {
            std::stringstream stream;
            stream << "fun main(){"
                      "var a = 1%3;"
                      "}";
            Parser parser(std::make_unique<Reader>(stream));

            std::unique_ptr<Program> program;
            BOOST_CHECK_NO_THROW(parser.parse());
            BOOST_CHECK_NO_THROW(program = parser.getProgram());
        }

        BOOST_AUTO_TEST_CASE(Math_Works_6) {
            std::stringstream stream;
            stream << "fun main(){"
                      "var a = 1+1*5;"
                      "}";
            Parser parser(std::make_unique<Reader>(stream));

            std::unique_ptr<Program> program;
            BOOST_CHECK_NO_THROW(parser.parse());
            BOOST_CHECK_NO_THROW(program = parser.getProgram());
        }

        BOOST_AUTO_TEST_CASE(Math_Works_7) {
            std::stringstream stream;
            stream << "fun main(){"
                      "var a = 1+1-1;"
                      "}";
            Parser parser(std::make_unique<Reader>(stream));

            std::unique_ptr<Program> program;
            BOOST_CHECK_NO_THROW(parser.parse());
            BOOST_CHECK_NO_THROW(program = parser.getProgram());
        }

        BOOST_AUTO_TEST_CASE(Math_Works_8) {
            std::stringstream stream;
            stream << "fun main(){"
                      "var a = 1-1+6;"
                      "}";
            Parser parser(std::make_unique<Reader>(stream));

            std::unique_ptr<Program> program;
            BOOST_CHECK_NO_THROW(parser.parse());
            BOOST_CHECK_NO_THROW(program = parser.getProgram());
        }

        BOOST_AUTO_TEST_CASE(Math_Works_9) {
            std::stringstream stream;
            stream << "fun main(){"
                      "var a = -1*1+8;"
                      "}";
            Parser parser(std::make_unique<Reader>(stream));

            std::unique_ptr<Program> program;
            BOOST_CHECK_NO_THROW(parser.parse());
            BOOST_CHECK_NO_THROW(program = parser.getProgram());
        }

        BOOST_AUTO_TEST_CASE(Math_Works_10) {
            std::stringstream stream;
            stream << "fun main(){"
                      "var a = 1*1/6;"
                      "}";
            Parser parser(std::make_unique<Reader>(stream));

            std::unique_ptr<Program> program;
            BOOST_CHECK_NO_THROW(parser.parse());
            BOOST_CHECK_NO_THROW(program = parser.getProgram());
        }

        BOOST_AUTO_TEST_CASE(Math_Works_11) {
            std::stringstream stream;
            stream << "fun main(){"
                      "var a = (1*(5/3));"
                      "}";
            Parser parser(std::make_unique<Reader>(stream));

            std::unique_ptr<Program> program;
            BOOST_CHECK_NO_THROW(parser.parse());
            BOOST_CHECK_NO_THROW(program = parser.getProgram());
        }

        BOOST_AUTO_TEST_CASE(Math_Works_12) {
            std::stringstream stream;
            stream << "fun main(){"
                      "var a = (1*(5/3)+9);"
                      "}";
            Parser parser(std::make_unique<Reader>(stream));

            std::unique_ptr<Program> program;
            BOOST_CHECK_NO_THROW(parser.parse());
            BOOST_CHECK_NO_THROW(program = parser.getProgram());
        }

        BOOST_AUTO_TEST_CASE(Math_Works_13) {
            std::stringstream stream;
            stream << "fun main(){"
                      "var a = -(1*(5/3)%9);"
                      "}";
            Parser parser(std::make_unique<Reader>(stream));

            std::unique_ptr<Program> program;
            BOOST_CHECK_NO_THROW(parser.parse());
            BOOST_CHECK_NO_THROW(program = parser.getProgram());
        }

        BOOST_AUTO_TEST_CASE(Math_Works_14) {
            std::stringstream stream;
            stream << "fun main(){"
                      "var a = (1*(5+3)%9);"
                      "}";
            Parser parser(std::make_unique<Reader>(stream));

            std::unique_ptr<Program> program;
            BOOST_CHECK_NO_THROW(parser.parse());
            BOOST_CHECK_NO_THROW(program = parser.getProgram());
        }

        BOOST_AUTO_TEST_CASE(Math_Works_15) {
            std::stringstream stream;
            stream << "fun main(){"
                      "var a = (1*(5/3)%9+5%7)*(1+2);"
                      "}";
            Parser parser(std::make_unique<Reader>(stream));

            std::unique_ptr<Program> program;
            BOOST_CHECK_NO_THROW(parser.parse());
            BOOST_CHECK_NO_THROW(program = parser.getProgram());
        }
        BOOST_AUTO_TEST_CASE(VecMath_Works_1) {
            std::stringstream stream;
            stream << "fun main(){"
                      "var a = vec(1,2)+vec(1,2)-vec(1,1);"
                      "}";
            Parser parser(std::make_unique<Reader>(stream));

            std::unique_ptr<Program> program;
            BOOST_CHECK_NO_THROW(parser.parse());
            BOOST_CHECK_NO_THROW(program = parser.getProgram());
        }

        BOOST_AUTO_TEST_CASE(VecMath_Works_2) {
            std::stringstream stream;
            stream << "fun main(){"
                      "var a = (vec(1,2)+vec(1,2))-vec(3,4);"
                      "}";
            Parser parser(std::make_unique<Reader>(stream));

            std::unique_ptr<Program> program;
            BOOST_CHECK_NO_THROW(parser.parse());
            BOOST_CHECK_NO_THROW(program = parser.getProgram());
        }

        BOOST_AUTO_TEST_CASE(Logic_Works_1) {
            std::stringstream stream;
            stream << "fun main(){"
                      "if(1 and 1){}"
                      "}";
            Parser parser(std::make_unique<Reader>(stream));

            std::unique_ptr<Program> program;
            BOOST_CHECK_NO_THROW(parser.parse());
            BOOST_CHECK_NO_THROW(program = parser.getProgram());
        }

        BOOST_AUTO_TEST_CASE(Logic_Works_2) {
            std::stringstream stream;
            stream << "fun main(){"
                      "if(1> 0 and 4){}"
                      "}";
            Parser parser(std::make_unique<Reader>(stream));

            std::unique_ptr<Program> program;
            BOOST_CHECK_NO_THROW(parser.parse());
            BOOST_CHECK_NO_THROW(program = parser.getProgram());
        }

        BOOST_AUTO_TEST_CASE(Logic_Works_3) {
            std::stringstream stream;
            stream << "fun main(){"
                      "if(1 or 0){}"
                      "}";
            Parser parser(std::make_unique<Reader>(stream));

            std::unique_ptr<Program> program;
            BOOST_CHECK_NO_THROW(parser.parse());
            BOOST_CHECK_NO_THROW(program = parser.getProgram());
        }

        BOOST_AUTO_TEST_CASE(Logic_Works_4) {
            std::stringstream stream;
            stream << "fun main(){"
                      "if(0 or !4){}"
                      "}";
            Parser parser(std::make_unique<Reader>(stream));

            std::unique_ptr<Program> program;
            BOOST_CHECK_NO_THROW(parser.parse());
            BOOST_CHECK_NO_THROW(program = parser.getProgram());
        }

        BOOST_AUTO_TEST_CASE(Logic_Works_5) {
            std::stringstream stream;
            stream << "fun main(){"
                      "if(1 and 2 or 0){}"
                      "}";
            Parser parser(std::make_unique<Reader>(stream));

            std::unique_ptr<Program> program;
            BOOST_CHECK_NO_THROW(parser.parse());
            BOOST_CHECK_NO_THROW(program = parser.getProgram());
        }

        BOOST_AUTO_TEST_CASE(Logic_Works_6) {
            std::stringstream stream;
            stream << "fun main(){"
                      "if(2 and !4 or 0){}"
                      "}";
            Parser parser(std::make_unique<Reader>(stream));

            std::unique_ptr<Program> program;
            BOOST_CHECK_NO_THROW(parser.parse());
            BOOST_CHECK_NO_THROW(program = parser.getProgram());
        }

        BOOST_AUTO_TEST_CASE(Logic_Works_7) {
            std::stringstream stream;
            stream << "fun main(){"
                      "if(2 and (!4 or 1) ){}"
                      "}";
            Parser parser(std::make_unique<Reader>(stream));

            std::unique_ptr<Program> program;
            BOOST_CHECK_NO_THROW(parser.parse());
            BOOST_CHECK_NO_THROW(program = parser.getProgram());
        }

        BOOST_AUTO_TEST_CASE(Logic_Works_8) {
            std::stringstream stream;
            stream << "fun main(){"
                      "if((1 and 2 == 3) or 0){}"
                      "}";
            Parser parser(std::make_unique<Reader>(stream));

            std::unique_ptr<Program> program;
            BOOST_CHECK_NO_THROW(parser.parse());
            BOOST_CHECK_NO_THROW(program = parser.getProgram());
        }

        BOOST_AUTO_TEST_CASE(Logic_Works_9) {
            std::stringstream stream;
            stream << "fun main(){"
                      "if(1 or (0 and 4) or 12 > 9){}"
                      "}";
            Parser parser(std::make_unique<Reader>(stream));

            std::unique_ptr<Program> program;
            BOOST_CHECK_NO_THROW(parser.parse());
            BOOST_CHECK_NO_THROW(program = parser.getProgram());
        }

        BOOST_AUTO_TEST_CASE(Logic_Works_10) {
            std::stringstream stream;
            stream << "fun main(){"
                      "if(1 or (12 > 9) and !(1==4)){}"
                      "}";
            Parser parser(std::make_unique<Reader>(stream));

            std::unique_ptr<Program> program;
            BOOST_CHECK_NO_THROW(parser.parse());
            BOOST_CHECK_NO_THROW(program = parser.getProgram());
        }

        BOOST_AUTO_TEST_CASE(Return_Works_1) {
            std::stringstream stream;
            stream << "fun func() {"
                      "}"
                      "fun main(){"
                      "return 1;"
                      "}";
            Parser parser(std::make_unique<Reader>(stream));

            std::unique_ptr<Program> program;
            BOOST_CHECK_NO_THROW(parser.parse());
            BOOST_CHECK_NO_THROW(program = parser.getProgram());
        }

        BOOST_AUTO_TEST_CASE(Return_Works_2) {
            std::stringstream stream;
            stream << "fun func() {"
                      "return 1;"
                      "}"
                      "fun main(){"
                      "return func();"
                      "}";
            Parser parser(std::make_unique<Reader>(stream));

            std::unique_ptr<Program> program;
            BOOST_CHECK_NO_THROW(parser.parse());
            BOOST_CHECK_NO_THROW(program = parser.getProgram());
        }

        BOOST_AUTO_TEST_CASE(Return_Works_3) {
            std::stringstream stream;
            stream << "fun func() {"
                      "return 1;"
                      "}"
                      "fun main(){"
                      "return 12*func();"
                      "}";
            Parser parser(std::make_unique<Reader>(stream));

            std::unique_ptr<Program> program;
            BOOST_CHECK_NO_THROW(parser.parse());
            BOOST_CHECK_NO_THROW(program = parser.getProgram());
        }

        BOOST_AUTO_TEST_CASE(Return_Works_4) {
            std::stringstream stream;
            stream << "fun func() {"
                      "}"
                      "fun main(){"
                      "return !1;"
                      "}";
            Parser parser(std::make_unique<Reader>(stream));

            std::unique_ptr<Program> program;
            BOOST_CHECK_NO_THROW(parser.parse());
            BOOST_CHECK_NO_THROW(program = parser.getProgram());
        }

        BOOST_AUTO_TEST_CASE(Return_Works_5) {
            std::stringstream stream;
            stream << "fun func() {"
                      "}"
                      "fun main(){"
                      "return vec(1,2,3);"
                      "}";
            Parser parser(std::make_unique<Reader>(stream));

            std::unique_ptr<Program> program;
            BOOST_CHECK_NO_THROW(parser.parse());
            BOOST_CHECK_NO_THROW(program = parser.getProgram());
        }

    BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()