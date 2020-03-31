//
// Created by przemek on 13.03.2020.
//

#ifndef VECC_LANG_TOKEN_H
#define VECC_LANG_TOKEN_H

#include <unordered_map>
#include <functional>
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

        explicit Token(const Position &position = Position(), const Type &type = Type::NaT);

        // setters
        void setType(const Type &type);

        void setLiteral(const std::string &literal);

        // getters
        [[nodiscard]] const Position &getTokenPos() const;

        [[nodiscard]] Type getType() const;

        [[nodiscard]] const std::string &getLiteral() const;

        [[nodiscard]] std::string toString() const;

        // functions connected with Type
        [[nodiscard]] std::string typeName() const;   //!< description for errors and so

        static Type findKeywordType(const std::string &literal);        //!< for standard literals
        static Type findSymbolType(const char &literal);                //!< for single signs like operators
        static Type checkSecondSecond(const char &first,
                                      const char &second); //!< for two-symbol operators like ==, returns type::NaT if it's not a two-symbol operator
        static std::string getTypeName(const Type &type);

    private:
        Position tokenPos_;   //!< position of the Token
        Type type_;           //!< type of token
        std::string literal_; //!< to distinguish identifiers

        static const std::unordered_map<Type, std::string> typeDescription;
        static const std::unordered_map<std::string, Type> keywords;
        static const std::unordered_map<char, Type> specialCharacters;
        static const std::unordered_map<char, std::function<Type(const char &)>> twoCharOperators;

        static inline Token::Type checkSymbol(const char &got, const char &expected, const Token::Type &occured) {
            if (got == expected) {
                return occured;
            } else {
                return Type::NaT;
            }
        }
    };
}

#endif //VECC_LANG_TOKEN_H
