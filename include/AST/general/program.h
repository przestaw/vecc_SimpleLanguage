//
// Created by przemek on 19.03.2020.
//

#ifndef VECC_LANG_PROGRAM_H
#define VECC_LANG_PROGRAM_H

#include <string>
#include <unordered_map>
#include <memory>
#include <AST/general/function.h>
#include <error/exeception.h>

namespace vecc::ast {
    /**
     * Class describing Program in form of AST
     */
    class Program {
    public:
        /**
         * Constructor
         */
        Program() = default;

        /**
         * Finds function
         * @param identifier function identifier
         * @return Function definition reference
         */
        Function &findFunction(const std::string &identifier);

        /**
         * Checks for function existence
         * @param identifier function identifier
         * @return true if function exists in Program
         */
        bool existFunction(const std::string &identifier) const;

        /**
         * Adds function to program
         * @param function function to be added
         */
        void addFunction(std::unique_ptr<Function> function);

        /**
         * Runs Program
         * @return return value
         */
        Return run();

    private:
        std::unordered_map<std::string, std::unique_ptr<Function>> functions;
    };
}

#endif //VECC_LANG_PROGRAM_H
