//
// Created by przemek on 24.03.2020.
//

#include <AST/expression/realtion_expr.h>

using namespace vecc;

RelationExpr::RelationExpr(std::unique_ptr<Expression> lVal, std::unique_ptr<Expression> rVal,
                            const OperatorType &type) : type_(type), lVal_(std::move(lVal)), rVal_(std::move(rVal)) {}

Variable RelationExpr::calculate() const {
    switch (type_){
        case OperatorType::equal:
            return (lVal_->calculate() == rVal_->calculate());
        case OperatorType::notEqual:
            return (lVal_->calculate() != rVal_->calculate());
        case OperatorType::greater:
            return (lVal_->calculate() > rVal_->calculate());
        case OperatorType::greaterOrEqual:
            return (lVal_->calculate() >= rVal_->calculate());
        case OperatorType::less:
            return (lVal_->calculate() < rVal_->calculate());
        case OperatorType::lessOrEqual:
            return (lVal_->calculate() <= rVal_->calculate());
    }
    // how to silence warning using g++ instead of clang++
}