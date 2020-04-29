//
// Created by przemek on 18.03.2020.
//

#ifndef VECC_LANG_EXECEPTION_H
#define VECC_LANG_EXECEPTION_H

#include <iostream>
#include <list>
#include <scanner/token.h>
#include <stdexcept>

namespace vecc {
  namespace error {
    /**
     * Exception class used as base type for vecc exceptions
     */
    class Exception : public std::runtime_error {
    public:
      /**
       * Constructor
       * @param desc error description
       */
      explicit Exception(const std::string &desc) : runtime_error(desc) {}
    };

    /**
     * ParseException class used as base type for vecc parse phase exceptions
     */
    class ParseException : public Exception {
    public:
      /**
       * Constructor
       * @param desc error description
       */
      explicit ParseException(const std::string &desc) : Exception(desc) {}
    };

    /**
     * RuntimeException class used as base type for vecc runtime phase
     * exceptions
     */
    class RuntimeException : public Exception {
    public:
      /**
       * Constructor
       * @param desc error description
       */
      explicit RuntimeException(const std::string &desc) : Exception(desc) {}
    };

    /**
     * Class describing undefined tokens exception
     */
    class NotAToken : public ParseException {
    public:
      /**
       * Constructor
       * @param token on which error occurred
       */
      explicit NotAToken(const Token &token)
          : ParseException(FMAG(BOLD("Token ERROR : \n")) "Unknown token : "
                           + token.toString()) {}
    };

    /**
     * Class used to inform about missing input stream
     */
    class NoInputStream : public ParseException {
    public:
      /**
       * Constructor
       */
      explicit NoInputStream()
          : ParseException(
              FMAG(BOLD("Stream ERROR : \n")) "No input stream to read - " FRED(
                  "nullptr")) {}
    };

    /**
     * Class describing unexpected tokens errors
     */
    class UnexpectedToken : public ParseException {
    public:
      /**
       * Constructor
       * @param token on which error occurred
       * @param expected expected tokens
       */
      explicit UnexpectedToken(
          const Token &token,
          const std::list<Token::Type> &expected = std::list<Token::Type>())
          : ParseException([&]() {
              std::string buf = FRED(BOLD("Unexpected Token ERROR : \n"));
              buf.append("Got " + token.typeName());
              if (!expected.empty()) {
                buf.append(" but expected : \n");
                for (auto &it : expected) {
                  buf.append("\t" + Token::getTypeName(it) + "\n");
                }
              }
              return buf;
            }() + "at " + token.getTokenPos().toString()) {}
    };

    /**
     * Class describing undefined variable errors
     */
    class UndefinedVar : public ParseException {
    public:
      /**
       * Constructor
       * @param token on which error occurred
       */
      explicit UndefinedVar(const Token &token)
          : ParseException(
              FRED(BOLD("Undefined Variable ERROR : \n")) "Variable "
              + token.getLiteral() + " not found"
              + "\nat line: " + token.getTokenPos().toString()) {}
    };

    /**
     * Class describing redefined variable errors
     */
    class RedefinedVar : public ParseException {
    public:
      /**
       * Constructor
       * @param token on which error occurred
       */
      explicit RedefinedVar(const Token &token)
          : ParseException(
              FRED(BOLD("Redefined Variable ERROR : \n")) "Variable "
              + token.getLiteral() + " has been redefined"
              + "\nat line: " + token.getTokenPos().toString()) {}
    };

    /**
     * Class describing undefined function errors
     */
    class UndefinedFun : public ParseException {
    public:
      /**
       * Constructor
       * @param function function on which error occurred
       */
      explicit UndefinedFun(const Token &function)
          : ParseException(
              FRED(BOLD("Undefined Function ERROR : \n")) "Function "
              + function.getLiteral() + " has not been defined\nat line: "
              + function.getTokenPos().toString()) {}
    };

    /**
     * Class describing undefined main function errors
     */
    class UndefinedMain : public RuntimeException {
    public:
      /**
       * Constructor
       */
      explicit UndefinedMain()
          : RuntimeException(
              FRED(BOLD("Undefined Function ERROR : \n")) "Function main has "
                                                          "not been defined") {}
    };

    /**
     * Class describing redefined function errors
     */
    class RedefinedFun : public ParseException {
    public:
      /**
       * Constructor
       * @param function function on which error occurred
       */
      explicit RedefinedFun(const Token &function)
          : ParseException(
              FRED(BOLD("Redefined Function ERROR : \n")) "Function "
              + function.getLiteral() + " is already defined"
              + "\nat line: " + function.getTokenPos().toString()) {}
    };

    /**
     * Class describing invalid function call errors - with mismatched arguments
     * count
     */
    class MismatchedArgumentsCount : public ParseException {
    public:
      /**
       * Constructor
       * @param function function on which error occurred
       * @param funCount function arguments count
       * @param callCount call arguments count
       */
      explicit MismatchedArgumentsCount(const Token &function,
                                        const unsigned &funCount,
                                        const unsigned &callCount)
          : ParseException(
              FRED(BOLD("Function Call ERROR : \n")) "Function "
              + function.getLiteral() + " has " + std::to_string(funCount)
              + " arguments but " + std::to_string(callCount) + "were provided"
              + "\nat line: " + function.getTokenPos().toString()) {}
    };

    /**
     * Class describing invalid function call errors - without return statement
     */
    class NoReturnValue : public RuntimeException {
    public:
      /**
       * Constructor
       * @param desc error description
       */
      explicit NoReturnValue(const std::string &desc)
          : RuntimeException(FRED(BOLD("No Return Value ERROR : \n")) + desc) {}
    };

    /**
     * Class describing all possible math related exceptions, like zero-division
     * and invalid operands
     */
    class MathException : public RuntimeException {
    public:
      /**
       * Constructor
       * @param desc error description
       */
      explicit MathException(const std::string &desc)
          : RuntimeException(FYEL(BOLD("Math ERROR : \n")) + desc) {}
    };

    /**
     * Class describing range exception when [] operator is used at invalid
     * position
     */
    class RangeException : public RuntimeException {
    public:
      /**
       * Constructor
       * @param desc error description
       */
      explicit RangeException(const std::string &desc)
          : RuntimeException(FYEL(BOLD("Range ERROR : \n")) + desc) {}
    };
  } // namespace error
} // namespace vecc

#endif // VECC_LANG_EXECEPTION_H
