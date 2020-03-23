//
// Created by przemek on 23.03.2020.
//

#ifndef VECC_LANG_ASSIGN_STMT_H
#define VECC_LANG_ASSIGN_STMT_H

#include <memory>
#include <AST/statement/statement.h>
#include <AST/expression/expression.h>

namespace vecc {
    class AssignStatement : public Statement {
    public:
        AssignStatement(Variable &variable, std::unique_ptr<Expression> expression);
        AssignStatement(Variable &variable, const unsigned &index, std::unique_ptr<Expression> expression);

        Return run() override;

        void setPosition(const Position &position);
    private:
        Variable &variable_;
        std::unique_ptr<Expression> expression_;
        bool indexedAcess;      //!< if variable is acessed with [] operator
        unsigned index_;
        Position position_;
    };
}

#endif //VECC_LANG_ASSIGN_STMT_H
