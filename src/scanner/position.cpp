//
// Created by przemek on 13.03.2020.
//

#include "scanner/position.h"

#include <sstream>

using namespace vecc;

Position::Position()
        : lineNumber(1),
          signNumber(0),
          linePosition(linePosition),
          signPosition(signPosition) {}

bool Position::operator==(const Position &rhs) const {
    return lineNumber == rhs.lineNumber &&
           signNumber == rhs.signNumber &&
           linePosition == rhs.linePosition &&
           signPosition == rhs.signPosition;
}

bool Position::operator!=(const Position &rhs) const {
    return !(rhs == *this);
}

bool Position::operator<(const Position &rhs) const {
    if (lineNumber < rhs.lineNumber)
        return true;
    if (rhs.lineNumber < lineNumber)
        return false;
    return signNumber < rhs.signNumber;
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