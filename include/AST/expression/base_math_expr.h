//
// Created by przemek on 20.03.2020.
//

#ifndef VECC_LANG_BASE_MATH_EXPR_H
#define VECC_LANG_BASE_MATH_EXPR_H

#include <memory>
#include <variant>
#include <AST/expression/expression.h>
#include <AST/statement/statement.h>

namespace vecc::ast {
    /**
     * Class describing Base Mathematical Expression
     */
    class BaseMathExpr : public Expression {
    public:
        BaseMathExpr() = delete;

        /**
         * Constructor
         * @param functionCall function call returning value
         * @param unaryMathOp determines is value should be negated
         */
        explicit BaseMathExpr(std::unique_ptr<Statement> functionCall, bool unaryMathOp = false);

        /**
         * Constructor
         * @param expr
         * @param unaryMathOp determines is value should be negated
         */
        explicit BaseMathExpr(std::unique_ptr<Expression> expr, bool unaryMathOp = false);

        /**
         * Constructor
         * @param constant constant value
         * @param unaryMathOp determines is value should be negated
         */
        explicit BaseMathExpr(Variable constant, bool unaryMathOp = false);

        /**
         * Constructor
         * @param variable variable
         * @param unaryMathOp determines is value should be negated
         */
        explicit BaseMathExpr(std::shared_ptr<Variable> variable, bool unaryMathOp = false);

        /**
         * Constructor
         * @param variable variable
         * @param index index
         * @param unaryMathOp determines is value should be negated
         */
        BaseMathExpr(std::shared_ptr<Variable> variable, unsigned index, bool unaryMathOp = false);

        /**
         * Calculate value of Expression
         * @return Expression value
         */
        [[nodiscard]] Variable calculate() const override;

    private:
        [[nodiscard]] inline Variable getBaseValue() const;

        enum class Type {
            Function,
            Expression,
            Constant,
            Variable
        };

        Type type_;             //!< determines type of expression
        bool indexedAccess_;      //!< if variable is acessed with [] operator
        bool invert_;            //!< if unarymathOperator was present

        std::variant<
                std::unique_ptr<Statement>,
                std::unique_ptr<Expression>,
                Variable,
                std::shared_ptr<Variable> > value_;

        unsigned index_;
    };
}

#endif //VECC_LANG_BASE_MATH_EXPR_H
