//
// Created by przemek on 19.03.2020.
//

#ifndef VECC_LANG_RETURN_H
#define VECC_LANG_RETURN_H

#include <utility>
#include "variable.h"

namespace vecc::ast {
    /**
     * Return struct - contains value and type information
     */
    struct Return {
        enum class Type {
            Noting, //!< no value is returned
            Value   //!< value is returned
        };

        /**
         * Constructor
         * @param type return type
         */
        explicit Return(const Type &type = Type::Noting) : type_(type) {}

        /**
         * Constructor
         * @param type return type
         * @param variable return value
         */
        explicit Return(const Type &type, Variable variable) : type_(type), variable_(std::move(variable)) {}

        Type type_;
        Variable variable_;
    };
}

#endif //VECC_LANG_RETURN_H
