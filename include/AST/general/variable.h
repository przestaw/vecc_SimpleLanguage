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

        //TODO
    private:
        std::vector<int> values_; //!< can store normal value or 2,3(with possibility for more) dim vec
        Token connectedToken;     // FIXME : maybe just vecc::Position
    };
}

#endif //VECC_LANG_VARIABLE_H
