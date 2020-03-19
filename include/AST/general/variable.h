//
// Created by przemek on 19.03.2020.
//

#ifndef VECC_LANG_VARIABLE_H
#define VECC_LANG_VARIABLE_H

#include <vector>
#include <scanner/token.h>

namespace vecc {
    class Variable {
    public:
        Variable() = default;
        explicit Variable(std::vector<int> values);

        Variable(const Variable &) = default;
        Variable &operator=(const Variable &rhs) = default;

        int& operator[](int idx);
        const int& operator[](int idx) const;
        std::vector<int>& operator*();

        int& at(unsigned idx);
        const int& at(unsigned idx) const;
        unsigned size() const;

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

        std::string toString() const;
    private:
        std::vector<int> values_; //!< can store normal value or 2,3(with possibility for more) dim vec
        Position currentPosition;

        static const Variable retTrue;
        static const Variable retFalse;
    };
}

#endif //VECC_LANG_VARIABLE_H
