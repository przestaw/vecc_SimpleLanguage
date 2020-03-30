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
            position_.incrementLine();

        } // else -> CRLF LFCR
    } else {
        position_.incrementSymbol();
    }
    lastSymbol_ = symbol_;

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
