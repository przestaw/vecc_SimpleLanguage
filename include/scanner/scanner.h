//
// Created by przemek on 13.03.2020.
//

#ifndef VECC_LANG_SCANNER_H
#define VECC_LANG_SCANNER_H

#include <memory>
#include <vecc_include.h>
#include "scanner/token.h"
#include "scanner/reader.h"

namespace vecc {

    /**
     * Scanner abstraction providing stream of Tokens from given source
     */
    class Scanner {
    public:
        /**
         * Constructor for Scanner with empty Reader
         * @param logLevel LogLevel determining if anything needs to be logged
         * @param out log out stream
         */
        explicit Scanner(const LogLevel &logLevel = LogLevel::NoLog,
                         std::ostream &out = std::cout);

        /**
         *
         * @param reader initial Reader
         * @param logLevel LogLevel determining if anything needs to be logged
         * @param out log out stream
         */
        explicit Scanner(std::unique_ptr<Reader> reader,
                         const LogLevel &logLevel = LogLevel::NoLog,
                         std::ostream &out = std::cout);

        /**
         * Obtains current Token
         * @return current Token
         */
        Token getToken();

        /**
         * Parses next Token and returns it
         * @return next Token
         */
        Token parseToken();

        /**
         * Sets current Reader
         * @param reader Reader
         */
        void setReader(std::unique_ptr<Reader> reader);

    private:
        LogLevel logLevel_;                 //!< Log level
        std::ostream &out_;                 //!< output stream for logs

        std::unique_ptr<Reader> reader_;    //!< Internal reader
        Token currentToken;                 //!< Current Token storage


        inline bool canRead(); // use built-in std::unique_ptr check if ptr is "valid" (!= nullptr)

        inline void tryToken();

        inline void tryKeyword();

        inline void tryCharString();

        inline void tryNumberString();

        inline void tryOperatorOrBracket();
    };
}
#endif //VECC_LANG_SCANNER_H