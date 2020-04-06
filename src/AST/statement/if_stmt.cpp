//
// Created by przemek on 24.03.2020.
//

#include <AST/statement/if_stmt.h>

using namespace vecc;
using namespace vecc::ast;

IfStatement::IfStatement(std::unique_ptr<Expression> expression) : expression_(std::move(expression)) {}

StatementBlock &IfStatement::trueBlock() {
    return trueBlock_;
}

StatementBlock &IfStatement::falseBlock() {
    return falseBlock_;
}

Return IfStatement::run() {
    if (static_cast<bool>(expression_->calculate())) {
        return trueBlock_.run();
    } else {
        return falseBlock_.run();
    }
}
