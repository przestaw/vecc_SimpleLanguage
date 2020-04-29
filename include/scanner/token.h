//
// Created by przemek on 13.03.2020.
//

#ifndef VECC_LANG_TOKEN_H
#define VECC_LANG_TOKEN_H

#include "scanner/position.h"
#include <functional>
#include <unordered_map>

namespace vecc {
  /**
   * Class Token representing single literal token in source file
   */
  class Token {
  public:
    /**
     * Enum Type representing type of the Token
     */
    enum class Type {
      Function, //!< Function keyword : fun
      If,       //!< If keyword : if
      Else,     //!< Else keyword : else
      While,    //!< While keyword : while
      Return,   //!< Return keyword : return

      Var,   //!< Variable keyword : var
      Vec,   //!< Vector keyword : vec
      Print, //!< Print keyword : print

      ParenthesisOpen,   //!< Parenthesis Open : (
      ParenthesisClose,  //!< Parenthesis Close : )
      BracketOpen,       //!< Bracket Open : [
      BracketClose,      //!< Bracket Close : ]
      CurlyBracketOpen,  //!< Curly Bracket Open : {
      CurlyBracketClose, //!< Curly Bracket Open : }

      Comma,     //!< Comma : ,
      Semicolon, //!< Semicolon : ;

      Assignment, //!< Assignment operator : =

      Negation,       //!< Logical negation : !
      Or,             //!< Logical Or operator
      And,            //!< Logical And operator
      Equality,       //!< Relation operator : Equality ==
      Inequality,     //!< Relation operator : Inequality !=
      Less,           //!< Relation operator : Less <
      Greater,        //!< Relation operator : Greater >
      LessOrEqual,    //!< Relation operator : Less or Equal <=
      GreaterOrEqual, //!< Relation operator : Greater or Equal >=
      Plus,           //!< Mathematical addition operation : +
      Minus,          //!< Mathematical subtraction operation : -  or negation
      Multiply,       //!< Mathematical multiply operation : *
      Divide,         //!< Mathematical division operation : /
      Modulo,         //!< Mathematical modulo operation : %

      Identifier,      //!< Identifier of function or variable
      NumberString,    //!< Number value
      CharacterString, //!< Printable character string

      NaT, //!< Not a Token

      EoF //!< End of File
    };

    /**
     * Token constructor
     * @param position Position of the Token
     * @param type Token Type
     */
    explicit Token(const Position &position = Position(),
                   const Type &type         = Type::NaT);

    // setters
    /**
     * Sets Token Type
     * @param type Token Type
     */
    void setType(const Type &type);

    /**
     * Sets Token literal
     * @param literal Token literal
     */
    void setLiteral(const std::string &literal);

    // getters
    /**
     * Returns Token Position
     * @return Token Position
     */
    [[nodiscard]] const Position &getTokenPos() const;

    /**
     * Returns Token Type
     * @return Token Type
     */
    [[nodiscard]] Type getType() const;

    /**
     * Returns Token literal
     * @return Token literal
     */
    [[nodiscard]] const std::string &getLiteral() const;

    /**
     * Generates and returns information about Token
     * @return Token description, position and value
     */
    [[nodiscard]] std::string toString() const;

    /**
     * Prints Token using toString on given stream
     * @param os given stream
     * @return modified os
     */
    inline std::ostream &operator<<(std::ostream &os) const {
      os << toString();
      return os;
    }

    // functions connected with Type
    /**
     * Returns Token Type name
     * @return Token Type name
     */
    [[nodiscard]] std::string typeName() const;

    /**
     * Static method
     * Returns keyword Type for given literal
     * @param literal literal
     * @return keyword Type or NaT
     */
    static Type findKeywordType(const std::string &literal);

    /**
     * Static method
     * Returns character Type for given symbol
     * @param symbol symbol
     * @return symbol Type or NaT
     */
    static Type findSymbolType(const char &symbol);

    /**
     * Static method
     * Returns Type of two symbol sequence
     * @param first first symbol
     * @param second second symbol
     * @return sequence Type or NaT
     */
    static Type checkSecondSecond(const char &first, const char &second);

    /**
     * Static method
     * Returns Type name
     * @param type Token Type
     * @return type name
     */
    static std::string getTypeName(const Type &type);

  protected:
    Position tokenPos_;   //!< position of the Token
    Type type_;           //!< type of token
    std::string literal_; //!< to distinguish identifiers

  private:
    static const std::unordered_map<Type, std::string> typeDescription;
    static const std::unordered_map<std::string, Type> keywords;
    static const std::unordered_map<char, Type> specialCharacters;
    static const std::unordered_map<char, std::function<Type(const char &)>>
        twoCharOperators;

    static inline Token::Type checkSymbol(const char &got, const char &expected,
                                          const Token::Type &occured) {
      if (got == expected) {
        return occured;
      } else {
        return Type::NaT;
      }
    }
  };
} // namespace vecc

#endif // VECC_LANG_TOKEN_H
