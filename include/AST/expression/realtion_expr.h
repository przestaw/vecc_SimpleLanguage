//
// Created by przemek on 20.03.2020.
//

#ifndef VECC_LANG_ADDITIVE_EXPR_H
#define VECC_LANG_ADDITIVE_EXPR_H

#include <memory>
#include <AST/general/variable.h>
#include <AST/expression/expression.h>

namespace vecc::ast {
    /**
     * Class describing Relational Expression
     */
    class RelationExpr : public Expression {
    public:
        /**
         * Type of operation
         */
        enum class OperatorType {
            Equal,          //!< ==
            NotEqual,       //!< !=
            Greater,        //!< >
            GreaterOrEqual, //!< >=
            Less,           //!< <
            LessOrEqual,    //!< <=
        };

        /**
         * Constructor
         * @param lVal left side of relation
         * @param type OperatorType
         * @param rVal right side of relation
         * @param position Position of relation used to inform about errors
         */
        RelationExpr(std::unique_ptr<Expression> lVal, const OperatorType &type, std::unique_ptr<Expression> rVal,
                     const Position &position = Position());

        /**
         * Calculate value of Expression
         * @return Expression value
         */
        [[nodiscard]] Variable calculate() const override;

    private:
        OperatorType type_;
        std::unique_ptr<Expression> lVal_;
        Position pos_;
        std::unique_ptr<Expression> rVal_;
    };
}

#endif //VECC_LANG_ADDITIVE_EXPR_H
