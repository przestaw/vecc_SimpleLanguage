//
// Created by przemek on 19.03.2020.
//

#ifndef VECC_LANG_PARSER_H
#define VECC_LANG_PARSER_H

#include <AST/expression/expression.h>
#include <AST/statement/statement.h>
#include <AST/statement/statement_block.h>
#include <error/exeception.h>

#include <AST/general/function.h>
#include <AST/general/program.h>
#include <scanner/reader.h>
#include <scanner/scanner.h>
#include <scanner/token.h>

namespace vecc {
  /**
   * Class used to generate AST for given sources in form of vecc::ast::Program
   */
  class Parser {
  public:
    /**
     * Constructor without initial source
     * @param logLevel log level
     * @param out output stream
     */
    explicit Parser(error::Logger &logger = error::Logger::noLogger,
                    std::ostream &out     = std::cout);

    /**
     * Constructor with initial source
     * @param source initial source
     * @param logLevel log level
     * @param out output stream
     */
    explicit Parser(std::unique_ptr<Reader> source,
                    error::Logger &logger = error::Logger::noLogger,
                    std::ostream &out     = std::cout);

    /**
     * Sets current source
     * @param source source to be set
     */
    void setSource(std::unique_ptr<Reader> source);

    /**
     * Parses internal source
     */
    void parse();

    /**
     * Obtains program and clears Parser
     * @return parsed program
     */
    std::unique_ptr<ast::Program> getProgram();

  private:
    error::Logger &logger_;
    std::ostream &out_; //!< output stream for print

    std::unique_ptr<Scanner>
        scanner_; //!< Internal scanner providing tokens stream
    std::unique_ptr<ast::Program> currentProgram; //!< Currently parsed Program

    ast::Context *currentContext =
        nullptr; //!< Current context [connected with code logic]

    /**
     * Check if next token is of given type, adn consumes it if so
     * @param type expected Token type
     * @return true on sucess
     */
    inline bool tryConsumeToken(const Token::Type &type) {
      if (scanner_->getToken().getType() == type) {
        scanner_->readToken();
        return true;
      } else {
        return false;
      }
    };

    /**
     * Check if next token is of given type and execute action if so.
     * Throws exception if token has not been encountered
     * @param type expected Token type
     */
    inline void expectNextToken(const Token::Type type) {
      if (scanner_->getToken().getType() != type)
        throw error::UnexpectedToken(scanner_->getToken(), {type});
    };

    // Utility function
    inline void parseFunctionDef();

    inline void parseParameters(ast::Function &def);

    inline void parseStatementBlock(ast::StatementBlock &newBlock);

    inline ast::Variable parseVectorValue();

    // Statements
    inline std::unique_ptr<ast::Statement>
    parseAssignStatement(ast::Variable *variable);

    inline std::unique_ptr<ast::Statement> parseInitStatement();

    inline std::unique_ptr<ast::Statement> parseIdentifier();

    inline std::unique_ptr<ast::Statement>
    parseFunctionCall(const Token &function);

    inline std::unique_ptr<ast::Statement> parseIfStatement();

    inline std::unique_ptr<ast::Statement> parseWhileStatement();

    inline std::unique_ptr<ast::Statement> parseReturnStatement();

    inline std::unique_ptr<ast::Statement> parsePrintStatement();

    // Expressions
    inline std::unique_ptr<ast::Expression> parseOrExpression();

    inline std::unique_ptr<ast::Expression> parseAndExpression();

    inline std::unique_ptr<ast::Expression> parseRelationalExpression();

    inline std::unique_ptr<ast::Expression> parseBaseLogicExpression();

    inline std::unique_ptr<ast::Expression> parseAdditiveExpression();

    inline std::unique_ptr<ast::Expression> parseMultiplyExpression();

    inline std::unique_ptr<ast::Expression> parseBaseMathExpression();

    inline std::unique_ptr<ast::Expression>
    parseParentExpression(const bool &unaryMathOp);

    inline std::unique_ptr<ast::Expression>
    parseIdentifierValue(const bool &unaryMathOp);
  };
} // namespace vecc

#endif // VECC_LANG_PARSER_H
