#include <AST/general/function.h>
#include <error/exeception.h>

using namespace vecc;

Function::Function(std::string identifier) : identifier_(std::move(identifier)) {}

void Function::addParameter(const std::string &identifier) {
    names_.push_back(identifier);
    functionBody_.addVariable(identifier);
}

Return Function::run(const std::vector<Variable> &parameters) {
    if (parameters.size() != names_.size()) {
        throw Exception("");
    } else {
        // Need to set parameters manually
        auto paramNameIt = names_.begin();
        auto paramValIt = parameters.begin();

        //save context
        std::vector<Variable> storedContext = functionBody_.getContext().saveValues();

        for (; paramValIt != parameters.end(); ++paramNameIt, ++paramValIt) {
            *(functionBody_.findVariable(*paramNameIt)) = *paramValIt;
        }
        Return ret = functionBody_.run();

        //restore context
        functionBody_.getContext().restoreValues(storedContext);

        return ret;
    }
}

StatementBlock &Function::getFunctionBody() {
    return functionBody_;
}
