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

        explicit MultiplyExpr(std::unique_ptr<Expression> value);

        void addOperand(std::unique_ptr<Expression> value, const OperatorType &type, const Position &position = Position());

        [[nodiscard]] Variable calculate() const override;

    private:
        std::unique_ptr<Expression> baseValue;

        struct Multiplyable {
            Multiplyable(const OperatorType type, std::unique_ptr<Expression> value, const Position &position)
                : operation_(type), value_(std::move(value)), pos_(position) {}

            OperatorType operation_;
            std::unique_ptr<Expression> value_;
            Position pos_;
        };

        std::vector<Multiplyable> multiplyables;
    };
}

#endif //VECC_LANG_MULTIPLY_EXPR_H
