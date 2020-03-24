//
// Created by przemek on 20.03.2020.
//

#include <AST/expression/base_math_expr.h>
#include <error/exeception.h>
#include <AST/general/function.h>
#include <AST/statement/function_call.h>

using namespace vecc;

BaseMathExpr::BaseMathExpr(std::unique_ptr<Statement> functionCall, bool unaryMathOp)
        : type_(Type::function), indexedAcess(false), invert(unaryMathOp), index_() {
    value_ = std::move(functionCall);
}

BaseMathExpr::BaseMathExpr(std::unique_ptr<Expression> expr, bool unaryMathOp)
        : type_(Type::expression), indexedAcess(false), invert(unaryMathOp), index_() {
    value_ = std::move(expr);
}

BaseMathExpr::BaseMathExpr(std::unique_ptr<Variable> constant, bool unaryMathOp)
        : type_(Type::constant), indexedAcess(false), invert(unaryMathOp), index_() {
    value_ = std::move(constant);
}

BaseMathExpr::BaseMathExpr(Variable *variable, bool unaryMathOp)
        : type_(Type::variable), indexedAcess(false), invert(unaryMathOp), index_() {
    value_ = variable;
}

BaseMathExpr::BaseMathExpr(Variable *variable, unsigned int index, bool unaryMathOp)
        : type_(Type::variable), indexedAcess(true), invert(unaryMathOp), index_(index) {
    value_ = variable;
}

Variable BaseMathExpr::calculate() const {
    Variable ret = getBaseValue();
    if (invert) {
        return -ret;
    } else {
        return ret;
    }
}

Variable BaseMathExpr::getBaseValue() const {
    switch (type_) {
        case Type::expression :
            return std::get<std::unique_ptr<Expression>>(value_)->calculate();
        case Type::constant :
            return *std::get<std::unique_ptr<Variable>>(value_);
        case Type::variable :
            if (indexedAcess) {
                return Variable({(std::get<Variable *>(value_)->at(index_))});
            } else {
                return *std::get<Variable *>(value_);
            }
            // FIXME : consider weak_ptr check
        default:
            return Variable();
        case Type::function :
            Return ret = std::get<std::unique_ptr<Statement>>(value_)->run();
            if (ret.type_ == Return::Type::value) {
                return ret.variable_;
            } else {
                throw NoReturnValue("Function " +
                                    dynamic_cast<FunctionCallStatement *>(std::get<std::unique_ptr<Statement>>(
                                            value_).get())->getFunction().getIdentifier() +
                                    " does not return any value");
            }
    }
}

