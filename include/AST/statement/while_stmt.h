//
// Created by przemek on 23.03.2020.
//

#ifndef VECC_LANG_WHILE_STMT_H
#define VECC_LANG_WHILE_STMT_H
#include <AST/statement/statement.h>
#include <AST/expression/expression.h>
#include <AST/statement/statement_block.h>

namespace vecc {
    class WhileStatement : public Statement {
    public:
        WhileStatement(std::unique_ptr<Expression> expression);

        StatementBlock &getWhileBody();

        Return run() override;

    private:
        std::unique_ptr<Expression> expression_;
        StatementBlock whileBody_;
    };
}

#endif //VECC_LANG_WHILE_STMT_H
