//
// Created by przemek on 24.03.2020.
//

#include <AST/statement/while_stmt.h>

using namespace vecc;

WhileStatement::WhileStatement(std::unique_ptr<Expression> expression) : expression_(std::move(expression)) {}

StatementBlock &WhileStatement::getWhileBody() {
    return whileBody_;
}

Return WhileStatement::run() {
    while(static_cast<bool>(expression_->calculate())){
        whileBody_.run();
    }

    return Return();
}