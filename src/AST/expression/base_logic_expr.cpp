//
// Created by przemek on 24.03.2020.
//

#include <AST/expression/base_logic_expr.h>

using namespace vecc;


BaseLogicExpr::BaseLogicExpr(std::unique_ptr<Expression> value, bool unaryLogicOp) : invert(unaryLogicOp),
                                                                                     value_(std::move(value)) {}

Variable BaseLogicExpr::calculate() const {
    return invert ? !value_->calculate() : value_->calculate();
}
