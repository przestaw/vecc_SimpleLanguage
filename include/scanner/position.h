//
// Created by przemek on 13.03.2020.
//

#ifndef VECC_LANG_POSITION_H
#define VECC_LANG_POSITION_H

#include <ostream>
#include <general_defines.h>

namespace vecc {

    /**
     * Class Position representing position in file(source)
     */
    class Position {
    public:
        /**
         * Default constructor - position (1,0) in unknown file
         */
        Position();
        /**
         * Constructor - position (line,symbol) in unknown file
         * @param line line position
         * @param symbol position in line
         */
        Position(unsigned line, unsigned symbol);

        /**
         * Constructor position (1,0) in source file
         * @param source source file name
         */
        explicit Position(std::string source);

        /**
         * Constructor position (line,symbol) in source file
         * @param line line position
         * @param symbol position in line
         * @param source source file name
         */
        Position(unsigned line, unsigned symbol, std::string source);

        /**
         * Copy constructor
         * @param other Position to be copied
         */
        Position(const Position &other) = default;

        /**
         * Operator ==
         * @param rhs right side of comparison
         * @return true if equal
         */
        bool operator==(const Position &rhs) const;

        /**
         * Operator !=
         * @param rhs right side of comparison
         * @return true if not equal
         */
        bool operator!=(const Position &rhs) const;

        /**
         * Operator <
         * @param rhs right side of comparison
         * @return true if less
         */
        bool operator<(const Position &rhs) const;

        /**
         * Operator >
         * @param rhs right side of comparison
         * @return true if greater
         */
        bool operator>(const Position &rhs) const;

        /**
         * Operator <=
         * @param rhs right side of comparison
         * @return true if less or equal
         */
        bool operator<=(const Position &rhs) const;

        /**
         * Operator >=
         * @param rhs right side of comparison
         * @return true if greater or equal
         */
        bool operator>=(const Position &rhs) const;

        /**
         * Helper function incrementing line Position in file
         */
        inline void incrementLine(){
            ++lineNo;
            symbolNo = 0;
        }

        /**
         * Helper function incrementing Position in line
         */
        inline void incrementSymbol(){
            ++symbolNo;
        }

        /**
         * Generates Position as string containing information
         * @return Position as string
         */
        [[nodiscard]] inline std::string toString() const {
            return BOLD("line number : ") + std::to_string(lineNo) + ", " BOLD("position : ") +
                   std::to_string(symbolNo) + (namedSource ? BOLD("\n\tin file : ") + sourceName : "");
        }

        /**
         * Prints Position using toString on given stream
         * @param os given stream
         * @return modified os
         */
        inline std::ostream &operator<<(std::ostream &os) const {
            os << toString();
            return os;
        }

    private:
        unsigned int lineNo;    //!< Position in file lines
        unsigned int symbolNo;  //!< Position in line

        bool namedSource;       //!< Determines if source is anonymous or named
        std::string sourceName; //!< Name of the source if present
    };
}

#endif //VECC_LANG_POSITION_H
