//
// Created by przemek on 19.03.2020.
//

#include <AST/general/context.h>
#include <error/exeception.h>

using namespace vecc;

void Context::addVariable(const std::string &identifier, const Variable &variable) {
    variables_.insert({identifier, std::make_shared<Variable>(variable)});
}

std::weak_ptr<Variable> Context::findVariable(const std::string &identifier, const Token& token) {
    if (variables_.count(identifier)) {
        return variables_.at(identifier);
    } else { // parent context?
        throw UndefinedVar(token);
    }
}

Context::Context(std::vector<std::pair<std::string, std::shared_ptr<Variable>>> variables) : parentContext(nullptr){
    for (auto &variable : variables) {
        this->variables_.insert(variable);
    }
}

Context::Context(const Context &context) : parentContext(context.parentContext){
    for (auto &variable : context.variables_) {
        this->variables_.insert(variable);
    }
}

bool Context::existVariable(const std::string &identifier) const {
    return variables_.count(identifier); // parent context?
}

Context *Context::getParentContext() {
    return parentContext;
}

std::vector<Variable> Context::saveValues() {
    //TODO
    return std::vector<Variable>();
}

void Context::restoreValues(const std::vector<Variable> &savedValues) {
    //TODO
}
