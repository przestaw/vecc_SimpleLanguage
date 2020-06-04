//
// Created by przemek on 31.03.2020.
//

#include <boost/test/unit_test.hpp>
#include <parser/parser.h>

using namespace vecc;
using namespace vecc::error;
using namespace vecc::ast;

BOOST_AUTO_TEST_SUITE(Parser_Test_Suite)

BOOST_AUTO_TEST_CASE(EmptyParser_Throws) {
  Parser parser;

  BOOST_CHECK_THROW(parser.parse(), NoInputStream);
}

BOOST_AUTO_TEST_CASE(EmptyStreamInParser_DoesNotThrow) {
  std::stringstream stream;
  Parser parser = Parser(std::make_unique<Reader>(stream));

  parser.parse();
}

BOOST_AUTO_TEST_SUITE(Invalid_Examples_Test_Suite)

BOOST_AUTO_TEST_CASE(NoFunctionDef_ParserGivenVar_Throws) {
  std::stringstream stream;
  stream << " var\n";
  Parser parser = Parser(std::make_unique<Reader>(stream));

  BOOST_CHECK_THROW(parser.parse(), UnexpectedToken);
}

BOOST_AUTO_TEST_CASE(NoFunctionDef_ParserGivenVec_Throws) {
  std::stringstream stream;
  stream << "\nvec(1,2)";
  Parser parser = Parser(std::make_unique<Reader>(stream));

  BOOST_CHECK_THROW(parser.parse(), UnexpectedToken);
}

BOOST_AUTO_TEST_CASE(NoFunctionDef_ParserGivenWhile_Throws) {
  std::stringstream stream;
  stream << " while(1){}";
  Parser parser = Parser(std::make_unique<Reader>(stream));

  BOOST_CHECK_THROW(parser.parse(), UnexpectedToken);
}

BOOST_AUTO_TEST_CASE(NoFunctionDef_ParserGivenJustFunKeyword_Throws) {
  std::stringstream stream;
  stream << "fun";
  Parser parser = Parser(std::make_unique<Reader>(stream));

  BOOST_CHECK_THROW(parser.parse(), UnexpectedToken);
}

BOOST_AUTO_TEST_CASE(
    InvalidFunctionDef_ParserGivenNoNameAndParenthesis_Throws) {
  std::stringstream stream;
  stream << "fun{}";
  Parser parser = Parser(std::make_unique<Reader>(stream));

  BOOST_CHECK_THROW(parser.parse(), UnexpectedToken);
}

BOOST_AUTO_TEST_CASE(
    InvalidFunctionDef_ParserGivenNoParenthesisAndBody_Throws) {
  std::stringstream stream;
  stream << "fun main";
  Parser parser = Parser(std::make_unique<Reader>(stream));

  BOOST_CHECK_THROW(parser.parse(), UnexpectedToken);
}

BOOST_AUTO_TEST_CASE(InvalidFunctionDef_ParserGivenFunNoBody_Throws) {
  std::stringstream stream;
  stream << "fun main()";
  Parser parser = Parser(std::make_unique<Reader>(stream));

  BOOST_CHECK_THROW(parser.parse(), UnexpectedToken);
}

BOOST_AUTO_TEST_CASE(InvalidFunctionDef_ParserGivenFunWithArgsNoBody_Throws) {
  std::stringstream stream;
  stream << "fun main(a, f)";
  Parser parser = Parser(std::make_unique<Reader>(stream));

  BOOST_CHECK_THROW(parser.parse(), UnexpectedToken);
}

BOOST_AUTO_TEST_CASE(
    InvalidFunctionDef_ParserGivenFunWithNoCurlyBracketClose_Throws) {
  std::stringstream stream;
  stream << "fun main(){";
  Parser parser = Parser(std::make_unique<Reader>(stream));

  BOOST_CHECK_THROW(parser.parse(), UnexpectedToken);
}

BOOST_AUTO_TEST_CASE(
    InvalidFunctionDef_ParserGivenSquareInsteadOfCurly_Throws) {
  std::stringstream stream;
  stream << "fun main()[]";
  Parser parser = Parser(std::make_unique<Reader>(stream));

  BOOST_CHECK_THROW(parser.parse(), UnexpectedToken);
}

BOOST_AUTO_TEST_CASE(
    InvalidFunctionDef_ParserGivenSquareInsteadOfParenthesis_Throws) {
  std::stringstream stream;
  stream << "fun main[]{}";
  Parser parser = Parser(std::make_unique<Reader>(stream));

  BOOST_CHECK_THROW(parser.parse(), UnexpectedToken);
}

