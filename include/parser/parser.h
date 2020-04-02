//
// Created by przemek on 19.03.2020.
//

#ifndef VECC_LANG_PARSER_H
#define VECC_LANG_PARSER_H

#include <error/exeception.h>
#include <AST/statement/statement.h>
#include <AST/statement/statement_block.h>
#include <AST/expression/expression.h>

#include <AST/general/function.h>
#include <AST/general/program.h>
#include <scanner/scanner.h>
#include <scanner/reader.h>
#include <scanner/token.h>

namespace vecc {
    class Parser {
    public:
        explicit Parser(const LogLevel &logLevel = LogLevel::NoLog, std::ostream &out = std::cout);
        
        explicit Parser(std::unique_ptr<Reader> source, const LogLevel &logLevel = LogLevel::NoLog, std::ostream &out = std::cout);
        
        void setSource(std::unique_ptr<Reader> source);
        
        void parse();
        
        std::unique_ptr<Program> getProgram();
    
    private:
        LogLevel logLevel_;
        std::ostream &out_;
        std::unique_ptr<Scanner> scanner_;
        std::unique_ptr<Program> currentProgram;
        
        Context *currentContext = nullptr;
        
        /**
         * Check if next token is of given type and execute action if so
         * @param type expected Token type
         * @param ifTrue action if token has been encountered
         * @return true on sucess
         */
        inline bool tryToken(const Token::Type &type, const std::function<void()> &ifTrue = std::function<void()>()) {
            if (scanner_->getToken().getType() == type) {
                if (ifTrue) {
                    ifTrue();
                }
                scanner_->parseToken();
                return true;
            } else {
                return false;
            }
        };
        /**
         * Check if next token is of given type and execute action if so.
         * Throws exception if token has not been encountered
         * @param type expected Token type
         * @param ifTrue action if token has been encountered
         */
        inline void expectToken(const Token::Type type, const std::function<void()>& ifTrue = std::function<void()>()) {
            if (!tryToken(type, ifTrue))
                throw UnexpectedToken(scanner_->getToken(), {type});
        };
        
        // Utility function
        inline void parseFunctionDef();
        inline void parseParameters(Function &def);
        inline void parseStatementBlock(StatementBlock &newBlock);
        inline Variable parseVectorValue();
        
        // Statements
        inline std::unique_ptr<Statement> parseAssignStatement(std::weak_ptr<Variable> variable);
        inline std::unique_ptr<Statement> parseInitStatement();
        inline std::unique_ptr<Statement> parseIdentifier();
        inline std::unique_ptr<Statement> parseFunctionCall(const Token &function);
        inline std::unique_ptr<Statement> parseIfStatement();
        inline std::unique_ptr<Statement> parseWhileStatement();
        inline std::unique_ptr<Statement> parseReturnStatement();
        inline std::unique_ptr<Statement> parsePrintStatement();
        
        // Expressions
        inline std::unique_ptr<Expression> parseOrExpression();
        inline std::unique_ptr<Expression> parseAndExpression();
        inline std::unique_ptr<Expression> parseRelationalExpression();
        inline std::unique_ptr<Expression> parseBaseLogicExpression();
        inline std::unique_ptr<Expression> parseAdditiveExpression();
        inline std::unique_ptr<Expression> parseMultiplyExpression();
        inline std::unique_ptr<Expression> parseBaseMathExpression();
        inline std::unique_ptr<Expression> parseParentExpression(const bool &unaryMathOp);
        inline std::unique_ptr<Expression> parseIdentifierValue(const bool &unaryMathOp);
    };
}

#endif //VECC_LANG_PARSER_H
