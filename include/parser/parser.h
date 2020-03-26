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
#include "scanner/reader.h"
#include "scanner/scanner.h"
#include "AST/general/program.h"

namespace vecc {
    class Parser{
    public:
        explicit Parser(std::ostream &out = std::cout);
        explicit Parser(std::unique_ptr<Reader> source, std::ostream &out = std::cout);

        void setSource(std::unique_ptr<Reader> source);

        //Program parse();    // FIXME : run multiple times as source changes?
        // FIXME : may be replaced with :
        void parse();
        std::unique_ptr<Program> getProgram();

        void cleanParser(); // to clean AST tree / new program

    private:
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
        bool tryToken(Token::Type type, const std::function<void()>& ifTrue = std::function<void()>());

        /**
         * Check if next token is of given type and execute action if so.
         * Throws exception if token has not been encountered
         * @param type expected Token type
         * @param ifTrue action if token has been encountered
         */
        inline void expectToken(const Token::Type type, const std::function<void()> ifTrue = std::function<void()>()) {
            if(!tryToken(type, ifTrue))
                throw UnexpectedToken(scanner_->getToken(), {type});
        }

        void parseFunctionDef();
        void parseParameters(Function &def);

        void parseStatementBlock(StatementBlock &newBlock);

        Variable parseVectorValue();

        std::unique_ptr<Statement> parseAssignStatement(std::weak_ptr<Variable> variable);
        std::unique_ptr<Statement> parseIdentifier(const Token &identifier);
        std::unique_ptr<Statement> parseFunctionCall(const Token &function);
        std::unique_ptr<Statement> parseIfStatement();
        std::unique_ptr<Statement> parseWhileStatement();
        std::unique_ptr<Statement> parseReturnStatement();
        std::unique_ptr<Statement> parsePrintStatement();

        std::unique_ptr<Expression> parseOrExpression();
        std::unique_ptr<Expression> parseAndExpression();
        std::unique_ptr<Expression> parseRelationalExpression();
        std::unique_ptr<Expression> parseBaseLogicExpression();
        std::unique_ptr<Expression> parseAdditiveExpression();
        std::unique_ptr<Expression> parseMultiplyExpression();
        std::unique_ptr<Expression> parseBaseMathExpression();
    };
}

#endif //VECC_LANG_PARSER_H
