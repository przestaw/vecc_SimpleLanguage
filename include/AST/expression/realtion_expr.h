//
// Created by przemek on 20.03.2020.
//

#ifndef VECC_LANG_ADDITIVE_EXPR_H
#define VECC_LANG_ADDITIVE_EXPR_H

#include <AST/general/variable.h>
#include <AST/expression/expression.h>

namespace vecc {
    class RelationExpr : public Expression {
    public:
        virtual ~RelationExpr() {}

        Variable calculate() const override;
    };
}

#endif //VECC_LANG_ADDITIVE_EXPR_H
