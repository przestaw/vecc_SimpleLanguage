//
// Created by przemek on 20.03.2020.
//

#ifndef VECC_LANG_AND_LOGIC_EXPR_H
#define VECC_LANG_AND_LOGIC_EXPR_H

#include <AST/expression/expression.h>
#include <AST/general/variable.h>
#include <memory>

namespace vecc::ast {
  /**
   * Class describing And Logical Expression
   */
  class AndLogicExpr : public Expression {
  public:
    /**
     * Constructor
     * @param value first value of Expression
     */
    explicit AndLogicExpr(std::unique_ptr<Expression> value);

    /**
     * Adds operand to expression
     * @param value operand value
     */
    void addOperand(std::unique_ptr<Expression> value);

    /**
     * Calculate value of Expression
     * @return Expression value
     */
    Variable calculate() const override;

  private:
    std::vector<std::unique_ptr<Expression>> operands;
  };
} // namespace vecc::ast

#endif // VECC_LANG_AND_LOGIC_EXPR_H
