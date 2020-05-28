//
// Created by przemek on 20.03.2020.
//

#ifndef VECC_LANG_MATH_EXPR_H
#define VECC_LANG_MATH_EXPR_H

#include <AST/expression/expression.h>
#include <AST/general/variable.h>
#include <memory>

namespace vecc::ast {
  /**
   * Class describing Additive Mathematical Expression
   */
  class AdditiveExpr : public Expression {
  public:
    /**
     * Type of operation
     */
    enum class OperatorType {
      Add,      //!< +
      Substract //!< -
    };

    /**
     * Constructor
     * @param value first value of Expression
     */
    explicit AdditiveExpr(std::unique_ptr<Expression> value);

    /**
     * Adds operand to Expression
     * @param value operand value
     * @param type operation type
     * @param position position used to inform about errors
     */
    void addOperand(std::unique_ptr<Expression> value, const OperatorType &type,
                    const Position &position = Position());

    /**
     * Calculate value of Expression
     * @return Expression value
     */
    [[nodiscard]] Variable calculate() const override;

    /**
     * Returns simplified AST representation
     * @return simplified AST
     */
    //[[nodiscard]] virtual std::string toString() const override;
  private:
    std::unique_ptr<Expression> baseValue;

    struct Addable {
      Addable(const OperatorType type, std::unique_ptr<Expression> value,
              const Position &position)
          : operation_(type), value_(std::move(value)), pos_(position) {}

      OperatorType operation_;
      std::unique_ptr<Expression> value_;
      Position pos_;
    };

    std::vector<Addable> multiplyables;
  };
} // namespace vecc::ast

#endif // VECC_LANG_MATH_EXPR_H
