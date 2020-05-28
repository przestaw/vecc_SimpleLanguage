//
// Created by przemek on 23.03.2020.
//

#ifndef VECC_LANG_IF_STMT_H
#define VECC_LANG_IF_STMT_H

#include "statement_block.h"
#include <AST/expression/expression.h>
#include <AST/statement/statement.h>

namespace vecc::ast {
  /**
   * Class describing If Statement. Executes it's statement block depending on a
   * condition value
   */
  class IfStatement : public Statement {
  public:
    /**
     * Constructor
     * @param expression if expression
     */
    explicit IfStatement(std::unique_ptr<Expression> expression);

    /**
     * Returns reference to true statement block body
     * @return true body reference
     */
    StatementBlock &trueBlock();

    /**
     * Returns reference to false statement block body
     * @return false body reference
     */
    StatementBlock &falseBlock();

    /**
     * Runs statement
     * @return return value
     */
    Return run() override;

    /**
     * Returns simplified AST representation
     * @return simplified AST
     */
    [[nodiscard]] std::string toString() const override;

  private:
    std::unique_ptr<Expression> expression_;
    StatementBlock trueBlock_;
    StatementBlock falseBlock_;
  };
} // namespace vecc::ast

#endif // VECC_LANG_IF_STMT_H
