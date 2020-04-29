//
// Created by przemek on 19.03.2020.
//

#ifndef VECC_LANG_FUNCTION_H
#define VECC_LANG_FUNCTION_H

#include <AST/general/return.h>
#include <AST/general/variable.h>
#include <AST/statement/statement_block.h>
#include <string>
#include <vector>

namespace vecc::ast {
  /**
   * Class describin Function definition
   */
  class Function {
  public:
    /**
     * Constructor
     * @param identifier function name
     */
    explicit Function(std::string identifier);

    /**
     * Adds function parameter
     * @param identifier parameter name
     */
    void addParameter(const std::string &identifier);

    /**
     * Returns number of arguments
     * @return number of arguments
     */
    unsigned size() const;

    /**
     * Returns function name
     * @return function name
     */
    const std::string &getIdentifier() const;

    /**
     * Runs statement
     * @return return value
     */
    Return
    run(const std::vector<Variable> &parameters = std::vector<Variable>());

    /**
     * Returns reference to function body
     * @return function body reference
     */
    StatementBlock &getFunctionBody();

  private:
    const std::string identifier_;   //!< function identifier/name
    std::vector<std::string> names_; //!< Parameters names
    StatementBlock functionBody_;    //!< Function Body
  };
} // namespace vecc::ast

#endif // VECC_LANG_FUNCTION_H
