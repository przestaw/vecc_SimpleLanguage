//
// Created by przemek on 23.03.2020.
//

#ifndef VECC_LANG_FUNCTION_CALL_H
#define VECC_LANG_FUNCTION_CALL_H

#include <AST/statement/statement.h>
#include <AST/general/function.h>
#include <AST/expression/expression.h>

namespace vecc {
    namespace ast {
        class FunctionCallStatement : public Statement {
        public:
            explicit FunctionCallStatement(Function &function);

            void addArgument(std::unique_ptr<Expression> arg);

            [[nodiscard]] const Function &getFunction() const;

            Return run() override;

            [[nodiscard]] unsigned size() const;

        private:
            Function &function_;
            std::list<std::unique_ptr<Expression>> arguments_;
        };
    }
}

#endif //VECC_LANG_FUNCTION_CALL_H
