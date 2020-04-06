//
// Created by przemek on 24.03.2020.
//

#include <AST/statement/while_stmt.h>

using namespace vecc;
using namespace vecc::ast;

WhileStatement::WhileStatement(std::unique_ptr<Expression> expression) : expression_(std::move(expression)) {}

StatementBlock &WhileStatement::getWhileBody() {
    return whileBody_;
}

Return WhileStatement::run() {
    Return ret;

    while (static_cast<bool>(expression_->calculate())) {
        ret = whileBody_.run();
        if(ret.type_ == Return::Type::Value){
            break;
        }
    }

    return ret;
}