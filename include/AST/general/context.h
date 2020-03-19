//
// Created by przemek on 19.03.2020.
//

#ifndef VECC_LANG_CONTEXT_H
#define VECC_LANG_CONTEXT_H

#include <iostream>
#include <AST/general/variable.h>
#include <vector>

namespace vecc {
    class Context {
    public:
        //explicit Context(std::ostream &output = std::cout);
        Context(std::vector<std::pair<std::string, Variable>> variables); //, std::ostream &output = std::cout);
        Context(const Context& context);

        void addVariable(const std::string &identifier, Variable &&variable);
        bool existVariable(const std::string &identifier) const;
        Variable &findVariable(const std::string &identifier, const Token& token);

        //inline std::ostream &getOutput() { return output_; }
    private:
        std::unordered_map<std::string, Variable> variables_;
        //std::ostream output_;
    };

}

#endif //VECC_LANG_CONTEXT_H
