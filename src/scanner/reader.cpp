//
// Created by przemek on 13.03.2020.
//

#include "scanner/reader.h"

using namespace vecc;

Reader::Reader(std::istream &input, const std::string &source) : stream_(input), sourceName(source) {}

char Reader::get() {
    //TODO read next, calc position
    stream_.get(symbol_);
    if (symbol_ == '\n' || symbol_ == '\r') {
        if (lastSymbol_ == symbol_ ||
            (lastSymbol_ != '\n' && lastSymbol_ != '\r')) {
            // to allow LF CR an CRLF line endings
            position_.lineNo++;
            position_.symbolNo = 0;
            position_.linePos = stream_.tellg();
        } // else -> CRLF LFCR
    } else {
        position_.symbolNo++;
    }
    lastSymbol_ = symbol_;
    position_.symbolPos = stream_.tellg();

    return symbol_;
}

char Reader::peek() {
    return stream_.peek();
}

const Position &Reader::getCurrentPos() const {
    return position_;
}

bool Reader::isEoF() const {
    return stream_.eof();
}
