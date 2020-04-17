//
// Created by przemek on 23.03.2020.
//

#ifndef VECC_LANG_RETURN_STMT_H
#define VECC_LANG_RETURN_STMT_H

#include <memory>
#include <AST/statement/statement.h>
#include <AST/expression/expression.h>

namespace vecc {
    class ReturnStatement : public Statement {
    public:
        ReturnStatement();

        explicit ReturnStatement(std::unique_ptr<Expression> expression);

        Return run() override;

    private:
        std::unique_ptr<Expression> expression_;
        Return::Type return_;
    };
}

#endif //VECC_LANG_RETURN_STMT_H
