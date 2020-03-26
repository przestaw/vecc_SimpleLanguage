//
// Created by przemek on 13.03.2020.
//

#ifndef PROJECT_READER_H
#define PROJECT_READER_H

#include <iostream>
#include "scanner/position.h"

namespace vecc {

    class Reader {
    public:
        explicit Reader(std::istream &input, const std::string &source = "unknown");

        char get();

        char peek();

        const Position &getCurrentPos() const;

        bool isEoF() const;

    private:
        std::istream &stream_;       //!< stream cannot be changed as Reader holds position in code
        std::string sourceName;      //!< identifer of the source

        char symbol_ = 0x00;
        Position position_;
        char lastSymbol_ = 0x00; //!< to detect different line endings
    };

}

#endif //PROJECT_READER_H
