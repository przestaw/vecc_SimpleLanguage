//
// Created by przemek on 17.03.2020.
//

#include <scanner/token.h>

using namespace vecc;

const std::unordered_map<Token::Type, std::string> Token::typeDescription = {
        {Token::Type::Function,          "Function"},
        {Token::Type::If,                "If"},
        {Token::Type::While,             "While"},
        {Token::Type::Else,              "Else"},
        {Token::Type::Return,            "Return"},
        {Token::Type::Break,             "Break"},

        {Token::Type::Var,               "Var"},
        {Token::Type::Vec,               "Vec"},
        {Token::Type::Print,             "Print"},

        {Token::Type::ParenthesisOpen,   "Parenthesis Open"},
        {Token::Type::ParenthesisClose,  "Parenthesis Close"},
        {Token::Type::BracketOpen,       "Bracket Open"},
        {Token::Type::BracketClose,      "Bracket Close"},
        {Token::Type::CurlyBracketOpen,  "Curly Bracket Open"},
        {Token::Type::CurlyBracketClose, "Curly Bracket Close"},

        {Token::Type::Comma,             "Comma"},
        {Token::Type::Semicolon,         "Semicolon"},

        {Token::Type::Assignment,        "Assignment"},

        {Token::Type::Negation,          "Negation"},
        {Token::Type::Or,                "Or"},
        {Token::Type::And,               "And"},
        {Token::Type::Equality,          "Equality"},
        {Token::Type::Inequality,        "Inequality"},
        {Token::Type::Less,              "Less"},
        {Token::Type::Greater,           "Greater"},
        {Token::Type::LessOrEqual,       "Less Or Equal"},
        {Token::Type::GreaterOrEqual,    "Greater Or Equal"},
        {Token::Type::Plus,              "Plus"},
        {Token::Type::Minus,             "Minus"},
        {Token::Type::Multiply,          "Multiply"},
        {Token::Type::Divide,            "Divide"},
        {Token::Type::Modulo,            "Modulo"},

        {Token::Type::Identifier,        "Identifier"},
        {Token::Type::NumberString,      "Number String"},
        {Token::Type::CharacterString,   "Character String"},

        {Token::Type::NaT,               "Invalid"},
        {Token::Type::EoF,               "End Of File"}
};

const std::unordered_map<std::string, Token::Type> Token::keywords = {
        {"fun",    Token::Type::Function},
        {"if",     Token::Type::If},
        {"while",  Token::Type::While},
        {"else",   Token::Type::Else},
        {"return", Token::Type::Return},
        {"and",    Token::Type::And},
        {"or",     Token::Type::Or},
        {"break",  Token::Type::Break},
        {"var",    Token::Type::Var},
        {"vec",    Token::Type::Vec},
        {"print",  Token::Type::Print}
};

const std::unordered_map<char, Token::Type> Token::specialCharacters = {
        {'(', Token::Type::ParenthesisOpen},
        {')', Token::Type::ParenthesisClose},
        {'[', Token::Type::BracketOpen},
        {']', Token::Type::BracketClose},
        {'{', Token::Type::CurlyBracketOpen},
        {'}', Token::Type::CurlyBracketClose},

        {',', Token::Type::Comma},
        {';', Token::Type::Semicolon},

        {'=', Token::Type::Assignment},
        {'>', Token::Type::Greater},
        {'<', Token::Type::Less},

        {'!', Token::Type::Negation},
        {'+', Token::Type::Plus},
        {'-', Token::Type::Minus},
        {'*', Token::Type::Multiply},
        {'/', Token::Type::Divide},
        {'%', Token::Type::Modulo}
};

const std::unordered_map<char, std::function<Token::Type(const char &)>> Token::twoCharOperators = {
        {'=', [](const char &got) { return checkSymbol(got, '=', Token::Type::Equality); }},
        {'<', [](const char &got) { return checkSymbol(got, '=', Token::Type::LessOrEqual); }},
        {'>', [](const char &got) { return checkSymbol(got, '=', Token::Type::GreaterOrEqual); }},
        {'!', [](const char &got) { return checkSymbol(got, '=', Token::Type::Inequality); }}
};

Token::Type Token::findKeywordType(const std::string &literal) {
    auto type = keywords.find(literal);
    return type == keywords.end() ? Token::Type::NaT : type->second;
}

Token::Type Token::findSymbolType(const char &literal) {
    auto type = specialCharacters.find(literal);
    return type == specialCharacters.end() ? Token::Type::NaT : type->second;
}

Token::Type Token::checkSecondSecond(const char &first, const char &second) {
    if (twoCharOperators.count(first)) {
        return twoCharOperators.at(first)(second);
    } else {
        return Token::Type::NaT;
    }
}

std::string Token::typeName() const {
    return typeDescription.at(this->type_);
}

Token::Token(const Position &position, const Token::Type &type) : tokenPos_(position), type_(type) {}

void Token::setType(const Token::Type &type) {
    type_ = type;
}

void Token::setLiteral(const std::string &literal) {
    literal_ = literal;
}

const Position &Token::getTokenPos() const {
    return tokenPos_;
}

Token::Type Token::getType() const {
    return type_;
}

const std::string &Token::getLiteral() const {
    return literal_;
}

std::string Token::toString() const {
    return "Token " + typeName() + ", \"" + literal_ + "\", \n at " + tokenPos_.toString();
}

std::string Token::getTypeName(const Token::Type &type) {
    return typeDescription.at(type);
}
