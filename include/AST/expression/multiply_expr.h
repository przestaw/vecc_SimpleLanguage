//
// Created by przemek on 20.03.2020.
//

#ifndef VECC_LANG_MULTIPLY_EXPR_H
#define VECC_LANG_MULTIPLY_EXPR_H

#include <AST/general/variable.h>
#include <AST/expression/expression.h>

namespace vecc {
    class MultiplyExpr : public Expression {
    public:
        virtual ~MultiplyExpr() {}

        Variable calculate() const override;
    };
}

#endif //VECC_LANG_MULTIPLY_EXPR_H
