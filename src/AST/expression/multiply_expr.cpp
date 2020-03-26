//
// Created by przemek on 24.03.2020.
//

#include <AST/expression/multiply_expr.h>

using namespace vecc;

MultiplyExpr::MultiplyExpr(std::unique_ptr<Expression> value) : baseValue(std::move(value)) {}

void MultiplyExpr::addOperand(std::unique_ptr<Expression> value, const MultiplyExpr::OperatorType &type) {
    multiplyables.emplace_back(type, std::move(value));
}

Variable MultiplyExpr::calculate() const {
    Variable ret = baseValue->calculate();

    for(auto &&it : multiplyables){
        switch (it.operation) {
            case OperatorType::Multiply:
                ret = ret * it.value_->calculate();
                break;
            case OperatorType::Divide:
                ret = ret / it.value_->calculate();
                break;
            case OperatorType::Modulo:
                ret = ret % it.value_->calculate();
                break;
        }
    }

    return ret;
}