BOOST_AUTO_TEST_CASE(NoMainFunction_Throws) {
  std::stringstream stream;
  stream << "fun kotek(a,b,c){}";
  Parser parser = Parser(std::make_unique<Reader>(stream));

  std::unique_ptr<Program> program;
  parser.parse();
  program = parser.getProgram();

  BOOST_CHECK_THROW(program->run(), UndefinedMain);
}

BOOST_AUTO_TEST_CASE(InvalidVariableInit_ParserGivenNoName_Throws) {
  // no identifier
  std::stringstream stream;
  stream << "fun func() {"
            "var;"
            "}";
  Parser parser = Parser(std::make_unique<Reader>(stream));

  BOOST_CHECK_THROW(parser.parse(), UnexpectedToken);
}

BOOST_AUTO_TEST_CASE(InvalidVariableInit_ParserGivenNoSemicolon_Throws) {
  // no semicolon
  std::stringstream stream;
  stream << "fun func() {"
            "var a"
            "}";
  Parser parser = Parser(std::make_unique<Reader>(stream));

  BOOST_CHECK_THROW(parser.parse(), UnexpectedToken);
}

BOOST_AUTO_TEST_CASE(InvalidVariableInit_ParserGivenNoVal_Throws) {
  // no value ;
  std::stringstream stream;
  stream << "fun func() {"
            "var a =;"
            "}";
  Parser parser = Parser(std::make_unique<Reader>(stream));

  BOOST_CHECK_THROW(parser.parse(), UnexpectedToken);
}

BOOST_AUTO_TEST_CASE(
    InvalidVariableInit_ParserGivenValWithoutSemicolon_Throws) {
  // no semicolon
  std::stringstream stream;
  stream << "fun func() {"
            "var a = 2"
            "}";
  Parser parser = Parser(std::make_unique<Reader>(stream));

  BOOST_CHECK_THROW(parser.parse(), UnexpectedToken);
}

BOOST_AUTO_TEST_CASE(VariableRedefinition_Throws) {
  std::stringstream stream;
  stream << "fun main() {"
            "var a = 2;"
            "var a;"
            "}";
  Parser parser = Parser(std::make_unique<Reader>(stream));

  std::unique_ptr<Program> program;
  BOOST_CHECK_THROW(parser.parse(), RedefinedVar);
}

BOOST_AUTO_TEST_CASE(InvalidRelationExpr_ParserGivenKeywor_Throws) {
  std::stringstream stream;
  stream << "fun main() {"
            "12 > var;"
            "}";
  Parser parser = Parser(std::make_unique<Reader>(stream));

  BOOST_CHECK_THROW(parser.parse(), UnexpectedToken);
}

BOOST_AUTO_TEST_CASE(InvalidRelationExpr_ParserGivenNoSecondOperand_Throws) {
  std::stringstream stream;
  stream << "fun main() {"
            "12 ==;"
            "}";
  Parser parser = Parser(std::make_unique<Reader>(stream));

  BOOST_CHECK_THROW(parser.parse(), UnexpectedToken);
}

BOOST_AUTO_TEST_CASE(NotClosedStmtBlock_Throws) {
  std::stringstream stream;
  stream << "fun main() {"
            "{ var a;"
            "}";
  Parser parser = Parser(std::make_unique<Reader>(stream));

  BOOST_CHECK_THROW(parser.parse(), UnexpectedToken);
}

BOOST_AUTO_TEST_CASE(InvalidVec_ParserGivenNoValues_Throws) {
  std::stringstream stream;
  stream << "fun main() {"
            "  var a = vec();"
            "}";
  Parser parser = Parser(std::make_unique<Reader>(stream));

  BOOST_CHECK_THROW(parser.parse(), UnexpectedToken);
}

BOOST_AUTO_TEST_CASE(InvalidVec_ParserGivenSingleValue_Throws) {
  std::stringstream stream;
  stream << "fun main() {"
            "  var a = vec(1);"
            "}";
  Parser parser = Parser(std::make_unique<Reader>(stream));

  BOOST_CHECK_THROW(parser.parse(), UnexpectedToken);
}

BOOST_AUTO_TEST_CASE(InvalidVec_Throws) {
  std::stringstream stream;
  stream << "fun main() {"
            "  var a = vec(1 2);"
            "}";
  Parser parser = Parser(std::make_unique<Reader>(stream));

  BOOST_CHECK_THROW(parser.parse(), UnexpectedToken);
}

BOOST_AUTO_TEST_CASE(InvalidVec_ParserGivenNoSecondVal_Throws) {
  std::stringstream stream;
  stream << "fun main() {"
            "  var a = vec(1, );"
            "}";
  Parser parser = Parser(std::make_unique<Reader>(stream));

  BOOST_CHECK_THROW(parser.parse(), UnexpectedToken);
}

