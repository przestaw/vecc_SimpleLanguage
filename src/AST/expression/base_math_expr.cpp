//
// Created by przemek on 20.03.2020.
//

#include <AST/expression/base_math_expr.h>
#include <AST/general/function.h>
#include <AST/statement/function_call.h>
#include <error/exeception.h>

using namespace vecc;
using namespace vecc::ast;

BaseMathExpr::BaseMathExpr(std::unique_ptr<Statement> functionCall,
                           bool unaryMathOp)
    : type_(Type::Function), indexedAccess_(false), invert_(unaryMathOp),
      value_(std::move(functionCall)), index_() {
}

BaseMathExpr::BaseMathExpr(std::unique_ptr<Expression> expr, bool unaryMathOp)
    : type_(Type::Expression), indexedAccess_(false), invert_(unaryMathOp),
      value_(std::move(expr)), index_() {
}

BaseMathExpr::BaseMathExpr(Variable constant, bool unaryMathOp)
    : type_(Type::Constant), indexedAccess_(false), invert_(unaryMathOp),
      value_(std::move(constant)), index_() {
}

BaseMathExpr::BaseMathExpr(Variable* variable, bool unaryMathOp)
    : type_(Type::Variable), indexedAccess_(false), invert_(unaryMathOp),
      value_(variable), index_() {
}

BaseMathExpr::BaseMathExpr(Variable* variable, unsigned int index,
                           bool unaryMathOp)
    : type_(Type::Variable), indexedAccess_(true), invert_(unaryMathOp),
      value_(variable), index_(index) {
}

Variable BaseMathExpr::calculate() const {
  Variable ret = getBaseValue();
  if (invert_) {
    return -ret;
  } else {
    return ret;
  }
}

Variable BaseMathExpr::getBaseValue() const {
  switch (type_) {
  case Type::Expression:
    return std::get<std::unique_ptr<Expression>>(value_)->calculate();
  case Type::Constant:
    return std::get<Variable>(value_);
  case Type::Variable:
    if (indexedAccess_) {
      return Variable({(std::get<Variable*>(value_)->at(index_))});
    } else {
      return *std::get<Variable*>(value_);
    }
  default:
    return Variable();
  case Type::Function:
    Return ret = std::get<std::unique_ptr<Statement>>(value_)->run();
    if (ret.type_ == Return::Type::Value) {
      return ret.variable_;
    } else {
      // TODO : remove? rework?
      throw error::NoReturnValue(
          "Function "
          + dynamic_cast<FunctionCallStatement*>(
                std::get<std::unique_ptr<Statement>>(value_).get())
                ->getFunction()
                .getIdentifier()
          + " does not return any value");
    }
  }
}
std::string BaseMathExpr::toString() const {
  std::string ret;

  switch (type_) {
  case Type::Expression:
    ret = std::get<std::unique_ptr<Expression>>(value_)->toString();
    break;
  case Type::Constant:
    ret = std::get<Variable>(value_).toString();
    break;
  case Type::Variable:
    if (indexedAccess_) {
      ret = std::get<Variable*>(value_)->getName() + "["
            + std::to_string(index_) + "]";
    } else {
      ret = std::get<Variable*>(value_)->getName();
    }
    break;
  case Type::Function:
  default:
    ret = std::get<std::unique_ptr<Statement>>(value_)->toString();
    break;
  }

  if (invert_) {
    return "(-" + ret + ")";
  } else {
    return ret;
  }
}
