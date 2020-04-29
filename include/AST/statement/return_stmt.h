//
// Created by przemek on 23.03.2020.
//

#ifndef VECC_LANG_RETURN_STMT_H
#define VECC_LANG_RETURN_STMT_H

#include <AST/expression/expression.h>
#include <AST/statement/statement.h>
#include <memory>

namespace vecc::ast {
  /**
   * Class describing return statement
   */
  class ReturnStatement : public Statement {
  public:
    /**
     * Constructor
     * @param expression Expression which value is returned
     */
    explicit ReturnStatement(std::unique_ptr<Expression> expression =
                                 std::unique_ptr<Expression>(nullptr));

    /**
     * Runs statement
     * @return return value
     */
    Return run() override;

  private:
    std::unique_ptr<Expression> expression_;
  };
} // namespace vecc::ast

#endif // VECC_LANG_RETURN_STMT_H
