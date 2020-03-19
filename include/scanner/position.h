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
        Position(const Position& other) = default;

        bool operator==(const Position &rhs) const;
        bool operator!=(const Position &rhs) const;

        bool operator<(const Position &rhs) const;
        bool operator>(const Position &rhs) const;
        bool operator<=(const Position &rhs) const;
        bool operator>=(const Position &rhs) const;

        //private ? make class ?
        unsigned int lineNo;
        unsigned int symbolNo;
        std::streampos linePos;
        std::streampos symbolPos;

        inline std::string toString() const{
            return BOLD("line number : ") + std::to_string(lineNo) + ", " BOLD("position : ") + std::to_string(symbolNo) + '\n';
        }

        inline std::ostream &operator<<(std::ostream &os) {
            os << toString();
            return os;
        }
    };
}

#endif //VECC_LANG_POSITION_H
