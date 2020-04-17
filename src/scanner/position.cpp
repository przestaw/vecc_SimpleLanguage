//
// Created by przemek on 13.03.2020.
//

#include "scanner/position.h"

#include <sstream>
#include <utility>

using namespace vecc;

Position::Position()
        : lineNo(1),
          symbolNo(0),
          namedSource(false) {}

Position::Position(std::string source)
        : lineNo(1),
          symbolNo(0),
          namedSource(true),
          sourceName(std::move(source)) {}

Position::Position(unsigned line, unsigned symbol)
        : lineNo(line),
          symbolNo(symbol),
          namedSource(false) {}

Position::Position(unsigned line, unsigned symbol, std::string streamName)
        : lineNo(line),
          symbolNo(symbol),
          namedSource(true),
          sourceName(std::move(streamName)) {}

bool Position::operator==(const Position &rhs) const {
    return lineNo == rhs.lineNo &&
           symbolNo == rhs.symbolNo &&
           (namedSource == rhs.namedSource) &&
           (namedSource ? true : sourceName == rhs.sourceName);
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
