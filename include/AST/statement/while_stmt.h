//
// Created by przemek on 23.03.2020.
//

#ifndef VECC_LANG_WHILE_STMT_H
#define VECC_LANG_WHILE_STMT_H

#include <AST/expression/expression.h>
#include <AST/statement/statement.h>
#include <AST/statement/statement_block.h>

namespace vecc::ast {
  /**
   * While Statement class. Executes it's statement block if expression is true
   */
  class WhileStatement : public Statement {
  public:
    /**
     * Constructor
     * @param expression while expression
     */
    explicit WhileStatement(std::unique_ptr<Expression> expression);

    /**
     * Returns reference to while body
     * @return while body reference
     */
    StatementBlock &getWhileBody();

    /**
     * Runs statement
     * @return return value
     */
    Return run() override;

  private:
    std::unique_ptr<Expression> expression_;
    StatementBlock whileBody_;
  };
} // namespace vecc::ast

#endif // VECC_LANG_WHILE_STMT_H
