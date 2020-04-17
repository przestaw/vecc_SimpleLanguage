//
// Created by przemek on 24.03.2020.
//
#include <AST/statement/return_stmt.h>

using namespace vecc;

ReturnStatement::ReturnStatement() : return_(Return::Type::Noting) {}

ReturnStatement::ReturnStatement(std::unique_ptr<Expression> expression)
        : expression_(std::move(expression)), return_(Return::Type::Value) {}

Return ReturnStatement::run() {
    if (expression_) {
        return Return(Return::Type::Value, expression_->calculate());
    } else {
        return Return(return_);
    }
}