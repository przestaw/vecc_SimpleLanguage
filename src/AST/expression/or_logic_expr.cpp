//
// Created by przemek on 24.03.2020.
//

#include <AST/expression/or_logic_expr.h>

using namespace vecc;
using namespace vecc::ast;

OrLogicExpr::OrLogicExpr(std::unique_ptr<Expression> value) {
  operands.emplace_back(std::move(value));
}

void OrLogicExpr::addOperand(std::unique_ptr<Expression> value) {
  operands.emplace_back(std::move(value));
}

Variable OrLogicExpr::calculate() const {
  Variable ret = operands.begin()->get()->calculate();

  for (auto it = ++operands.begin(); it != operands.end(); ++it) {
    ret = ret || it->get()->calculate();
    if (ret)
      break;
  }

  return ret;
}
std::string OrLogicExpr::toString() const {
  if (operands.size() < 2) {
    return operands.begin()->get()->toString();
  } else {
    std::string ret = "(" + operands.begin()->get()->toString();
    for (auto it = ++operands.begin(); it != operands.end(); ++it) {
      ret += " or " + it->get()->toString();
    }
    ret += ")";
    return ret;
  }
}