BOOST_AUTO_TEST_CASE(InvalidIf_ParserGivenNoStmtBlock_Throws) {
  std::stringstream stream;
  stream << "fun func() {"
            "if(1)";
  Parser parser = Parser(std::make_unique<Reader>(stream));

  BOOST_CHECK_THROW(parser.parse(), UnexpectedToken);
}

BOOST_AUTO_TEST_CASE(InvalidIf_ParserGivenNoCond_Throws) {
  std::stringstream stream;
  stream << "fun func() {"
            "if(){}"
            "}";
  Parser parser = Parser(std::make_unique<Reader>(stream));

  BOOST_CHECK_THROW(parser.parse(), UnexpectedToken);
}

BOOST_AUTO_TEST_CASE(InvalidIf_ParserGivenNotClosedStmtBlock_Throws) {
  std::stringstream stream;
  stream << "fun func() {"
            "if(2 > 1){"
            "}";
  Parser parser = Parser(std::make_unique<Reader>(stream));

  BOOST_CHECK_THROW(parser.parse(), UnexpectedToken);
}

BOOST_AUTO_TEST_CASE(InvalidIf_ParserGivenElseWithoutStmtBlock_Throws) {
  std::stringstream stream;
  stream << "fun func() {"
            "if(1){}"
            "else"
            "}";
  Parser parser = Parser(std::make_unique<Reader>(stream));

  BOOST_CHECK_THROW(parser.parse(), UnexpectedToken);
}

BOOST_AUTO_TEST_CASE(InvalidWhile_ParserGivenNoWhileBody_Throws) {
  std::stringstream stream;
  stream << "fun func() {"
            "while(1)"
            "}";
  Parser parser = Parser(std::make_unique<Reader>(stream));

  BOOST_CHECK_THROW(parser.parse(), UnexpectedToken);
}

BOOST_AUTO_TEST_CASE(InvalidWhile_ParserGivenNoCondParentesis_Throws) {
  std::stringstream stream;
  stream << "fun func() {"
            "while{"
            "}"
            "}";
  Parser parser = Parser(std::make_unique<Reader>(stream));

  BOOST_CHECK_THROW(parser.parse(), UnexpectedToken);
}

BOOST_AUTO_TEST_CASE(InvalidWhile_ParserGivenNoCond_Throws) {
  std::stringstream stream;
  stream << "fun func() {"
            "while(){"
            "}"
            "}";
  Parser parser = Parser(std::make_unique<Reader>(stream));

  BOOST_CHECK_THROW(parser.parse(), UnexpectedToken);
}

BOOST_AUTO_TEST_CASE(
    InvalidFunctionCall_ParserGivenCallWithMismachedArgs_Throws) {
  std::stringstream stream;
  stream << "fun func() {"
            "}"
            "fun main(){"
            "func(1,23);"
            "}";
  Parser parser = Parser(std::make_unique<Reader>(stream));

  std::unique_ptr<Program> program;
  BOOST_CHECK_THROW(parser.parse(), MismatchedArgumentsCount);
}

BOOST_AUTO_TEST_CASE(
    InvalidFunctionCall_ParserGivenCallWithMissingArgs_Throws) {
  std::stringstream stream;
  stream << "fun func(a,b) {"
            "}"
            "fun main(){"
            "func();"
            "}";
  Parser parser = Parser(std::make_unique<Reader>(stream));

  std::unique_ptr<Program> program;
  BOOST_CHECK_THROW(parser.parse(), MismatchedArgumentsCount);
}

BOOST_AUTO_TEST_CASE(InvalidMath_ParserGivenPlusWithoutOperand_Throws) {
  std::stringstream stream;
  stream << "fun main(){"
            "var a = 1+;"
            "}";
  Parser parser = Parser(std::make_unique<Reader>(stream));

  BOOST_CHECK_THROW(parser.parse(), UnexpectedToken);
}

BOOST_AUTO_TEST_CASE(InvalidMath_ParserGivenMinusWithoutOperand_Throws) {
  std::stringstream stream;
  stream << "fun main(){"
            "var a = 1-;"
            "}";
  Parser parser = Parser(std::make_unique<Reader>(stream));

  BOOST_CHECK_THROW(parser.parse(), UnexpectedToken);
}

BOOST_AUTO_TEST_CASE(InvalidMath_ParserGivenMultiplyWithoutOperand_Throws) {
  std::stringstream stream;
  stream << "fun main(){"
            "var a = 1*;"
            "}";
  Parser parser = Parser(std::make_unique<Reader>(stream));

  BOOST_CHECK_THROW(parser.parse(), UnexpectedToken);
}

BOOST_AUTO_TEST_CASE(InvalidMath_ParserGivenDivisionWithoutOperand_Throws) {
  std::stringstream stream;
  stream << "fun main(){"
            "var a = 1/;"
            "}";
  Parser parser = Parser(std::make_unique<Reader>(stream));

  BOOST_CHECK_THROW(parser.parse(), UnexpectedToken);
}

