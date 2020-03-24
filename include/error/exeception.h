//
// Created by przemek on 18.03.2020.
//

#ifndef VECC_LANG_EXECEPTION_H
#define VECC_LANG_EXECEPTION_H

#include <iostream>
#include <stdexcept>
#include <list>
#include <scanner/token.h>

namespace vecc {
    class Exception : public std::runtime_error {
    public:
        explicit Exception(const std::string &desc) : runtime_error(desc), value(desc) {}

        virtual const std::string &getMessage() { return value; }

    protected:
        std::string value;
    };

    class NotAToken : public Exception {
    public:
        explicit NotAToken(const Token &token) : Exception(
                FMAG(BOLD("Token ERROR : \n")) "Unknown token : " + token.toString()) {}
    };

    class NoInputStream : public Exception {
    public:
        explicit NoInputStream() : Exception(
                FMAG(BOLD("Stream ERROR : \n")) "No input stream to read - " FRED("nullptr")) {}
    };

    class UnexpectedToken : public Exception {
    public:
        explicit UnexpectedToken(const Token &token, const std::list<Token::Type> &expected = std::list<Token::Type>())
                : Exception(
                [&]() {
                    std::string buf = FRED(BOLD("Unexpected Token ERROR : \n"));
                    buf.append("Got " + token.typeName());
                    if (!expected.empty()) {
                        buf.append("but expected : \n");
                        for (auto &it: expected) {
                            buf.append("\t" + Token::getTypeName(it) + "\n");
                        }
                    }
                    return buf;
                }()
                + " at " + token.getTokenPos().toString()) {}
    };

    class UndefinedVar : public Exception {
    public:
        explicit UndefinedVar(const Token &token) : Exception(
                FRED(BOLD("Undefined Variable ERROR : ")) "Variable " + token.getLiteral() + " not found\nat line: " +
                token.getTokenPos().toString()) {}
    };

    class UndefinedFun : public Exception {
    public:
        explicit UndefinedFun(const std::string &desc) : Exception(FRED(BOLD("Undefined Function ERROR : ")) + desc) {}
    };

    class NoReturnValue : public Exception {
    public:
        explicit NoReturnValue(const std::string &desc) : Exception(FRED(BOLD("No Return Value ERROR : ")) + desc) {}
    };

    class MathException : public Exception {
    public:
        explicit MathException(const std::string &desc) : Exception(FYEL(BOLD("Math ERROR : \n")) + desc) {}
    };

    class RangeException : public Exception {
    public:
        explicit RangeException(const std::string &desc) : Exception(FYEL(BOLD("Range ERROR : \n")) + desc) {}
    };
}

#endif //VECC_LANG_EXECEPTION_H
