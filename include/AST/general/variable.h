//
// Created by przemek on 19.03.2020.
//

#ifndef VECC_LANG_VARIABLE_H
#define VECC_LANG_VARIABLE_H

#include <vector>
#include <scanner/token.h>

namespace vecc {
    namespace ast {
        class Variable {
        public:
            Variable() = default;

            explicit Variable(std::vector<int> values);

            Variable(const Variable &) = default;

            Variable(Variable &&) = default;

            Variable &operator=(const Variable &rhs) = default;

            int &operator[](int idx);

            const int &operator[](int idx) const;

            std::vector<int> &operator*();

            [[nodiscard]] int &at(unsigned idx);

            [[nodiscard]] const int &at(unsigned idx) const;

            [[nodiscard]] unsigned size() const;

            Variable operator==(const Variable &rhs) const;

            Variable operator!=(const Variable &rhs) const;

            Variable operator<(const Variable &rhs) const;

            Variable operator>(const Variable &rhs) const;

            Variable operator<=(const Variable &rhs) const;

            Variable operator>=(const Variable &rhs) const;

            Variable operator+() const;

            Variable operator-() const;

            Variable operator+(const Variable &rhs) const;

            Variable operator-(const Variable &rhs) const;

            Variable operator*(const Variable &rhs) const;

            Variable operator/(const Variable &rhs) const;

            Variable operator%(const Variable &rhs) const;

            Variable operator!() const;

            Variable operator&&(const Variable &rhs) const;

            Variable operator||(const Variable &rhs) const;

            explicit operator bool() const;

            void setPosition(const Position &position);

            [[nodiscard]] std::string toString() const;

            inline std::ostream &operator<<(std::ostream &os) const {
                os << toString();
                return os;
            }

        private:
            std::vector<int> values_; //!< can store normal value or 2,3(with possibility for more) dim vec
            Position currentPosition;

            static const Variable retTrue;
            static const Variable retFalse;
        };
    }
}

#endif //VECC_LANG_VARIABLE_H
