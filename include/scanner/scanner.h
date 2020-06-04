//
// Created by przemek on 13.03.2020.
//

#ifndef VECC_LANG_SCANNER_H
#define VECC_LANG_SCANNER_H

#include "scanner/reader.h"
#include "scanner/token.h"
#include <error/logger.h>
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
     * @param logger logging output
     */
    explicit Scanner(std::istream &input,
                     error::Logger &logger = error::Logger::noLogger);

    /**
     * @param reader Reader
     * @param logger logging output
     */
    explicit Scanner(std::unique_ptr<Reader> reader,
                     error::Logger &logger = error::Logger::noLogger);

    /**
     * Obtains current Token
     * @return current Token
     */
    Token getToken();

    /**
     * Parses next Token and returns it
     * @return next Token
     */
    Token readToken();

  private:
    std::unique_ptr<Reader> reader_;
    error::Logger logger_;
    Token currentToken; //!< Current Token storage

    inline void tryToken();

    inline void tryKeywordOrIdentifier(const Position &tokenStartPos);

    inline void tryCharString(const Position &tokenStartPos);

    inline void tryNumberString(const Position &tokenStartPos);

    inline void tryOperatorOrBracket(const Position &tokenStartPos);
  };
} // namespace vecc
#endif // VECC_LANG_SCANNER_H