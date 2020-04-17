//
// Created by przemek on 13.03.2020.
//

#ifndef VECC_LANG_POSITION_H
#define VECC_LANG_POSITION_H

#include <ostream>
#include <general_defines.h>

namespace vecc {

    struct Position {
        Position();

        Position(unsigned line, unsigned symbol);

        explicit Position(const std::string &streamName);

        Position(unsigned line, unsigned symbol, const std::string &streamName);

        Position(const Position &other) = default;

        bool operator==(const Position &rhs) const;

        bool operator!=(const Position &rhs) const;

        bool operator<(const Position &rhs) const;

        bool operator>(const Position &rhs) const;

        bool operator<=(const Position &rhs) const;

        bool operator>=(const Position &rhs) const;

        inline void incrementLine(){
            ++lineNo;
            symbolNo = 0;
        }

        inline void incrementSymbol(){
            ++symbolNo;
        }

        [[nodiscard]] inline std::string toString() const {
            return BOLD("line number : ") + std::to_string(lineNo) + ", " BOLD("position : ") +
                   std::to_string(symbolNo) + (namedSource ? BOLD("\n\tin file : ") + sourceName : "");
        }

        inline std::ostream &operator<<(std::ostream &os) {
            os << toString();
            return os;
        }
    private:
        //private ? make class ?
        unsigned int lineNo;
        unsigned int symbolNo;

        bool namedSource;
        std::string sourceName;
    };
}

#endif //VECC_LANG_POSITION_H
