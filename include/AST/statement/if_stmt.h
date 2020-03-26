//
// Created by przemek on 23.03.2020.
//

#ifndef VECC_LANG_IF_STMT_H
#define VECC_LANG_IF_STMT_H

#include <AST/statement/statement.h>
#include <AST/expression/expression.h>
#include "statement_block.h"

namespace vecc {
    class IfStatement : public Statement {
    public:
        IfStatement(std::unique_ptr<Expression> expression);

        StatementBlock &trueBlock();

        StatementBlock &falseBlock();

        Return run() override;

    private:
        std::unique_ptr<Expression> expression_;
        StatementBlock trueBlock_;
        StatementBlock falseBlock_;
    };
}

#endif //VECC_LANG_IF_STMT_H
