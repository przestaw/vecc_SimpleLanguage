//
// Created by przemek on 24.03.2020.
//

#include <AST/expression/realtion_expr.h>

using namespace vecc;
using namespace vecc::ast;

RelationExpr::RelationExpr(std::unique_ptr<Expression> lVal,
                           const RelationExpr::OperatorType &type,
                           std::unique_ptr<Expression> rVal,
                           const Position &position)
    : type_(type), lVal_(std::move(lVal)), pos_(position),
      rVal_(std::move(rVal)) {
}

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wreturn-type"
/* NOTE: GCC inproperly handles that case : strongly typed enum with all values
 *       covered. This was added to allow of usage -Werror with GCC
 */
Variable RelationExpr::calculate() const {
  Variable ret = lVal_->calculate();
  ret.setPosition(pos_);

  switch (type_) {
  case OperatorType::Equal:
    return (ret == rVal_->calculate());
  case OperatorType::NotEqual:
    return (ret != rVal_->calculate());
  case OperatorType::Greater:
    return (ret > rVal_->calculate());
  case OperatorType::GreaterOrEqual:
    return (ret >= rVal_->calculate());
  case OperatorType::Less:
    return (ret < rVal_->calculate());
  case OperatorType::LessOrEqual:
    return (ret <= rVal_->calculate());
  }
}
std::string RelationExpr::toString() const {
  std::string ret = "(" + lVal_->toString();
  switch (type_) {
  case OperatorType::Equal:
    return (ret += " == " + rVal_->toString() + ")");
  case OperatorType::NotEqual:
    return (ret += " != " + rVal_->toString() + ")");
  case OperatorType::Greater:
    return (ret += " > " + rVal_->toString() + ")");
  case OperatorType::GreaterOrEqual:
    return (ret += " >= " + rVal_->toString() + ")");
  case OperatorType::Less:
    return (ret += " < " + rVal_->toString() + ")");
  case OperatorType::LessOrEqual:
    return (ret += " <= " + rVal_->toString() + ")");
  }
}
#pragma GCC diagnostic pop
