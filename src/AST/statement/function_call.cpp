//
// Created by przemek on 24.03.2020.
//

#include <AST/statement/function_call.h>

using namespace vecc;

FunctionCallStatement::FunctionCallStatement(Function &function) : function_(function) {}

void FunctionCallStatement::addArgument(std::unique_ptr<Expression> arg) {
    arguments_.push_back(std::move(arg));
}

const Function &FunctionCallStatement::getFunction() const {
    return function_;
}

Return FunctionCallStatement::run() {
    std::vector<Variable> argVal;
    for (auto &&it : arguments_) {
        argVal.push_back(it->calculate());
    }
    //save context
    std::vector<Variable> storedContext = function_.getFunctionBody().getContext().saveValues();

    Return ret = function_.run(argVal);

    //restore context
    function_.getFunctionBody().getContext().restoreValues(storedContext);

    return ret;
}

unsigned FunctionCallStatement::size() const {
    return arguments_.size();
}

