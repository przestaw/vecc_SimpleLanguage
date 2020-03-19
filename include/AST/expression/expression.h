//
// Created by przemek on 19.03.2020.
//

#ifndef VECC_LANG_EXPRESSION_H
#define VECC_LANG_EXPRESSION_H

#include <AST/general/variable.h>

namespace vecc {
    class Expression {
    public:
        virtual ~Expression() = default;

        virtual Variable calculate() const = 0;
    }
}

#endif //VECC_LANG_EXPRESSION_H
