//
// Created by przemek on 18.03.2020.
//

#ifndef VECC_LANG_EXECEPTION_H
#define VECC_LANG_EXECEPTION_H

#include <iostream>
#include <stdexcept>
#include <scanner/token.h>

namespace vecc {
    class Exception : public std::runtime_error {
    public:
        explicit Exception(const std::string& desc) : runtime_error(desc), value(desc) {}
        virtual const std::string &getMessage() {return value;}
    protected:
        std::string value;
    };

    class NotAToken : public Exception {
    public:
        explicit NotAToken(const Token &token) : Exception(FMAG(BOLD("Token ERROR : \n")) "Unknown token : " + token.toString()) {}
    };

    class NoInputStream : public Exception {
    public:
        explicit NoInputStream() : Exception(FMAG(BOLD("Stream ERROR : \n")) "No input stream to read - " FRED("nullptr")) {}
    };
}

#endif //VECC_LANG_EXECEPTION_H
