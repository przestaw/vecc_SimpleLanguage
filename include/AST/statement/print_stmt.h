//
// Created by przemek on 23.03.2020.
//

#ifndef VECC_LANG_PRINT_STMT_H
#define VECC_LANG_PRINT_STMT_H

#include <AST/expression/expression.h>
#include <AST/statement/statement.h>
#include <iostream>
#include <memory>
#include <variant>

namespace vecc::ast {
  /**
   * Class describing print statement
   */
  class PrintStatement : public Statement {
  public:
    /**
     * Constructor
     * @param out stream where statement will be outputted
     */
    explicit PrintStatement(std::ostream &out = std::cout);

    /**
     * Expression to be printed
     * @param expression expression to be printed
     */
    void addExpression(std::unique_ptr<Expression> expression);

    /**
     * String constant to be printed
     * @param string string to be printed
     */
    void addString(std::string string);

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
    std::ostream &out_;

    struct Printable {
      explicit Printable(std::unique_ptr<Expression> val)
          : expression(true), value(std::move(val)) {}

      explicit Printable(std::string val)
          : expression(false), value(std::move(val)) {}

      bool expression;
      std::variant<std::unique_ptr<Expression>, std::string> value;
    };

    std::vector<Printable> printables;
  };
} // namespace vecc::ast

#endif // VECC_LANG_PRINT_STMT_H
