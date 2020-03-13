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
        Reader();
        Reader(std::istream &input);

        unsigned char get() const;
        unsigned char peek();
        const Position &getCurrentPos() const;

        // waht else?
        // TODO : interface, more tests & implement
    private:
        std::istream &stream_;       //!< stream cannot be changed as Reader holds position in code

        unsigned char symbol_ = 0x00;
        Position position_;
        unsigned char lastSymbol_ = 0x00; //!< to detect different line endings
    };

}

#endif //PROJECT_READER_H
