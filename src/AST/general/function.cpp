#include <AST/general/function.h>
#include <error/exeception.h>

using namespace vecc;
using namespace vecc::ast;

Function::Function(std::string identifier)
    : identifier_(std::move(identifier)) {}

void Function::addParameter(const std::string &identifier) {
  names_.push_back(identifier);
  functionBody_.addVariable(identifier);
}

Return Function::run(const std::vector<Variable> &parameters) {
  if (parameters.size() != names_.size()) {
    throw error::Exception("");
  } else {
    // Need to set parameters manually
    auto paramNameIt = names_.begin();
    auto paramValIt  = parameters.begin();

    // save context
    std::vector<Variable> storedContext =
        functionBody_.getContext().saveValues();

    for (; paramValIt != parameters.end(); ++paramNameIt, ++paramValIt) {
      functionBody_.findVariable(*paramNameIt) = *paramValIt;
    }
    Return ret = functionBody_.run();

    // restore context
    functionBody_.getContext().restoreValues(storedContext);

    return ret;
  }
}

StatementBlock &Function::getFunctionBody() {
  return functionBody_;
}

const std::string &Function::getIdentifier() const {
  return identifier_;
}

unsigned Function::size() const {
  return names_.size();
}

std::string Function::toString() const {
  std::string ret = "fun " + identifier_ + "(";
  if (!names_.empty()) {
    ret += *names_.begin();
    for (auto it = ++names_.begin(); it != names_.end(); ++it) {
      ret += ", " + *it;
    }
  }
  ret += ")" + functionBody_.toString();
  return ret;
}
