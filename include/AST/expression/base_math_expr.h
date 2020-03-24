//
// Created by przemek on 20.03.2020.
//

#ifndef VECC_LANG_BASE_MATH_EXPR_H
#define VECC_LANG_BASE_MATH_EXPR_H

#include <memory>
#include <variant>
#include <AST/expression/expression.h>
#include <AST/statement/statement.h>

namespace vecc {
    class BaseMathExpr : public Expression {
    public:
        BaseMathExpr() = delete;

        explicit BaseMathExpr(std::unique_ptr<Statement> functionCall, bool unaryMathOp = false);
        explicit BaseMathExpr(std::unique_ptr<Expression> expr, bool unaryMathOp = false);

        explicit BaseMathExpr(std::unique_ptr<Variable> constant, bool unaryMathOp = false);
        // construction pointing to existing Variables
        // TODO : considere using shared ptr for Variables in Context and weak_ptr here
        explicit BaseMathExpr(Variable* variable, bool unaryMathOp = false);
        explicit BaseMathExpr(Variable* variable, unsigned index = 0, bool unaryMathOp = false);

        Variable calculate() const override;
    private:
        inline Variable getBaseValue() const;

        enum class Type {
            function,
            expression,
            constant,
            variable
        };

        Type type_;             //!< determines type of expression
        bool indexedAcess;      //!< if variable is acessed with [] operator
        bool invert;            //!< if unarymathOperator was present

        std::variant<
                std::unique_ptr<Statement>,
                std::unique_ptr<Expression>,
                std::unique_ptr<Variable>,
                Variable*> value_;

        unsigned index_;
    };

}

#endif //VECC_LANG_BASE_MATH_EXPR_H
