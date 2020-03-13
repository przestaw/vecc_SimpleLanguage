//
// Created by przemek on 13.03.2020.
//

#include "reader.h"

using namespace vecc;

Reader::Reader() : stream_(nullptr) {}

Reader::Reader(std::istream *input) : stream_(input) {}
