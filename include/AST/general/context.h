//
// Created by przemek on 19.03.2020.
//

#ifndef VECC_LANG_CONTEXT_H
#define VECC_LANG_CONTEXT_H

#include <iostream>
#include <memory>
#include <AST/general/variable.h>
#include <vector>

namespace vecc::ast {
    /**
     * Utility class storing Context of code execution with its variables and information about parent Context
     */
    class Context {
    public:
        /**
         * Constructor
         * @param parent context
         */
        explicit Context(Context *parent = nullptr) : parentContext_(parent) {}

        /**
         * Copy constructor
         * @param context
         */
        Context(const Context &context);

         /**
          * Adds Variable to Context
          * @param identifier Variable to be added
          * @param variable value
          */
        void addVariable(const std::string &identifier, const Variable &variable);

        /**
         * Checks for Variable existence
         * @param identifier Variable identifier
         * @return true if Variable exists in Context
         */
        bool existVariable(const std::string &identifier) const;

        /**
         * Finds Variable
         * @param identifier Variable identifier
         * @param token connected Token
         * @return Variable shared_ptr
         */
        std::shared_ptr<Variable> findVariable(const std::string &identifier, const Token &token);

        /**
         * Returns pointer to parent Context
         * @return pointer to parent Context
         */
        Context *getParentContext();

        /**
         * Sets parent context
         * @param parentContext parent Context
         */
        void setParentContext(Context *parentContext);

        /**
         * Save Context state
         * @return values of all Context Variables
         */
        [[nodiscard]] std::vector<Variable> saveValues();

        /**
         * Restores Context state
         * @param savedValues values of all Context Variables
         */
        void restoreValues(const std::vector<Variable> &savedValues);

    private:
        Context *parentContext_; //!< used incases like if/while branch/just some code in curly brackets. In other cases nullptr
        std::unordered_map<std::string, std::shared_ptr<Variable>> variables_;
    };
}

#endif //VECC_LANG_CONTEXT_H
