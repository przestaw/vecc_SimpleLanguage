//
// Created by przemek on 20.03.2020.
//

#ifndef VECC_LANG_OR_LOGIC_EXP_H
#define VECC_LANG_OR_LOGIC_EXP_H

#include <AST/general/variable.h>
#include <AST/expression/expression.h>

namespace vecc {
    class OrLogicExpr : public Expression {
    public:
        virtual ~OrLogicExpr() {}

        Variable calculate() const override;
    };
}

#endif //VECC_LANG_OR_LOGIC_EXP_H
