//
// Created by przemek on 13.03.2020.
//

#ifndef PROJECT_READER_H
#define PROJECT_READER_H

#include "scanner/position.h"
#include <iostream>

namespace vecc {

  /**
   * Reader abstraction providing stream and position in source
   */
  class Reader {
  public:
    /**
     * Constructor
     * @param input source stream
     */
    explicit Reader(std::istream &input);

    /**
     * Constructor
     * @param input source stream
     * @param source source name
     */
    Reader(std::istream &input, const std::string &source);

    /**
     * Obtains next character in stream and consumes it
     * @return next character in stream
     */
    char get();

    /**
     * Peeks next character in stream
     * @return next character in stream
     */
    char peek();

    /**
     * Returns current Position
     * @return current Position
     */
    [[nodiscard]] const Position &getCurrentPos() const;

    /**
     * Checks if End of File has been reached
     * @return EoF flag
     */
    [[nodiscard]] bool isEoF() const;

  private:
    std::istream
        &stream_; //!< stream cannot be changed as Reader holds position in code

    char symbol_ = 0x00; //!< current symbol
    Position position_;  //!< current symbol position

    char lastSymbol_ = 0x00; //!< to detect different line endings
  };

} // namespace vecc

#endif // PROJECT_READER_H
