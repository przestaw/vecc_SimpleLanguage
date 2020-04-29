//
// Created by przemek on 23.03.2020.
//

#include <AST/statement/assign_stmt.h>
#include <error/exeception.h>

using namespace vecc;
using namespace vecc::ast;

AssignStatement::AssignStatement(Variable &variable,
                                 std::unique_ptr<Expression> expression)
    : variable_(variable), expression_(std::move(expression)),
      indexedAccess(false), index_() {}

AssignStatement::AssignStatement(Variable &variable, const unsigned &index,
                                 std::unique_ptr<Expression> expression)
    : variable_(variable), expression_(std::move(expression)),
      indexedAccess(true), index_(index) {}

Return AssignStatement::run() {
  Variable value = expression_->calculate();
  if (indexedAccess) {
    if (value.size() == 1) {
      variable_.setPosition(position_);
      variable_.at(index_) = value.at(0);
    } else {
      throw error::MathException(
          "Try to assign a n-dimensional vector to the int\n"
          + (position_ != Position() ? "at " + position_.toString() : ""));
    }
  } else {
    variable_ = value;
  }

  return Return(Return::Type::Noting);
}

void AssignStatement::setPosition(const Position &position) {
  this->position_ = position;
}
