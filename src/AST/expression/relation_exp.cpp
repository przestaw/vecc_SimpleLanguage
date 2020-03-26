//
// Created by przemek on 24.03.2020.
//

#include <AST/expression/realtion_expr.h>

using namespace vecc;

RelationExpr::RelationExpr(std::unique_ptr<Expression> lVal, std::unique_ptr<Expression> rVal,
                            const OperatorType &type) : type_(type), lVal_(std::move(lVal)), rVal_(std::move(rVal)) {}

Variable RelationExpr::calculate() const {
    switch (type_){
        case OperatorType::Equal:
            return (lVal_->calculate() == rVal_->calculate());
        case OperatorType::NotEqual:
            return (lVal_->calculate() != rVal_->calculate());
        case OperatorType::Greater:
            return (lVal_->calculate() > rVal_->calculate());
        case OperatorType::GreaterOrEqual:
            return (lVal_->calculate() >= rVal_->calculate());
        case OperatorType::Less:
            return (lVal_->calculate() < rVal_->calculate());
        case OperatorType::LessOrEqual:
            return (lVal_->calculate() <= rVal_->calculate());
        case OperatorType::PassValue:
            return lVal_->calculate();
    }
    // how to silence warning using g++ instead of clang++
}