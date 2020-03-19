//
// Created by przemek on 19.03.2020.
//

#ifndef VECC_LANG_RETURN_H
#define VECC_LANG_RETURN_H

#include "variable.h"

namespace vecc {

    struct Return {
        enum class Type{
            noting,
            value
        };

        explicit Return(const Type &type = Type::noting) : type(type) {}

        explicit Return(const Type &type, const Variable& variable) : type(type), variable(variable) {}

        Type type;
        Variable variable;
    };
}

#endif //VECC_LANG_RETURN_H
