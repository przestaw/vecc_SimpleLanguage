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

        for (; paramValIt != parameters.end(); ++paramNameIt, ++paramValIt) {
            *(functionBody_.findVariable(*paramNameIt)) = *paramValIt;
        }

        return functionBody_.run();
    }
}

StatementBlock &Function::getFunctionBody() {
    return functionBody_;
}
