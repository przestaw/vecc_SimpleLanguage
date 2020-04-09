//
// Created by przemek on 23.03.2020.
//

#ifndef VECC_LANG_ASSIGN_STMT_H
#define VECC_LANG_ASSIGN_STMT_H

#include <memory>
#include <AST/statement/statement.h>
#include <AST/expression/expression.h>

namespace vecc::ast {
    /**
     * Class describing Assign Statement
     */
    class AssignStatement : public Statement {
    public:
        /**
         * Constructor
         * @param variable Variable to which value will be assigned
         * @param expression Expresion which value will be assigned
         */
        AssignStatement(Variable &variable, std::unique_ptr<Expression> expression);

        /**
         * Constructor
         * @param variable Variable to which value will be assigned
         * @param index index at which value will be assigned
         * @param expression Expresion which value will be assigned
         */
        AssignStatement(Variable &variable, const unsigned &index, std::unique_ptr<Expression> expression);

        /**
         * Runs statement
         * @return return value
         */
        Return run() override;

        /**
         * Position in code where assignment occurs. used to inform about possible error
         * @param position position in code where assignment occurs
         */
        void setPosition(const Position &position);

    private:
        Variable &variable_;
        std::unique_ptr<Expression> expression_;
        bool indexedAccess;      //!< if variable is acessed with [] operator
        unsigned index_;
        Position position_;
    };
}

#endif //VECC_LANG_ASSIGN_STMT_H
