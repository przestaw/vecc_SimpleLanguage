//
// Created by przemek on 13.03.2020.
//

#ifndef VECC_LANG_POSITION_H
#define VECC_LANG_POSITION_H

#include <ostream>
#include <general_defines.h>

namespace vecc {

    class Position {

    public:
        Position();
        Position(const Position& other) = default;

        bool operator==(const Position &rhs) const;
        bool operator!=(const Position &rhs) const;

        bool operator<(const Position &rhs) const;
        bool operator>(const Position &rhs) const;
        bool operator<=(const Position &rhs) const;
        bool operator>=(const Position &rhs) const;

        //private or make as a struct
        unsigned int lineNumber;
        unsigned int signNumber;
        std::streampos linePosition;
        std::streampos signPosition;

        friend std::ostream &operator<<(std::ostream &os, const Position &position);
        inline std::string toString() const{
            return "line number : " + std::to_string(this->lineNumber) + ", position : " + std::to_string(this->signNumber);
        }
    };

    inline std::ostream &operator<<(std::ostream &os, const Position &position) {
        os << BOLD("line number : ") << position.lineNumber
           << ", " BOLD("position : ") << position.signNumber;
        return os;
    }
}

#endif //VECC_LANG_POSITION_H
