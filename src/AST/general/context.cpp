//
// Created by przemek on 19.03.2020.
//

#include <AST/general/context.h>
#include <error/exeception.h>

using namespace vecc;

void Context::addVariable(const std::string &identifier, Variable &&variable) {
    variables_.insert({identifier, std::move(variable)});
}

Variable &Context::findVariable(const std::string &identifier, const Token& token) {
    if (variables_.count(identifier)) {
        return variables_.at(identifier);
    } else { // parent context?
        throw UndefinedVar("Variable " + identifier + " not found\n"
                        " at line: " + token.getTokenPos().toString());
    }
}

Context::Context(std::vector<std::pair<std::string, Variable>> variables) {
    for (auto &variable : variables) {
        this->variables_.insert(variable);
    }
}

Context::Context(const Context &context) {
    for (auto &variable : context.variables_) {
        this->variables_.insert(variable);
    }
}

bool Context::existVariable(const std::string &identifier) const {
    return variables_.count(identifier); // parent context?
}
