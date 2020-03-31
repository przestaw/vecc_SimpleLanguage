//
// Created by przemek on 24.03.2020.
//

#include <AST/statement/statement_block.h>

using namespace vecc;

StatementBlock::StatementBlock(Context *parentContext) : context_(parentContext) {}

void StatementBlock::addInstruction(std::unique_ptr<Statement> statement) {
    this->statements_.push_back(std::move(statement));
}

void StatementBlock::addVariable(const std::string &identifier) {
    this->context_.addVariable(identifier, Variable());
}

std::weak_ptr<Variable> StatementBlock::findVariable(const std::string &identifier) {
    return context_.findVariable(identifier, Token()); //TODO ??
}

Return StatementBlock::run() {
    Return ret;

    for (auto &it : statements_) {
        ret = it->run();
        if (ret.type_ != Return::Type::Noting) {
            break;
        }
    }

    return ret;
}

Context &StatementBlock::getContext() {
    return context_;
}
