//
// Created by przemek on 19.03.2020.
//

#ifndef VECC_LANG_FUNCTION_H
#define VECC_LANG_FUNCTION_H

#include <string>
#include <list>
#include <AST/general/variable.h>
#include <AST/general/return.h>
#include <AST/statement/statement_block.h>

namespace vecc {
    class Function {
    public:
        explicit Function(std::string identifier) : identifier_(std::move(identifier)) {}

        void addParameter(const std::string &identifier);

        unsigned size() const { return parameters_.size(); }

        const std::string &getIdentifier() const { return identifier_; }

        Return run(std::list<Variable> parameters = std::list<Variable>());

        StatementBlock &getFunctionBody();
    private:
        const std::string identifier_;      //!< function identifier/name
        std::list<std::string> parameters_; //!< Parameters names
        StatementBlock functionBody_;
    };
}

#endif //VECC_LANG_FUNCTION_H
