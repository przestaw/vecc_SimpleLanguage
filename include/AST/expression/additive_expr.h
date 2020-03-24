//
// Created by przemek on 20.03.2020.
//

#ifndef VECC_LANG_MATH_EXPR_H
#define VECC_LANG_MATH_EXPR_H

#include <memory>
#include <AST/general/variable.h>
#include <AST/expression/expression.h>

namespace vecc {
    class AddExpr : public Expression {
    public:
        enum class OperatorType{
            add,
            substract
        };
        AddExpr(std::unique_ptr<Expression> value);

        void addOperand(std::unique_ptr<Expression> value, const OperatorType &type);

        Variable calculate() const override;
    private:
        std::unique_ptr<Expression> baseValue;
        struct Addable {
            Addable(const OperatorType type, std::unique_ptr<Expression> value) : operation(type), value_(std::move(value)) {}
            OperatorType operation;
            std::unique_ptr<Expression> value_;
        };
        std::vector<Addable> multiplyables;
    };
}

#endif //VECC_LANG_MATH_EXPR_H
