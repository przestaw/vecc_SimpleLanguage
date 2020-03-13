//
// Created by przemek on 13.03.2020.
//

#ifndef VECC_LANG_TOKEN_H
#define VECC_LANG_TOKEN_H

#include "scanner/position.h"

namespace vecc {
    class Token{
    public:
        enum class Type{
            Function,
            If,
            Else,
            While,
            Return,
            //TODO : Rest of types ...

            NaT         //!< Not a Token
        };

        Token(const Position &position = Position(), const Type &type = Type::NaT);

        // setters
        void setType(const Type& type);
        void setLiteral(const std::string& literal);
        // getters
        const Position& getTokenPos() const;
        Type getTokenType() const;
        const std::string& getLiteral() const;

        // functions connected with Type
        static Type findType(std::string literal);  //!< for standard literals
        static Type findType(unsigned char literal);//!< for single signs like operators
        static std::string typeName(std::string);   //!< description for errors and so
    private:
        Position tokenPos_;   //!< position of the Token
        Type type_;           //!< type of token
        std::string literal_; //!< to distinguish identifiers

        // TODO : map of types literals and map of descriptions
    };
}

#endif //VECC_LANG_TOKEN_H
