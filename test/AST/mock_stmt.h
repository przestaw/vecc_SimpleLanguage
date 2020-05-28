//
// Created by przemek on 28.05.2020.
//

#ifndef VECC_MOCK_STMT_H
#define VECC_MOCK_STMT_H

#include <AST/statement/statement.h>

#include <utility>

namespace vecc::test {
  class MockStmt : public vecc::ast::Statement {
  public:
    explicit MockStmt(std::string name = "functionCall(a)")
        : name_(std::move(name)) {}

    vecc::ast::Return run() override { return vecc::ast::Return(); }

    std::string toString() const override { return name_; };

  private:
    std::string name_;
  };
} // namespace vecc::test

#endif // VECC_MOCK_STMT_H
