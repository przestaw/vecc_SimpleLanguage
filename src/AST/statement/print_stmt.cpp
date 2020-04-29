//
// Created by przemek on 24.03.2020.
//

#include <AST/statement/print_stmt.h>
#include <sstream>

using namespace vecc;
using namespace vecc::ast;

PrintStatement::PrintStatement(std::ostream &out) : out_(out) {}

void PrintStatement::addExpression(std::unique_ptr<Expression> expression) {
  printables.emplace_back(std::move(expression));
}

void PrintStatement::addString(std::string string) {
  printables.emplace_back(std::move(string));
}

Return PrintStatement::run() {
  std::stringstream buffer;
  for (auto &it : printables) {
    if (it.expression) {
      buffer << std::get<std::unique_ptr<Expression>>(it.value)
                    ->calculate()
                    .toString();
    } else {
      buffer << std::get<std::string>(it.value);
    }
  }
  out_ << buffer.str() << std::endl;
  return Return(Return::Type::Noting);
}
