//
// Created by przemek on 24.03.2020.
//
#include <AST/statement/return_stmt.h>

using namespace vecc;

ReturnStatement::ReturnStatement() : return_(Return::Type::noting) {}

ReturnStatement::ReturnStatement(std::unique_ptr<Expression> expression)
        : expression(std::move(expression)), return_(Return::Type::value) {}

Return ReturnStatement::run() {
    if (expression) {
        return Return(return_, expression->calculate());
    } else {
        return Return(return_);
    }
}