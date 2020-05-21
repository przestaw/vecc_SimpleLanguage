//
// Created by przemek on 13.03.2020.
//

#ifndef VECC_LANG_SCANNER_H
#define VECC_LANG_SCANNER_H

#include "scanner/reader.h"
#include "scanner/token.h"
#include <memory>
#include <vecc_include.h>

namespace vecc {

  /**
   * Scanner abstraction providing stream of Tokens from given source
   */
  class Scanner {
  public:
    /**
     * @param input input stream
     * @param logLevel LogLevel determining if anything needs to be logged
     * @param out log out stream
     */
    explicit Scanner(std::istream &input,
                     const LogLevel &logLevel = LogLevel::NoLog,
                     std::ostream &out        = std::cout);

    /**
     * @param reader Reader
     * @param logLevel LogLevel determining if anything needs to be logged
     * @param out log out stream
     */
    explicit Scanner(std::unique_ptr<Reader> reader,
                     const LogLevel &logLevel = LogLevel::NoLog,
                     std::ostream &out        = std::cout);

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

  private:
    std::unique_ptr<Reader> reader_;
    LogLevel logLevel_; //!< Log level
    std::ostream &out_; //!< output stream for logs
    Token currentToken; //!< Current Token storage

    inline void tryToken();

    inline void tryKeywordOrIdentifier(const Position &tokenStartPos);

    inline void tryCharString(const Position &tokenStartPos);

    inline void tryNumberString(const Position &tokenStartPos);

    inline void tryOperatorOrBracket(const Position &tokenStartPos);
  };
} // namespace vecc
#endif // VECC_LANG_SCANNER_H