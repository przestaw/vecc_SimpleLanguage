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
        explicit Exception(const std::string &desc) : runtime_error(desc) {}
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
            FRED(BOLD("Undefined Variable ERROR : ")) "Variable " + token.getLiteral() + " not found"
            + "\nat line: " + token.getTokenPos().toString()) {}
    };

    class RedefinedVar : public Exception {
    public:
        explicit RedefinedVar(const Token &token) : Exception(
            FRED(BOLD("Redefined Variable ERROR : ")) "Variable " + token.getLiteral() + " has been redefined"
            + "\nat line: " + token.getTokenPos().toString()) {}
    };

    class UndefinedFun : public Exception {
    public:
        explicit UndefinedFun(const Token &function) : Exception(
            FRED(BOLD("Undefined Function ERROR : ")) "Function " + function.getLiteral() +
            " has not been defined\nat line: " + function.getTokenPos().toString()) {}
    };

    class RedefinedFun : public Exception {
    public:
        explicit RedefinedFun(const Token &function) : Exception(
            FRED(BOLD("Redefined Function ERROR : ")) "Function " + function.getLiteral() + " is already defined"
            + "\nat line: " + function.getTokenPos().toString()) {}
    };

    class MismachedArgumentsCount : public Exception {
    public:
        explicit MismachedArgumentsCount(const Token &function, const unsigned &funCount, const unsigned &callCount) : Exception(
            FRED(BOLD("Function Call ERROR : ")) "Function " + function.getLiteral() +
            " has " + std::to_string(funCount) + " arguments but " + std::to_string(callCount) + "were provided"
            + "\nat line: " + function.getTokenPos().toString()) {}
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
