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

        friend std::ostream &operator<<(std::ostream &os, const Position &position);
        inline std::string toString() const{
            return "line number : " + std::to_string(this->lineNo) + ", position : " + std::to_string(this->symbolNo);
        }
    };

    inline std::ostream &operator<<(std::ostream &os, const Position &position) {
        os << BOLD("line number : ") << position.lineNo
           << ", " BOLD("position : ") << position.symbolNo;
        return os;
    }
}

#endif //VECC_LANG_POSITION_H
