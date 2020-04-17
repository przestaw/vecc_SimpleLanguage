//
// Created by przemek on 20.03.2020.
//

#ifndef VECC_LANG_ADDITIVE_EXPR_H
#define VECC_LANG_ADDITIVE_EXPR_H

#include <memory>
#include <AST/general/variable.h>
#include <AST/expression/expression.h>

namespace vecc {
    class RelationExpr : public Expression {
    public:
        enum class OperatorType {
            Equal,
            NotEqual,
            Greater,
            GreaterOrEqual,
            Less,
            LessOrEqual,
            //PassValue
        };

        RelationExpr(std::unique_ptr<Expression> lVal, const OperatorType &type, std::unique_ptr<Expression> rVal, const Position &position  = Position());

        [[nodiscard]] Variable calculate() const override;

    private:
        OperatorType type_;
        std::unique_ptr<Expression> lVal_;
        Position pos_;
        std::unique_ptr<Expression> rVal_;
    };
}

#endif //VECC_LANG_ADDITIVE_EXPR_H
