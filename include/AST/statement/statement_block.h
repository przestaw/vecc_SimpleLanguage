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
    class StatementBlock : public Statement {
    public:

        //TODO

        void addInstruction(std::unique_ptr<Statement> statement) {
            this->statements_.push_back(std::move(statement));
        }

        Return run() override {
            Return ret;

            for(auto &it : statements_){
                ret = it->run();
                if(ret.type_ == Return::Type::value){
                    break;
                }
            }

            return ret;
        }
    private:
        std::list<std::unique_ptr<Statement>> statements_;
        Context context_;
    };
}

#endif //VECC_LANG_STATEMENT_BLOCK_H