BOOST_AUTO_TEST_CASE(InvalidMath_ParserGivenModuloWithoutOperand_Throws) {
  std::stringstream stream;
  stream << "fun main(){"
            "var a = 1%;"
            "}";
  Parser parser = Parser(std::make_unique<Reader>(stream));

  BOOST_CHECK_THROW(parser.parse(), UnexpectedToken);
}

BOOST_AUTO_TEST_CASE(InvalidMath_ParserGivenMissingParentesisClose_Throws) {
  std::stringstream stream;
  stream << "fun main(){"
            "var a = (1*(5/3);"
            "}";
  Parser parser = Parser(std::make_unique<Reader>(stream));

  BOOST_CHECK_THROW(parser.parse(), UnexpectedToken);
}

BOOST_AUTO_TEST_CASE(InvalidMath_ParserGivenMissingOperand_Throws) {
  std::stringstream stream;
  stream << "fun main(){"
            "var a = (1*(5/3)+);"
            "}";
  Parser parser = Parser(std::make_unique<Reader>(stream));

  BOOST_CHECK_THROW(parser.parse(), UnexpectedToken);
}

BOOST_AUTO_TEST_CASE(InvalidMath_ParserGivenMissingParentesisOpen_Throws) {
  std::stringstream stream;
  stream << "fun main(){"
            "var a = 1*(5+3)%9);"
            "}";
  Parser parser = Parser(std::make_unique<Reader>(stream));

  BOOST_CHECK_THROW(parser.parse(), UnexpectedToken);
}

BOOST_AUTO_TEST_CASE(InvalidVecMath_ParserGivenMissingOperand_Throws) {
  std::stringstream stream;
  stream << "fun main(){"
            "var a = vec(1,2)+vec(1,2)-;"
            "}";
  Parser parser = Parser(std::make_unique<Reader>(stream));

  BOOST_CHECK_THROW(parser.parse(), UnexpectedToken);
}

BOOST_AUTO_TEST_CASE(InvalidAndLogic_ParserGivenMissingRightOperand_Throws) {
  std::stringstream stream;
  stream << "fun main(){"
            "if(1 and){}"
            "}";
  Parser parser = Parser(std::make_unique<Reader>(stream));

  BOOST_CHECK_THROW(parser.parse(), UnexpectedToken);
}

BOOST_AUTO_TEST_CASE(InvalidLogic_ParserGivenMissingLeftOperand_Throws) {
  std::stringstream stream;
  stream << "fun main(){"
            "if(and 4){}"
            "}";
  Parser parser = Parser(std::make_unique<Reader>(stream));

  BOOST_CHECK_THROW(parser.parse(), UnexpectedToken);
}

BOOST_AUTO_TEST_CASE(InvalidOrLogic_ParserGivenMissingLeftOperand_Throws) {
  std::stringstream stream;
  stream << "fun main(){"
            "if(1 or){}"
            "}";
  Parser parser = Parser(std::make_unique<Reader>(stream));

  BOOST_CHECK_THROW(parser.parse(), UnexpectedToken);
}

BOOST_AUTO_TEST_CASE(InvalidLogic_ParserGivenMissingRightOperand_Throws) {
  std::stringstream stream;
  stream << "fun main(){"
            "if(or !4){}"
            "}";
  Parser parser = Parser(std::make_unique<Reader>(stream));

  BOOST_CHECK_THROW(parser.parse(), UnexpectedToken);
}

BOOST_AUTO_TEST_CASE(InvalidPrint_Throws) {
  std::stringstream stream;
  stream << "fun main(){"
            "print(\"string\",);"
            "}";
  Parser parser = Parser(std::make_unique<Reader>(stream));

  BOOST_CHECK_THROW(parser.parse(), UnexpectedToken);
}

BOOST_AUTO_TEST_CASE(InvalidReturn_ParserGivenMissingOperand_Throws) {
  std::stringstream stream;
  stream << "fun main(){"
            "return;"
            "}";
  Parser parser = Parser(std::make_unique<Reader>(stream));

  BOOST_CHECK_THROW(parser.parse(), UnexpectedToken);
}

