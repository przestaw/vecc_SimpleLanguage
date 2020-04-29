//
// Created by przemek on 24.03.2020.
//

#include <AST/expression/and_logic_expr.h>

using namespace vecc;
using namespace vecc::ast;

AndLogicExpr::AndLogicExpr(std::unique_ptr<Expression> value) {
  operands.emplace_back(std::move(value));
}

void AndLogicExpr::addOperand(std::unique_ptr<Expression> value) {
  operands.emplace_back(std::move(value));
}

Variable AndLogicExpr::calculate() const {
  // to allow for passing single value
  Variable ret = operands.begin()->get()->calculate();

  for (auto it = ++operands.begin(); it != operands.end(); ++it) {
    ret = ret && it->get()->calculate();
    if (!ret)
      break;
  }

  return ret;
}