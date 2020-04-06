//
// Created by przemek on 19.03.2020.
//

#ifndef VECC_LANG_STATEMENT_BLOCK_H
#define VECC_LANG_STATEMENT_BLOCK_H

#include <list>
#include <memory>
#include <AST/statement/statement.h>
#include <AST/general/context.h>

namespace vecc {
    namespace ast {
        class StatementBlock : public Statement {
        public:
            explicit StatementBlock(Context *parentContext = nullptr);

            void addInstruction(std::unique_ptr<Statement> statement);

            void addVariable(const std::string &identifier);

            std::shared_ptr<Variable> findVariable(const std::string &identifier);

            Context &getContext();

            Return run() override;

        private:
            std::list<std::unique_ptr<Statement>> statements_;
            Context context_;
        };
    }
}

#endif //VECC_LANG_STATEMENT_BLOCK_H
