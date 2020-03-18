//
// Created by przemek on 18.03.2020.
//

#ifndef VECC_LANG_VECC_EXECEPTION_H
#define VECC_LANG_VECC_EXECEPTION_H

#include <iostream>
#include <stdexcept>
#include <scanner/token.h>

namespace vecc {
    class Exception : public std::runtime_error {
    public:
        explicit Exception(const std::string& desc) : runtime_error(desc) {
            std::cerr << desc;
        }
    };

    class NotAToken : public Exception {
    public:
        explicit NotAToken(const Token& token) : Exception("Unknown token : " + token.toString()) {}
    };

    class NoInputStream : public Exception {
    public:
        explicit NoInputStream() : Exception("No input stream to read - " FRED("nullptr")) {}
    };
}

#endif //VECC_LANG_VECC_EXECEPTION_H
