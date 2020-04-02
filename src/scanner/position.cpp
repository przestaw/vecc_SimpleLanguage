//
// Created by przemek on 13.03.2020.
//

#include "scanner/position.h"

#include <sstream>

using namespace vecc;

Position::Position()
        : lineNo(1),
          symbolNo(0),
          linePos(),
          symbolPos() {}

bool Position::operator==(const Position &rhs) const {
    return lineNo == rhs.lineNo &&
           symbolNo == rhs.symbolNo &&
           linePos == rhs.linePos &&
           symbolPos == rhs.symbolPos;
}

bool Position::operator!=(const Position &rhs) const {
    return !(rhs == *this);
}

bool Position::operator<(const Position &rhs) const {
    if (lineNo < rhs.lineNo)
        return true;
    if (rhs.lineNo < lineNo)
        return false;
    return symbolNo < rhs.symbolNo;
}

bool Position::operator>(const Position &rhs) const {
    return rhs < *this;
}

bool Position::operator<=(const Position &rhs) const {
    return !(rhs < *this);
}

bool Position::operator>=(const Position &rhs) const {
    return !(*this < rhs);
}