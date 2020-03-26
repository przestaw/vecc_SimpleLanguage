//
// Created by przemek on 20.03.2020.
//

#ifndef VECC_LANG_MULTIPLY_EXPR_H
#define VECC_LANG_MULTIPLY_EXPR_H

#include <AST/general/variable.h>
#include <AST/expression/expression.h>
#include <AST/expression/base_math_expr.h>

namespace vecc {
    class MultiplyExpr : public Expression {
    public:
        enum class OperatorType {
            Multiply,
            Divide,
            Modulo
        };

        MultiplyExpr(std::unique_ptr<Expression> value);

        void addOperand(std::unique_ptr<Expression> value, const OperatorType &type);

        Variable calculate() const override;

    private:
        std::unique_ptr<Expression> baseValue;

        struct Multipyable {
            Multipyable(const OperatorType type, std::unique_ptr<Expression> value) : operation(type),
                                                                                      value_(std::move(value)) {}

            OperatorType operation;
            std::unique_ptr<Expression> value_;
        };

        std::vector<Multipyable> multiplyables;
    };
}

#endif //VECC_LANG_MULTIPLY_EXPR_H
