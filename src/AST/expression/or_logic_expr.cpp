//
// Created by przemek on 24.03.2020.
//

#include <AST/expression/or_logic_expr.h>

using namespace vecc;

OrLogicExpr::OrLogicExpr(std::unique_ptr<Expression> value) {
    operands.emplace_back(std::move(value));
}

void OrLogicExpr::addOperand(std::unique_ptr<Expression> value) {
    operands.emplace_back(std::move(value));
}

Variable OrLogicExpr::calculate() const {
    Variable ret = operands.begin()->get()->calculate();

    for(auto it = ++operands.begin(); it!=operands.end(); ++it) {
        ret = ret || it->get()->calculate();
        if (ret)
            break;
    }

    return ret;
}