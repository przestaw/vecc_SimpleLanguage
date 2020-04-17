#include <AST/general/program.h>

using namespace vecc::ast;

bool Program::existFunction(const std::string &identifier) const {
    return static_cast<bool>(functions.count(identifier));
}

void Program::addFunction(std::unique_ptr<Function> function) {
    functions.insert({function->getIdentifier(), std::move(function)});
}

Return Program::run() {
    auto main = functions.find("main");
    if (main != functions.end()) {
        return main->second->run();
    } else {
        throw error::UndefinedMain();
    }
}

Function &Program::findFunction(const std::string &identifier) {
    return *functions.at(identifier);
}
