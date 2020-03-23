//
// Created by przemek on 23.03.2020.
//

#include <AST/statement/assign_stmt.h>
#include <error/exeception.h>

using namespace vecc;

AssignStatement::AssignStatement(Variable &variable, std::unique_ptr<Expression> expression)
        : variable(variable), expression(std::move(expression)), indexedAcess(false), index_() {
}

AssignStatement::AssignStatement(Variable &variable, const unsigned &index, std::unique_ptr<Expression> expression)
        : variable(variable), expression(std::move(expression)), indexedAcess(true), index_(index) {
}

Return AssignStatement::run() {
    Variable value = expression->calculate();
    if (indexedAcess) {
        if (value.size() == 1) {
            variable.setPosition(position_);
            variable.at(index_) = value.at(0);
        } else {
            throw MathException("Try to assign a n-dimensional vector to the int\n"
                            + (position_ != Position() ? "at " + position_.toString() : ""));
        }
    } else {
        variable = value;
    }

    return Return(Return::Type::noting);
}

void AssignStatement::setPosition(const Position &position) {
    this->position_=position;
}
