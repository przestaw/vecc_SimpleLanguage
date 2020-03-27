//
// Created by przemek on 19.03.2020.
//

#include <AST/general/context.h>
#include <error/exeception.h>

using namespace vecc;

void Context::addVariable(const std::string &identifier, const Variable &variable) {
    variables_.insert({identifier, std::make_shared<Variable>(variable)});
}

std::weak_ptr<Variable> Context::findVariable(const std::string &identifier, const Token &token) {
    if (variables_.count(identifier)) {
        return variables_.at(identifier);
    } else if (parentContext) {
        return parentContext->findVariable(identifier, token);
    } else { // parent context?
        throw UndefinedVar(token);
    }
}

Context::Context(std::vector<std::pair<std::string, std::shared_ptr<Variable>>> variables) : parentContext(nullptr) {
    for (auto &variable : variables) {
        this->variables_.insert(variable);
    }
}

Context::Context(const Context &context) : parentContext(context.parentContext) {
    for (auto &variable : context.variables_) {
        this->variables_.insert(variable);
    }
}

bool Context::existVariable(const std::string &identifier) const {
    return variables_.count(identifier) || (parentContext ? parentContext->existVariable(identifier) : false);
}

Context *Context::getParentContext() {
    return parentContext;
}

std::vector<Variable> Context::saveValues() {
    std::vector<Variable> ret;
    for(auto &it: variables_){
        ret.emplace_back(*it.second);
    }
    return ret;
}

void Context::restoreValues(const std::vector<Variable> &savedValues) {
    if(savedValues.size() == variables_.size()){
        auto val = savedValues.begin();
        for(auto &it: variables_){
            *it.second = *val;
            ++val;
        }
    } else {
        throw Exception("Unknown runtime exception during restoring context\n");
    }
}
