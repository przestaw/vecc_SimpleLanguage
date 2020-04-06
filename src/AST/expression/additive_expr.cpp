//
// Created by przemek on 24.03.2020.
//

#include <AST/expression/additive_expr.h>

using namespace vecc;
using namespace vecc::ast;

AddExpr::AddExpr(std::unique_ptr<Expression> value) : baseValue(std::move(value)) {}

void AddExpr::addOperand(std::unique_ptr<Expression> value, const OperatorType &type, const Position &position) {
    multiplyables.emplace_back(type, std::move(value), position);
}

Variable AddExpr::calculate() const {
    Variable ret = baseValue->calculate();

    for (auto &&it : multiplyables) {
        ret.setPosition(it.pos_);
        switch (it.operation_) {
            case OperatorType::Add:
                ret = ret + it.value_->calculate();
                break;
            case OperatorType::Substract:
                ret = ret - it.value_->calculate();
                break;
        }
    }

    return ret;
}
