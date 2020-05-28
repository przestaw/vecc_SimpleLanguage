//
// Created by przemek on 19.03.2020.
//

#ifndef VECC_LANG_EXPRESSION_H
#define VECC_LANG_EXPRESSION_H

#include <AST/general/variable.h>

namespace vecc::ast {
  /**
   * Base virtual class for all Expressions
   */
  class Expression {
  public:
    /**
     * Virtual destructor
     */
    virtual ~Expression() = default;

    /**
     * Calculate value of Expression
     * @return Expression value
     */
    [[nodiscard]] virtual Variable calculate() const = 0;

    /**
     * Returns simplified AST representation
     * @return simplified AST
     */
    //[[nodiscard]] virtual std::string toString() const = 0;
  };
} // namespace vecc::ast

#endif // VECC_LANG_EXPRESSION_H
