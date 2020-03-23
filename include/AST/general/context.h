//
// Created by przemek on 19.03.2020.
//

#ifndef VECC_LANG_CONTEXT_H
#define VECC_LANG_CONTEXT_H

#include <iostream>
#include <AST/general/variable.h>
#include <vector>

namespace vecc {
    class Context {
    public:
        Context(std::vector<std::pair<std::string, Variable>> variables);
        Context(const Context& context);

        void addVariable(const std::string &identifier, Variable &&variable);
        bool existVariable(const std::string &identifier) const;
        Variable &findVariable(const std::string &identifier, const Token& token);

    private:
        Context *parentContext; //!< used incases like if/while branch/just some code in curly brackets. In other cases nullptr
        std::unordered_map<std::string, Variable> variables_;
    };

}

#endif //VECC_LANG_CONTEXT_H
