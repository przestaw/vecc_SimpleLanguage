//
// Created by przemek on 13.03.2020.
//

#include "scanner/reader.h"

using namespace vecc;

Reader::Reader() : stream_(nullptr) {}

Reader::Reader(std::istream *input) : stream_(input) {}

unsigned char Reader::get() const {
    return symbol_;
}

unsigned char Reader::peek() {
    return stream_->peek();
}

const Position &Reader::getCurrentPos() const {
    return position_;
}
