//
// Created by przemek on 24.03.2020.
//

#include <AST/statement/statement_block.h>

using namespace vecc;

StatementBlock::StatementBlock(Context *parentContext)  : context_(parentContext) {}

void StatementBlock::addInstruction(std::unique_ptr<Statement> statement) {
    this->statements_.push_back(std::move(statement));
}

void StatementBlock::addVariable(const std::string &identifier) {
    this->context_.addVariable(identifier, Variable());
}

Return StatementBlock::run() {
    Return ret;

    //save context

    for(auto &it : statements_){
        ret = it->run();
        if(ret.type_ == Return::Type::value){
            break;
        }
    }

    //restore context

    return ret;
}

std::weak_ptr<Variable> StatementBlock::findVariable(const std::string &identifier) {
    return context_.findVariable(identifier, Token()); //TODO
}
