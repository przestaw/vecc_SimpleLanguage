//
// Created by przemek on 20.03.2020.
//

#ifndef VECC_LANG_OR_LOGIC_EXP_H
#define VECC_LANG_OR_LOGIC_EXP_H

#include <memory>
#include <AST/general/variable.h>
#include <AST/expression/expression.h>

namespace vecc::ast {
    /**
     * Class describing Or Logical Expression
     */
    class OrLogicExpr : public Expression {
    public:
        /**
         * Constructor
         * @param value first value of Expression
         */
        explicit OrLogicExpr(std::unique_ptr<Expression> value);

        /**
         * Adds operand to expression
         * @param value operand value
         */
        void addOperand(std::unique_ptr<Expression> value);

        /**
         * Calculate value of Expression
         * @return Expression value
         */
        [[nodiscard]] Variable calculate() const override;

    private:
        std::vector<std::unique_ptr<Expression>> operands;
    };
}

#endif //VECC_LANG_OR_LOGIC_EXP_H
