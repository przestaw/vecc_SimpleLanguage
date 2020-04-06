//
// Created by przemek on 19.03.2020.
//

#ifndef VECC_LANG_CONTEXT_H
#define VECC_LANG_CONTEXT_H

#include <iostream>
#include <memory>
#include <AST/general/variable.h>
#include <vector>

namespace vecc {
    namespace ast {
        class Context {
        public:
            explicit Context(Context *parent = nullptr) : parentContext_(parent) {}

            explicit Context(std::vector<std::pair<std::string, std::shared_ptr<Variable>>> variables);

            Context(const Context &context);

            void addVariable(const std::string &identifier, const Variable &variable);

            bool existVariable(const std::string &identifier) const;

            std::shared_ptr<Variable> findVariable(const std::string &identifier, const Token &token);

            Context *getParentContext();

            void setParentContext(Context *parentContext);

            [[nodiscard]] std::vector<Variable> saveValues();

            void restoreValues(const std::vector<Variable> &savedValues);

        private:
            Context *parentContext_; //!< used incases like if/while branch/just some code in curly brackets. In other cases nullptr
            std::unordered_map<std::string, std::shared_ptr<Variable>> variables_;
        };
    }
}

#endif //VECC_LANG_CONTEXT_H
