//
// Created by przemek on 20.03.2020.
//

#ifndef VECC_LANG_BASE_MATH_EXPR_H
#define VECC_LANG_BASE_MATH_EXPR_H

#include <AST/expression/expression.h>
#include <AST/statement/statement.h>
#include <memory>
#include <variant>

namespace vecc::ast {
  /**
   * Class describing Base Mathematical Expression
   */
  class BaseMathExpr : public Expression {
  public:
    BaseMathExpr() = delete;

    /**
     * Constructor
     * @param functionCall function call returning value
     * @param unaryMathOp determines is value should be negated
     */
    explicit BaseMathExpr(std::unique_ptr<Statement> functionCall,
                          bool unaryMathOp = false);

    /**
     * Constructor for expression
     * @param expr expression
     * @param unaryMathOp determines is value should be negated
     */
    explicit BaseMathExpr(std::unique_ptr<Expression> expr,
                          bool unaryMathOp = false);

    /**
     * Constructor for constant value
     * @param constant constant value
     * @param unaryMathOp determines is value should be negated
     */
    explicit BaseMathExpr(Variable constant, bool unaryMathOp = false);

    /**
     * Constructor for program variable val
     * @param variable variable
     * @param unaryMathOp determines is value should be negated
     */
    // NOTE : using pointer instead of reference to distinguish from value
    explicit BaseMathExpr(Variable* variable, bool unaryMathOp = false);

    /**
     * Constructor for program variable val indexed acess
     * @param variable variable
     * @param index index
     * @param unaryMathOp determines is value should be negated
     */
    // NOTE : using pointer instead of reference to distinguish from value
    BaseMathExpr(Variable* variable, unsigned index, bool unaryMathOp = false);

    /**
     * Calculate value of Expression
     * @return Expression value
     */
    [[nodiscard]] Variable calculate() const override;

    /**
     * Returns simplified AST representation
     * @return simplified AST
     */
    [[nodiscard]] std::string toString() const override;

  private:
    [[nodiscard]] inline Variable getBaseValue() const;

    enum class Type { Function, Expression, Constant, Variable };

    Type type_;          //!< determines type of expression
    bool indexedAccess_; //!< if variable is acessed with [] operator
    bool invert_;        //!< if unarymathOperator was present

    std::variant<std::unique_ptr<Statement>, std::unique_ptr<Expression>,
                 Variable, Variable*>
        value_;

    unsigned index_;
  };
} // namespace vecc::ast

#endif // VECC_LANG_BASE_MATH_EXPR_H