BOOST_AUTO_TEST_CASE(InvalidReturn_ParserGivenMissingSemicolon_Throws) {
  std::stringstream stream;
  stream << "fun func(a,b) {"
            "}"
            "fun main(){"
            "return 6"
            "}";
  Parser parser = Parser(std::make_unique<Reader>(stream));

  BOOST_CHECK_THROW(parser.parse(), UnexpectedToken);
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(Valid_Examples_Test_Suite)

BOOST_AUTO_TEST_CASE(FunctionDef_GivenFunWithoutArgs_Works) {
  std::stringstream stream;
  stream << "fun kotek(){}";
  Parser parser = Parser(std::make_unique<Reader>(stream));

  std::unique_ptr<Program> program;
  parser.parse();
  program = parser.getProgram();

  BOOST_REQUIRE_EQUAL(true, program->existFunction("kotek"));
  BOOST_CHECK_EQUAL(program->findFunction("kotek").toString(),
                    "fun kotek(){\n}");
}

BOOST_AUTO_TEST_CASE(FunctionDef_GivenFunWith3Args_Works) {
  std::stringstream stream;
  stream << "fun kotek(a,b,c){}";
  Parser parser = Parser(std::make_unique<Reader>(stream));

  std::unique_ptr<Program> program;
  parser.parse();
  program = parser.getProgram();

  BOOST_REQUIRE_EQUAL(true, program->existFunction("kotek"));
  BOOST_CHECK_EQUAL(3, program->findFunction("kotek").size());
  BOOST_CHECK_EQUAL(program->findFunction("kotek").toString(),
                    "fun kotek(a, b, c){\n}");
}

BOOST_AUTO_TEST_CASE(MultipleFunctionDef_Works) {
  std::stringstream stream;
  stream << "fun kotek(){}\n"
            "fun barka(){}\n"
            "fun karmelek(){}\n"
            "fun main(){"
            "  kotek();"
            "  barka();"
            "  karmelek();"
            "}";
  Parser parser = Parser(std::make_unique<Reader>(stream));

  std::unique_ptr<Program> program;
  parser.parse();
  program = parser.getProgram();

  BOOST_CHECK_EQUAL(true, program->existFunction("kotek"));
  BOOST_CHECK_EQUAL(true, program->existFunction("barka"));
  BOOST_CHECK_EQUAL(true, program->existFunction("karmelek"));
  BOOST_CHECK_EQUAL(true, program->existFunction("main"));
}

BOOST_AUTO_TEST_CASE(VariableDef_GivenVar_Works) {
  std::stringstream stream;
  stream << "fun main() {"
            "var a = 1;"
            "}";
  Parser parser = Parser(std::make_unique<Reader>(stream));

  std::unique_ptr<Program> program;
  parser.parse();
  program = parser.getProgram();
  BOOST_REQUIRE_EQUAL(true, program->existFunction("main"));
  BOOST_CHECK(program->findFunction("main")
                  .getFunctionBody()
                  .getContext()
                  .existVariable("a"));
  BOOST_CHECK_EQUAL(program->findFunction("main").toString(),
                    "fun main(){\na = 1;\n}");
}

BOOST_AUTO_TEST_CASE(VariableDef_GivenVarsAndAssignment_Works) {
  std::stringstream stream;
  stream << "fun main() {"
            "var b = 2;"
            "var a = b;"
            "}";
  Parser parser = Parser(std::make_unique<Reader>(stream));

  std::unique_ptr<Program> program;
  parser.parse();
  program = parser.getProgram();
  BOOST_REQUIRE_EQUAL(true, program->existFunction("main"));
  BOOST_CHECK(program->findFunction("main")
                  .getFunctionBody()
                  .getContext()
                  .existVariable("b"));
  BOOST_CHECK(program->findFunction("main")
                  .getFunctionBody()
                  .getContext()
                  .existVariable("a"));
  BOOST_CHECK_EQUAL(program->findFunction("main").toString(),
                    "fun main(){\nb = 2;\na = b;\n}");
}

BOOST_AUTO_TEST_CASE(StmtBlock_Works) {
  std::stringstream stream;
  stream << "fun main() {"
            "{"
            "var b = 2;"
            "{"
            "var a = b;"
            "}"
            "}"
            "}";
  Parser parser = Parser(std::make_unique<Reader>(stream));

  std::unique_ptr<Program> program;
  parser.parse();
  program = parser.getProgram();
  BOOST_REQUIRE_EQUAL(true, program->existFunction("main"));
  BOOST_CHECK_EQUAL(program->findFunction("main").toString(),
                    "fun main(){\n{\nb = 2;\n{\na = b;\n};\n};\n}");
}

BOOST_AUTO_TEST_CASE(Relational_InequalWorks) {
  std::stringstream stream;
  stream << "fun main() {"
            "var a = 1;"
            "if(12 != a){}"
            "}";
  Parser parser = Parser(std::make_unique<Reader>(stream));

  std::unique_ptr<Program> program;
  parser.parse();
  program = parser.getProgram();
  BOOST_REQUIRE_EQUAL(true, program->existFunction("main"));
  BOOST_CHECK_EQUAL(program->findFunction("main").toString(),
                    "fun main(){\na = 1;\nif((12 != a)){\n}else{\n};\n}");
}

BOOST_AUTO_TEST_CASE(Relational_GreaterEqualWorks) {
  std::stringstream stream;
  stream << "fun main() {"
            "var a = 1;"
            "if(12 >= a){}"
            "}";
  Parser parser = Parser(std::make_unique<Reader>(stream));

  std::unique_ptr<Program> program;
  parser.parse();
  program = parser.getProgram();
  BOOST_REQUIRE_EQUAL(true, program->existFunction("main"));
  BOOST_CHECK_EQUAL(program->findFunction("main").toString(),
                    "fun main(){\na = 1;\nif((12 >= a)){\n}else{\n};\n}");
}

BOOST_AUTO_TEST_CASE(Vec3Assignment_Works) {
  std::stringstream stream;
  stream << "fun main() {"
            "  var a = vec(-1, 0);"
            "}";
  Parser parser = Parser(std::make_unique<Reader>(stream));

  std::unique_ptr<Program> program;
  parser.parse();
  program = parser.getProgram();
  BOOST_REQUIRE_EQUAL(true, program->existFunction("main"));
  BOOST_CHECK(program->findFunction("main")
                  .getFunctionBody()
                  .getContext()
                  .existVariable("a"));
  BOOST_CHECK_EQUAL(program->findFunction("main").toString(),
                    "fun main(){\na = vec(-1, 0);\n}");
}

BOOST_AUTO_TEST_CASE(VecNoThrow_4) {
  std::stringstream stream;
  stream << "fun main() {"
            "  var a = vec(-99, 0, 22);"
            "}";
  Parser parser = Parser(std::make_unique<Reader>(stream));

  std::unique_ptr<Program> program;
  parser.parse();
  program = parser.getProgram();
  BOOST_REQUIRE_EQUAL(true, program->existFunction("main"));
  BOOST_CHECK(program->findFunction("main")
                  .getFunctionBody()
                  .getContext()
                  .existVariable("a"));
  BOOST_CHECK_EQUAL(program->findFunction("main").toString(),
                    "fun main(){\na = vec(-99, 0, 22);\n}");
}

BOOST_AUTO_TEST_CASE(IfDefWithoutElse_Works) {
  std::stringstream stream;
  stream << "fun main() {"
            "var a;"
            "if(1){"
            "  a = 2;"
            "}"
            "}";
  Parser parser = Parser(std::make_unique<Reader>(stream));

  std::unique_ptr<Program> program;
  parser.parse();
  program = parser.getProgram();
  BOOST_REQUIRE_EQUAL(true, program->existFunction("main"));
  BOOST_CHECK_EQUAL(program->findFunction("main").toString(),
                    "fun main(){\na = 0;\nif(1){\na = 2;\n}else{\n};\n}");
}

BOOST_AUTO_TEST_CASE(IfDefWithElse_Works) {
  std::stringstream stream;
  stream << "fun main() {"
            "var a;"
            "if(1){"
            "  a = 2; "
            "} else {"
            " a = 6;"
            "}"
            "}";
  Parser parser = Parser(std::make_unique<Reader>(stream));

  std::unique_ptr<Program> program;
  parser.parse();
  program = parser.getProgram();
  BOOST_REQUIRE_EQUAL(true, program->existFunction("main"));
  BOOST_CHECK_EQUAL(
      program->findFunction("main").toString(),
      "fun main(){\na = 0;\nif(1){\na = 2;\n}else{\na = 6;\n};\n}");
}

BOOST_AUTO_TEST_CASE(WhileDef_Works) {
  std::stringstream stream;
  stream << "fun main() {"
            "var a = 1;"
            "while(a == 1){"
            "  a = a * 2 + 2; "
            "}"
            "}";
  Parser parser = Parser(std::make_unique<Reader>(stream));

  std::unique_ptr<Program> program;
  parser.parse();
  program = parser.getProgram();
  BOOST_REQUIRE_EQUAL(true, program->existFunction("main"));
  BOOST_CHECK_EQUAL(
      program->findFunction("main").toString(),
      "fun main(){\na = 1;\nwhile((a == 1)){\na = ((a*2)+2);\n};\n}");
}

BOOST_AUTO_TEST_CASE(FunctionCallWithoutArgs_Works) {
  std::stringstream stream;
  stream << "fun func() {"
            "}"
            "fun main(){"
            "func();"
            "}";
  Parser parser = Parser(std::make_unique<Reader>(stream));

  std::unique_ptr<Program> program;
  parser.parse();
  program = parser.getProgram();
  BOOST_REQUIRE_EQUAL(true, program->existFunction("main"));
  BOOST_CHECK_EQUAL(program->findFunction("main").toString(),
                    "fun main(){\nfunc();\n}");
  BOOST_REQUIRE_EQUAL(true, program->existFunction("func"));
  BOOST_CHECK_EQUAL(program->findFunction("func").toString(), "fun func(){\n}");
}

BOOST_AUTO_TEST_CASE(FunctionCallWithArgs_Works) {
  std::stringstream stream;
  stream << "fun func(a,b) {"
            "}"
            "fun main(){"
            "func(1,2);"
            "}";
  Parser parser = Parser(std::make_unique<Reader>(stream));

  std::unique_ptr<Program> program;
  parser.parse();
  program = parser.getProgram();
  BOOST_REQUIRE_EQUAL(true, program->existFunction("main"));
  BOOST_CHECK_EQUAL(program->findFunction("main").toString(),
                    "fun main(){\nfunc(1, 2);\n}");
  BOOST_REQUIRE_EQUAL(true, program->existFunction("func"));
  BOOST_CHECK_EQUAL(program->findFunction("func").toString(),
                    "fun func(a, b){\n}");
}

BOOST_AUTO_TEST_CASE(Print_Works) {
  std::stringstream stream;
  stream << "fun func() {"
            "}"
            "fun main(){"
            "print(\"func = \", func());"
            "}";
  Parser parser = Parser(std::make_unique<Reader>(stream));

  std::unique_ptr<Program> program;
  parser.parse();
  program = parser.getProgram();
  BOOST_REQUIRE_EQUAL(true, program->existFunction("main"));
  BOOST_CHECK_EQUAL(program->findFunction("main").toString(),
                    "fun main(){\nprint(\"func = \", func());\n}");
}

BOOST_AUTO_TEST_CASE(MathAddition_Works) {
  std::stringstream stream;
  stream << "fun main(){"
            "var a = 1+3;"
            "}";
  Parser parser = Parser(std::make_unique<Reader>(stream));

  std::unique_ptr<Program> program;
  parser.parse();
  program = parser.getProgram();
  BOOST_REQUIRE_EQUAL(true, program->existFunction("main"));
  BOOST_CHECK_EQUAL(program->findFunction("main").toString(),
                    "fun main(){\na = (1+3);\n}");
}

BOOST_AUTO_TEST_CASE(MathMultiplication_Works) {
  std::stringstream stream;
  stream << "fun main(){"
            "var a = 1*3;"
            "}";
  Parser parser = Parser(std::make_unique<Reader>(stream));

  std::unique_ptr<Program> program;
  parser.parse();
  program = parser.getProgram();
  BOOST_REQUIRE_EQUAL(true, program->existFunction("main"));
  BOOST_CHECK_EQUAL(program->findFunction("main").toString(),
                    "fun main(){\na = (1*3);\n}");
}

BOOST_AUTO_TEST_CASE(MathModulo_Works) {
  std::stringstream stream;
  stream << "fun main(){"
            "var a = 1%3;"
            "}";
  Parser parser = Parser(std::make_unique<Reader>(stream));

  std::unique_ptr<Program> program;
  parser.parse();
  program = parser.getProgram();
  BOOST_REQUIRE_EQUAL(true, program->existFunction("main"));
  BOOST_CHECK_EQUAL(program->findFunction("main").toString(),
                    "fun main(){\na = (1%3);\n}");
}

BOOST_AUTO_TEST_CASE(MathComplexExpr_Works) {
  std::stringstream stream;
  stream << "fun main(){"
            "var b = 8;"
            "var c = 9;"
            "var a = -1*b+c;"
            "}";
  Parser parser = Parser(std::make_unique<Reader>(stream));

  std::unique_ptr<Program> program;
  parser.parse();
  program = parser.getProgram();
  BOOST_REQUIRE_EQUAL(true, program->existFunction("main"));
  BOOST_CHECK_EQUAL(program->findFunction("main").toString(),
                    "fun main(){\nb = 8;\nc = 9;\na = (((-1)*b)+c);\n}");
}

BOOST_AUTO_TEST_CASE(MathComplexParentesis_Works) {
  std::stringstream stream;
  stream << "fun main(){"
            "var b = 8;"
            "var c = 9;"
            "var a = (1*(c/b));"
            "}";
  Parser parser = Parser(std::make_unique<Reader>(stream));

  std::unique_ptr<Program> program;
  parser.parse();
  program = parser.getProgram();
  BOOST_REQUIRE_EQUAL(true, program->existFunction("main"));
  BOOST_CHECK_EQUAL(program->findFunction("main").toString(),
                    "fun main(){\nb = 8;\nc = 9;\na = (1*(c/b));\n}");
}

BOOST_AUTO_TEST_CASE(MathWithVec_Works) {
  std::stringstream stream;
  stream << "fun main(){"
            "var b = vec(1,2);"
            "var a = vec(1,2)+b-vec(1,1);"
            "}";
  Parser parser = Parser(std::make_unique<Reader>(stream));

  std::unique_ptr<Program> program;
  parser.parse();
  program = parser.getProgram();
  BOOST_REQUIRE_EQUAL(true, program->existFunction("main"));
  BOOST_CHECK_EQUAL(
      program->findFunction("main").toString(),
      "fun main(){\nb = vec(1, 2);\na = (vec(1, 2)+b-vec(1, 1));\n}");
}

BOOST_AUTO_TEST_CASE(MathWithVecAndParentesis_Works) {
  std::stringstream stream;
  stream << "fun main(){"
            "var b = vec(1,2);"
            "var a = (vec(1,2)+b)*vec(3,4);"
            "}";
  Parser parser = Parser(std::make_unique<Reader>(stream));

  std::unique_ptr<Program> program;
  parser.parse();
  program = parser.getProgram();
  BOOST_REQUIRE_EQUAL(true, program->existFunction("main"));
  BOOST_CHECK_EQUAL(
      program->findFunction("main").toString(),
      "fun main(){\nb = vec(1, 2);\na = ((vec(1, 2)+b)*vec(3, 4));\n}");
}

BOOST_AUTO_TEST_CASE(AndLogic_Works) {
  std::stringstream stream;
  stream << "fun main(){"
            "if(1 and 1){}"
            "}";
  Parser parser = Parser(std::make_unique<Reader>(stream));

  std::unique_ptr<Program> program;
  parser.parse();
  program = parser.getProgram();
  BOOST_REQUIRE_EQUAL(true, program->existFunction("main"));
  BOOST_CHECK_EQUAL(program->findFunction("main").toString(),
                    "fun main(){\nif((1 and 1)){\n}else{\n};\n}");
}

BOOST_AUTO_TEST_CASE(OrLogic_Works) {
  std::stringstream stream;
  stream << "fun main(){"
            "if(0 or !4){}"
            "}";
  Parser parser = Parser(std::make_unique<Reader>(stream));

  std::unique_ptr<Program> program;
  parser.parse();
  program = parser.getProgram();
  BOOST_REQUIRE_EQUAL(true, program->existFunction("main"));
  BOOST_CHECK_EQUAL(program->findFunction("main").toString(),
                    "fun main(){\nif((0 or (not 4))){\n}else{\n};\n}");
}

BOOST_AUTO_TEST_CASE(ComplexLogic_Works) {
  std::stringstream stream;
  stream << "fun main(){"
            "if(2 and (!vec(4, 2) or 1) ){}"
            "}";
  Parser parser = Parser(std::make_unique<Reader>(stream));

  std::unique_ptr<Program> program;
  parser.parse();
  program = parser.getProgram();
  BOOST_REQUIRE_EQUAL(true, program->existFunction("main"));
  BOOST_CHECK_EQUAL(
      program->findFunction("main").toString(),
      "fun main(){\nif((2 and ((not vec(4, 2)) or 1))){\n}else{\n};\n}");
}

BOOST_AUTO_TEST_CASE(ReturnVal_Works) {
  std::stringstream stream;
  stream << "fun main(){"
            "return 1;"
            "}";
  Parser parser = Parser(std::make_unique<Reader>(stream));

  std::unique_ptr<Program> program;
  parser.parse();
  program = parser.getProgram();
  BOOST_REQUIRE_EQUAL(true, program->existFunction("main"));
  BOOST_CHECK_EQUAL(program->findFunction("main").toString(),
                    "fun main(){\nreturn 1;\n}");
}

BOOST_AUTO_TEST_CASE(ReturnCall_Works) {
  std::stringstream stream;
  stream << "fun func() {"
            "return 1;"
            "}"
            "fun main(){"
            "return func();"
            "}";
  Parser parser = Parser(std::make_unique<Reader>(stream));

  std::unique_ptr<Program> program;
  parser.parse();
  program = parser.getProgram();
  BOOST_REQUIRE_EQUAL(true, program->existFunction("main"));
  BOOST_CHECK_EQUAL(program->findFunction("main").toString(),
                    "fun main(){\nreturn func();\n}");
}

BOOST_AUTO_TEST_CASE(ReturnVec_Works) {
  std::stringstream stream;
  stream << "fun main(){"
            "return vec(1,2,3);"
            "}";
  Parser parser = Parser(std::make_unique<Reader>(stream));

  std::unique_ptr<Program> program;
  parser.parse();
  program = parser.getProgram();
  BOOST_REQUIRE_EQUAL(true, program->existFunction("main"));
  BOOST_CHECK_EQUAL(program->findFunction("main").toString(),
                    "fun main(){\nreturn vec(1, 2, 3);\n}");
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()
