//
// Created by przemek on 19.03.2020.
//

#ifndef VECC_LANG_STATEMENT_H
#define VECC_LANG_STATEMENT_H

#include <AST/general/return.h>

namespace vecc::ast {
    /**
     * Base virtual class for all statements
     */
    class Statement {
    public:
        /**
         * Virtual destructor
         */
        virtual ~Statement() = default;

        /**
         * Runs statement
         * @return return value
         */
        virtual Return run() = 0;
    };
}

#endif //VECC_LANG_STATEMENT_H
