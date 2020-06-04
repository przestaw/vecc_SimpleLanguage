//
// Created by przemek on 23.03.2020.
//

#ifndef VECC_LANG_FUNCTION_CALL_H
#define VECC_LANG_FUNCTION_CALL_H

#include <AST/expression/expression.h>
#include <AST/general/function.h>
#include <AST/statement/statement.h>

namespace vecc::ast {
  /**
   * Class describing function call
   */
  class FunctionCallStatement : public Statement {
  public:
    /**
     * Constructor
     * @param function Function to be called
     */
    explicit FunctionCallStatement(Function &function);

    /**
     * Adds argument to a call
     * @param arg Argument Expression
     */
    void addArgument(std::unique_ptr<Expression> arg);

    /**
     * Returns function definition
     * @return function definition
     */
    [[nodiscard]] const Function &getFunction() const;

    /**
     * Runs statement
     * @return return value
     */
    Return run() override;

    /**
     * Returns number of arguments
     * @return number of arguments
     */
    [[nodiscard]] unsigned size() const;

    /**
     * Returns simplified AST representation
     * @return simplified AST
     */
    [[nodiscard]] std::string toString() const override;

  private:
    Function &function_;
    std::list<std::unique_ptr<Expression>> arguments_;
  };
} // namespace vecc::ast

#endif // VECC_LANG_FUNCTION_CALL_H
