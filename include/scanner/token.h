//
// Created by przemek on 13.03.2020.
//

#ifndef VECC_LANG_TOKEN_H
#define VECC_LANG_TOKEN_H

#include <unordered_map>
#include "scanner/position.h"

namespace vecc {
    class Token {
    public:
        enum class Type {
            Function,
            If,
            Else,
            While,
            Return,

            Continue,
            Break,

            Var,
            Vec,

            Print,

            ParenthesisOpen,
            ParenthesisClose,
            BracketOpen,
            BracketClose,
            CurlyBracketOpen,
            CurlyBracketClose,

            Comma,
            Semicolon,

            Assignment,

            Negation,
            Or,
            And,
            Equality,
            Inequality,
            Less,
            Greater,
            LessOrEqual,
            GreaterOrEqual,
            Plus,
            Minus,
            Multiply,
            Divide,
            Modulo,

            Identifier,
            NumberString,
            CharacterString,

            NaT,                 //!< Not a Token

            EoF                  //!< End of File
        };

        Token(const Position &position = Position(), const Type &type = Type::NaT);

        // setters
        void setType(const Type &type);
        void setLiteral(const std::string &literal);

        // getters
        const Position &getTokenPos() const;
        Type getType() const;
        const std::string &getLiteral() const;

        // functions connected with Type
        std::string typeName();   //!< description for errors and so

        static Type findKeywordType(const std::string &literal);  //!< for standard literals
        static Type findSymbolType(const unsigned char &literal);//!< for single signs like operators
    private:
        Position tokenPos_;   //!< position of the Token
        Type type_;           //!< type of token
        std::string literal_; //!< to distinguish identifiers

        static const std::unordered_map<Type, std::string> typeDescription;
        static const std::unordered_map<std::string, Type> keywords;
        static const std::unordered_map<char, Type> specialCharacters;
    };
}

#endif //VECC_LANG_TOKEN_H
