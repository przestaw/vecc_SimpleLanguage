//
// Created by przemek on 19.03.2020.
//

#ifndef VECC_LANG_STATEMENT_BLOCK_H
#define VECC_LANG_STATEMENT_BLOCK_H

#include <AST/general/context.h>
#include <AST/statement/statement.h>
#include <list>
#include <memory>

namespace vecc::ast {
  /**
   *
   */
  class StatementBlock : public Statement {
  public:
    /**
     * Constructor
     * @param parentContext parent context in which StatementBlock exists
     */
    explicit StatementBlock(Context *parentContext = nullptr);

    /**
     * Adds statement to the end of the block
     * @param statement statement to be added
     */
    void addInstruction(std::unique_ptr<Statement> statement);

    /**
     * Adds new variable to the StatementBlock Context
     * @param identifier new Variable identifier
     */
    void addVariable(const std::string &identifier);

    /**
     * Returns variable by it's identifier
     * @param identifier variable identifier
     * @return shared_ptr to the variable
     */
    Variable &findVariable(const std::string &identifier);

    /**
     * Returns reference to StatementBlock internal Context
     * @return reference to StatementBlock internal Context
     */
    Context &getContext();

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
    std::list<std::unique_ptr<Statement>> statements_;
    Context context_;
  };
} // namespace vecc::ast

#endif // VECC_LANG_STATEMENT_BLOCK_H
