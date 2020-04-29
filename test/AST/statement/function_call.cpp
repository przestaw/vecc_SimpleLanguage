//
// Created by przemek on 01.04.2020.
//
#include <AST/expression/base_math_expr.h>
#include <AST/statement/assign_stmt.h>
#include <AST/statement/function_call.h>
#include <AST/statement/return_stmt.h>
#include <boost/test/unit_test.hpp>

using namespace vecc;
using namespace vecc::ast;

BOOST_AUTO_TEST_SUITE(AST_Test_Suite)

BOOST_AUTO_TEST_SUITE(Function_Call_Test_Suite)

BOOST_AUTO_TEST_CASE(FunctionRun_Works) {
  Function fun("kotek");
  Variable before({0});
  Variable after({3});

  fun.getFunctionBody().getContext().addVariable("kotitka", before);

  fun.getFunctionBody().addInstruction(std::make_unique<AssignStatement>(
      *fun.getFunctionBody().findVariable("kotitka"),
      std::make_unique<BaseMathExpr>(BaseMathExpr(after))));
  fun.getFunctionBody().addInstruction(
      std::make_unique<ReturnStatement>(std::make_unique<BaseMathExpr>(
          fun.getFunctionBody().findVariable("kotitka"))));

  FunctionCallStatement funCall(fun);

  BOOST_CHECK_EQUAL(
      true, static_cast<bool>(*fun.getFunctionBody().findVariable("kotitka")
                              == before));
  BOOST_CHECK_EQUAL(true, static_cast<bool>(funCall.run().variable_ == after));
  BOOST_CHECK_EQUAL(
      true, static_cast<bool>(*fun.getFunctionBody().findVariable("kotitka")
                              == before));
}

BOOST_AUTO_TEST_CASE(ArgPassedToFun_ReturnsCorrect) {
  Function fun("kotek");

  fun.addParameter("kotitka");

  fun.getFunctionBody().addInstruction(
      std::make_unique<ReturnStatement>(std::make_unique<BaseMathExpr>(
          fun.getFunctionBody().findVariable("kotitka"))));

  FunctionCallStatement funCall(fun);

  funCall.addArgument(std::make_unique<BaseMathExpr>(Variable({5})));

  BOOST_CHECK_EQUAL(
      true, static_cast<bool>(Variable({5}) == funCall.run().variable_));
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()