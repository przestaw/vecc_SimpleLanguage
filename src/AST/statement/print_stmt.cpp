//
// Created by przemek on 24.03.2020.
//

#include <AST/statement/print_stmt.h>

using namespace vecc;

PrintStatement::PrintStatement(std::ostream &out) : out_(out) {}

void PrintStatement::addExpression(std::unique_ptr<Expression> expression) {
    printables.emplace_back(std::move(expression));
}

void PrintStatement::addString(std::string string) {
    printables.emplace_back(std::move(string));
}

Return PrintStatement::run() {
    for(auto &it: printables){
        if(it.expression){
            out_ << std::get<std::unique_ptr<Expression>>(it.value)->calculate().toString();
        } else {
            out_ << std::get<std::string>(it.value);
        }
    }
    return Return(Return::Type::noting);
}
