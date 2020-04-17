//
// Created by przemek on 20.03.2020.
//

#ifndef VECC_LANG_BASE_LOGIC_EXPR_H
#define VECC_LANG_BASE_LOGIC_EXPR_H

#include <memory>
#include <AST/general/variable.h>
#include <AST/expression/expression.h>

namespace vecc::ast {
    /**
     * Class describing Base Logical Expression
     */
    class BaseLogicExpr : public Expression {
    public:
        /**
         * Constructor
         * @param value value of Expression
         * @param unaryLogicOp determines is vale should be negated
         */
        explicit BaseLogicExpr(std::unique_ptr<Expression> value, bool unaryLogicOp = false);

        /**
         * Calculate value of Expression
         * @return Expression value
         */
        [[nodiscard]] Variable calculate() const override;

    private:
        bool invert;
        std::unique_ptr<Expression> value_;
    };
}

#endif //VECC_LANG_BASE_LOGIC_EXPR_H
