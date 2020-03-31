//
// Created by przemek on 20.03.2020.
//

#ifndef VECC_LANG_AND_LOGIC_EXPR_H
#define VECC_LANG_AND_LOGIC_EXPR_H

#include <memory>
#include <AST/general/variable.h>
#include <AST/expression/expression.h>

namespace vecc {
    class AndLogicExpr : public Expression {
    public:
        explicit AndLogicExpr(std::unique_ptr<Expression> value);

        void addOperand(std::unique_ptr<Expression> value);

        Variable calculate() const override;

    private:
        std::vector<std::unique_ptr<Expression>> operands;
    };
}

#endif //VECC_LANG_AND_LOGIC_EXPR_H
