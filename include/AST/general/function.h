//
// Created by przemek on 19.03.2020.
//

#ifndef VECC_LANG_FUNCTION_H
#define VECC_LANG_FUNCTION_H

#include <string>
#include <vector>
#include <AST/general/variable.h>
#include <AST/general/return.h>
#include <AST/statement/statement_block.h>

namespace vecc {
    class Function {
    public:
        explicit Function(std::string identifier);

        void addParameter(const std::string &identifier);

        unsigned size() const { return names_.size(); }

        const std::string &getIdentifier() const { return identifier_; }

        Return run(const std::vector<Variable> &parameters = std::vector<Variable>());

        StatementBlock &getFunctionBody();
    private:
        const std::string identifier_;      //!< function identifier/name
        std::vector<std::string> names_; //!< Parameters names
        StatementBlock functionBody_;
    };
}

#endif //VECC_LANG_FUNCTION_H
