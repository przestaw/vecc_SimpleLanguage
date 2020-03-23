//
// Created by przemek on 20.03.2020.
//

#include <AST/expression/base_math_expr.h>

using namespace vecc;

BaseMathExpr::BaseMathExpr(std::unique_ptr<Statement> functionCall, bool unaryMathOp)
    : type_(Type::function), indexedAcess(false), invert(unaryMathOp), index_(){
    value_ = std::move(functionCall);
}

BaseMathExpr::BaseMathExpr(std::unique_ptr<Expression> expr, bool unaryMathOp)
    : type_(Type::expression), indexedAcess(false), invert(unaryMathOp), index_(){
    value_ = std::move(expr);
}

BaseMathExpr::BaseMathExpr(std::unique_ptr<Variable> constant, bool unaryMathOp)
        : type_(Type::constant), indexedAcess(false), invert(unaryMathOp), index_(){
    value_ = std::move(constant);
}

BaseMathExpr::BaseMathExpr(std::weak_ptr<Variable> variable, bool unaryMathOp)
        : type_(Type::variable), indexedAcess(false), invert(unaryMathOp), index_(){
    value_ = std::move(variable);
}

BaseMathExpr::BaseMathExpr(std::weak_ptr<Variable> variable, unsigned int index, bool unaryMathOp)
        : type_(Type::variable), indexedAcess(true), invert(unaryMathOp), index_(index){
    value_ = std::move(variable);
}

Variable BaseMathExpr::calculate() const {
    Variable ret = getBaseValue();
    if(invert){
        return -ret;
    } else {
        return ret;
    }
}

Variable BaseMathExpr::getBaseValue() const{
    switch (type_){
        case Type::function :
            return std::get<std::unique_ptr<Statement>>(value_)->run().variable_;
            // FIXME : consider exception if return NONE
        case Type::expression :
            return std::get<std::unique_ptr<Expression>>(value_)->calculate();
        case Type::constant :
            return *std::get<std::unique_ptr<Variable>>(value_);
        case Type::variable :
            if(indexedAcess){
                return *std::get<std::weak_ptr<Variable>>(value_).lock();
            } else {
                return Variable({(*std::get<std::weak_ptr<Variable>>(value_).lock()).at(index_)});
            }
            // FIXME : consider weak_ptr check
        default:
            return Variable();
    }
}

