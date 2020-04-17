//
// Created by przemek on 20.03.2020.
//

#ifndef VECC_LANG_BASE_LOGIC_EXPR_H
#define VECC_LANG_BASE_LOGIC_EXPR_H

#include <memory>
#include <AST/general/variable.h>
#include <AST/expression/expression.h>

namespace vecc {
    class BaseLogicExpr : public Expression {
    public:
        explicit BaseLogicExpr(std::unique_ptr<Expression> value, bool unaryLogicOp = false);

        [[nodiscard]] Variable calculate() const override;

    private:
        bool invert;
        std::unique_ptr<Expression> value_;
    };
}

#endif //VECC_LANG_BASE_LOGIC_EXPR_H
