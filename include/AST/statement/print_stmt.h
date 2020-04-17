//
// Created by przemek on 23.03.2020.
//

#ifndef VECC_LANG_PRINT_STMT_H
#define VECC_LANG_PRINT_STMT_H

#include <iostream>
#include <memory>
#include <variant>
#include <AST/expression/expression.h>
#include <AST/statement/statement.h>

namespace vecc {
    class PrintStatement : public Statement {
    public:
        explicit PrintStatement(std::ostream &out = std::cout);

        void addExpression(std::unique_ptr<Expression> expression);

        void addString(std::string string);

        Return run() override;

    private:
        std::ostream &out_;

        struct Printable {
            explicit Printable(std::unique_ptr<Expression> val) : expression(true), value(std::move(val)) {}

            explicit Printable(std::string val) : expression(false), value(std::move(val)) {}

            bool expression;
            std::variant<std::unique_ptr<Expression>, std::string> value;
        };

        std::vector<Printable> printables;
    };
}

#endif //VECC_LANG_PRINT_STMT_H
