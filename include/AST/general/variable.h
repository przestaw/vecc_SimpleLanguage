//
// Created by przemek on 19.03.2020.
//

#ifndef VECC_LANG_VARIABLE_H
#define VECC_LANG_VARIABLE_H

#include <scanner/token.h>
#include <vector>

namespace vecc::ast {
  /**
   * Variable class used to store values and perform math operations
   */
  class Variable {
  public:
    /**
     * Constructor
     */
    Variable() = default;

    /**
     * Constructor
     * @param values values of the variable
     */
    explicit Variable(std::vector<int> values);

    /**
     * Copy Constructor
     */
    Variable(const Variable &) = default;

    /**
     * Move Constructor
     */
    Variable(Variable &&) = default;

    /**
     * Assignment operator
     * @param rhs value
     * @return Variable value
     */
    Variable &operator=(const Variable &rhs) = default;

    /**
     * Indexed access operator
     * @param idx position
     * @return reference to value
     */
    int &operator[](int idx);

    /**
     * Indexed access operator
     * @param idx position
     * @return const reference to value
     */
    const int &operator[](int idx) const;

    /**
     * operator *
     * @return underlying Variable values
     */
    std::vector<int> &operator*();

    /**
     * Indexed access operator
     * @param idx position
     * @return reference to value
     */
    int &at(unsigned idx);

    /**
     * Indexed access operator
     * @param idx position
     * @return const reference to value
     */
    [[nodiscard]] const int &at(unsigned idx) const;

    /**
     * Returns dimension of the Variable
     * @return dimension of the Variable
     */
    [[nodiscard]] unsigned size() const;

    /**
     * Operator ==
     * @param rhs right side of comparison
     * @return true Variable if equal
     */
    Variable operator==(const Variable &rhs) const;

    /**
     * Operator !=
     * @param rhs right side of comparison
     * @return true Variable if not equal
     */
    Variable operator!=(const Variable &rhs) const;

    /**
     * Operator <
     * @param rhs right side of comparison
     * @return true Variable if less
     */
    Variable operator<(const Variable &rhs) const;

    /**
     * Operator >
     * @param rhs right side of comparison
     * @return true Variable if greater
     */
    Variable operator>(const Variable &rhs) const;

    /**
     * Operator <=
     * @param rhs right side of comparison
     * @return true Variable if less or equal
     */
    Variable operator<=(const Variable &rhs) const;

    /**
     * Operator >=
     * @param rhs right side of comparison
     * @return true Variable if greater or equal
     */
    Variable operator>=(const Variable &rhs) const;

    /**
     * Operator +
     * @return value of Variable
     */
    Variable operator+() const;

    /**
     * Operator -
     * @return negative value of Variable
     */
    Variable operator-() const;

    /**
     * Addition operator
     * @param rhs right operand
     * @return operation value
     */
    Variable operator+(const Variable &rhs) const;

    /**
     * Substraction operator
     * @param rhs right operand
     * @return operation value
     */
    Variable operator-(const Variable &rhs) const;

    /**
     * Multiplication operator
     * @param rhs right operand
     * @return operation value
     */
    Variable operator*(const Variable &rhs) const;

    /**
     * Division operator
     * @param rhs right operand
     * @return operation value
     */
    Variable operator/(const Variable &rhs) const;

    /**
     * Module operator
     * @param rhs right operand
     * @return operation value
     */
    Variable operator%(const Variable &rhs) const;

    /**
     * Negation operator
     * @return negated logic value of Variable
     */
    Variable operator!() const;

    /**
     * And logic operator
     * @param rhs right operand
     * @return operation value
     */
    Variable operator&&(const Variable &rhs) const;

    /**
     * Or logic operator
     * @param rhs right operand
     * @return operation value
     */
    Variable operator||(const Variable &rhs) const;

    /**
     * boolean operator
     * @return boolean value of Variable
     */
    operator bool() const;

    /**
     * Position of math operation
     * @param position
     */
    void setPosition(const Position &position);

    /**
     * Printable Variable value
     * @return printable Variable value
     */
    [[nodiscard]] std::string toString() const;

    /**
     * Stream operator
     * @param os stream
     * @return stream with outputted Variable
     */
    inline std::ostream &operator<<(std::ostream &os) const {
      os << toString();
      return os;
    }

  private:
    std::vector<int> values_; //!< can store normal value or 2,3(with
                              //!< possibility for more) dim vec
    Position currentPosition;

    static const Variable retTrue;
    static const Variable retFalse;
  };
} // namespace vecc::ast

#endif // VECC_LANG_VARIABLE_H
