//
// Created by przemek on 19.03.2020.
//

#ifndef VECC_LANG_PARSER_H
#define VECC_LANG_PARSER_H

#include <AST/statement/statement.h>
#include <error/exeception.h>
#include "scanner/reader.h"
#include "scanner/scanner.h"
#include "AST/general/program.h"

namespace vecc {
    class Parser{
    public:
        Parser();
        Parser(std::unique_ptr<Reader> source);
        //Parser(Scanner scan); // FIXME : is it needed? will i change scanner for any reason
        //void setlexer(Scanner scan);
        void setSource(std::unique_ptr<Reader> source);

        //Program parse();    // FIXME : run multiple times as source changes?
        // FIXME : may be replaced with :
        void parse();
        std::unique_ptr<Program> getProgram();

        void cleanParser(); // to clean AST tree / new program

    private:
        std::unique_ptr<Scanner> scanner_;
        std::unique_ptr<Program> currentProgram;

        /**
         * Check if next token is of given type and execute action if so
         * @param type expected Token type
         * @param ifTrue action if token has been encountered
         * @return true on sucess
         */
        bool tryToken(Token::Type type, std::function<void()> ifTrue = std::function<void()>());

        /**
         * Check if next token is of given type and execute action if so.
         * Throws exception if token has not been encountered
         * @param type expected Token type
         * @param ifTrue action if token has been encountered
         */
        inline void expectToken(const Token::Type type, const std::function<void()> ifTrue = std::function<void()>()) {
            if(!tryToken(type, ifTrue))
                throw Exception("expected token : " "TODO");
        }

        std::unique_ptr<Statement> parsePrintStatement();
    };
}

#endif //VECC_LANG_PARSER_H
