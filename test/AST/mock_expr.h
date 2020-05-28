//
// Created by przemek on 28.05.2020.
//

#ifndef VECC_MOCK_EXPR_H
#define VECC_MOCK_EXPR_H

#include <AST/expression/expression.h>

#include <utility>

namespace vecc::test {
  class MockExpr : public vecc::ast::Expression {
  public:
    explicit MockExpr(std::string name = "expression")
        : name_(std::move(name)) {}

    [[nodiscard]] vecc::ast::Variable calculate() const override {
      return vecc::ast::Variable();
    }

    [[nodiscard]] std::string toString() const override { return name_; };

  private:
    std::string name_;
  };
} // namespace vecc::test

#endif // VECC_MOCK_EXPR_H
