//
// Created by przemek on 23.03.2020.
//

#include <AST/expression/base_math_expr.h>
#include <AST/statement/assign_stmt.h>
#include <boost/test/unit_test.hpp>

using namespace vecc;
using namespace vecc::ast;

BOOST_AUTO_TEST_SUITE(AST_Test_Suite)

BOOST_AUTO_TEST_SUITE(Assign_Stmt_Test_Suite)

BOOST_AUTO_TEST_CASE(AssignVal_Works) {
  Variable before({0});
  auto variable = Variable(before);
  Variable after({3});

  AssignStatement stmt(variable,
                       std::make_unique<BaseMathExpr>(BaseMathExpr(after)));
  BOOST_REQUIRE_EQUAL(variable, before);
  stmt.run();
  BOOST_CHECK_EQUAL(variable, after);
}

BOOST_AUTO_TEST_CASE(AssignVec2_Works) {
  Variable before({1, 2});
  auto variable = Variable(before);
  Variable after({3, 3});

  AssignStatement stmt(variable,
                       std::make_unique<BaseMathExpr>(BaseMathExpr(after)));
  BOOST_REQUIRE_EQUAL(variable, before);
  stmt.run();
  BOOST_CHECK_EQUAL(variable, after);
}

BOOST_AUTO_TEST_CASE(AssignVec3_Works) {
  Variable before({0, 1, 2});
  auto variable = Variable(before);
  Variable after({3, 3, 3});

  AssignStatement stmt(variable,
                       std::make_unique<BaseMathExpr>(BaseMathExpr(after)));
  BOOST_REQUIRE_EQUAL(variable, before);
  stmt.run();
  BOOST_CHECK_EQUAL(variable, after);
}

BOOST_AUTO_TEST_CASE(AssignValToIndex1Vec2_Works) {
  Variable before({0, 2});
  auto variable = Variable(before);
  Variable after({0, 7});

  AssignStatement stmt(
      variable, 1, std::make_unique<BaseMathExpr>(BaseMathExpr(Variable({7}))));
  BOOST_REQUIRE_EQUAL(variable, before);
  stmt.run();
  BOOST_CHECK_EQUAL(variable, after);
}

BOOST_AUTO_TEST_CASE(AssignValToIndex0Vec3_Works) {
  Variable before({0, 2, 4});
  auto variable = Variable(before);
  Variable after({3, 2, 4});

  AssignStatement stmt(
      variable, 0, std::make_unique<BaseMathExpr>(BaseMathExpr(Variable({3}))));
  BOOST_REQUIRE_EQUAL(variable, before);
  stmt.run();
  BOOST_CHECK_EQUAL(variable, after);
}

BOOST_AUTO_TEST_CASE(AssignValToIndex1vec3_Works) {
  Variable before({0, 2, 4});
  auto variable = Variable(before);
  Variable after({0, 9, 4});

  AssignStatement stmt(
      variable, 1, std::make_unique<BaseMathExpr>(BaseMathExpr(Variable({9}))));
  BOOST_REQUIRE_EQUAL(variable, before);
  stmt.run();
  BOOST_CHECK_EQUAL(variable, after);
}

BOOST_AUTO_TEST_CASE(AssignVal_ToStirngWirks) {
  Variable variable({0, 2});
  variable.setName("roman");

  AssignStatement stmt(
      variable, std::make_unique<BaseMathExpr>(BaseMathExpr(Variable({3, 7}))));
  BOOST_REQUIRE_EQUAL(stmt.toString(), "roman = vec[3, 7]");
}

BOOST_AUTO_TEST_CASE(AssignValToIndex_ToStirngWirks) {
  Variable variable({0, 2, 4});
  variable.setName("roman");
  AssignStatement stmt(
      variable, 2,
      std::make_unique<BaseMathExpr>(BaseMathExpr(Variable({-3}))));
  BOOST_REQUIRE_EQUAL(stmt.toString(), "roman[2] = -3");
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()