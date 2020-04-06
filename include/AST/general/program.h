//
// Created by przemek on 19.03.2020.
//

#ifndef VECC_LANG_PROGRAM_H
#define VECC_LANG_PROGRAM_H

#include <string>
#include <unordered_map>
#include <memory>
#include <AST/general/function.h>
#include <error/exeception.h>

namespace vecc {
    namespace ast {
        class Program {
        public:
            Program() = default;

            Function &findFunction(const std::string &identifier) {
                return *functions.at(identifier);
            }

            bool existFunction(const std::string &identifier) const {
                return static_cast<bool>(functions.count(identifier));
            }

            void addFunction(std::unique_ptr<Function> function) {
                functions.insert({function->getIdentifier(), std::move(function)});
            }

            Return run() {
                auto main = functions.find("main");
                if (main != functions.end()) {
                    return main->second->run();
                } else {
                    throw error::UndefinedMain();
                }
            }

        private:
            std::unordered_map<std::string, std::unique_ptr<Function>> functions;
        };
    }
}

#endif //VECC_LANG_PROGRAM_H
