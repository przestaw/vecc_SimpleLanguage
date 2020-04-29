#include <AST/general/variable.h>
#include <error/exeception.h>

using namespace vecc;
using namespace vecc::ast;

const Variable Variable::retTrue  = Variable({1});
const Variable Variable::retFalse = Variable({0});

Variable::Variable(std::vector<int> values) : values_(std::move(values)) {}

int &Variable::operator[](int idx) { return values_[idx]; }

const int &Variable::operator[](int idx) const { return values_[idx]; }

std::vector<int> &Variable::operator*() { return values_; }

int &Variable::at(unsigned idx) {
  if (idx < values_.size()) {
    return values_.at(idx);
  } else {
    throw error::RangeException(
        "index out of range on "
        + ((size() != 1) ? (std::to_string(size()) + "-dimension vector's \n")
                         : "variable")
        + (currentPosition != Position() ? "at " + currentPosition.toString()
                                         : ""));
  }
}

const int &Variable::at(unsigned idx) const {
  if (idx < values_.size()) {
    return values_.at(idx);
  } else {
    throw error::RangeException(
        "index out of range on "
        + ((size() != 1) ? (std::to_string(size()) + "-dimension vector's \n")
                         : "variable")
        + (currentPosition != Position() ? "at " + currentPosition.toString()
                                         : ""));
  }
}

unsigned int Variable::size() const { return values_.size(); }

Variable Variable::operator==(const Variable &rhs) const {
  if (values_.size() == rhs.values_.size()) {
    if (values_ == rhs.values_) {
      return retTrue;
    } else {
      return retFalse;
    }
  } else {
    throw error::MathException(
        "Can't compare " + std::to_string(values_.size())
        + "-dimension vector and " + std::to_string(rhs.values_.size())
        + "-dimension vector\n"
        + (currentPosition != Position() ? "at " + currentPosition.toString()
                                         : ""));
  }
}

Variable Variable::operator!=(const Variable &rhs) const {
  return !(*this == rhs);
}

Variable Variable::operator<(const Variable &rhs) const {
  if (size() == 1) {
    if (this->values_[0] < rhs.values_[0]) {
      return retTrue;
    } else {
      return retFalse;
    }
  } else {
    throw error::MathException(
        "Can't compare vectors to be greater/less from each other\n"
        + (currentPosition != Position() ? "at " + currentPosition.toString()
                                         : ""));
  }
}

Variable Variable::operator>(const Variable &rhs) const { return rhs < *this; }

Variable Variable::operator<=(const Variable &rhs) const {
  return !(rhs < *this);
}

Variable Variable::operator>=(const Variable &rhs) const {
  return !(*this < rhs);
}

Variable Variable::operator+() const { return *this; }

Variable Variable::operator-() const {
  Variable var(std::vector<int>(values_.size()));
  for (unsigned i = 0; i < values_.size(); ++i) { var[i] = -values_[i]; }
  return var;
}

Variable Variable::operator+(const Variable &rhs) const {
  Variable var;
  if (values_.size() == rhs.values_.size()) {
    var = *this;
    for (unsigned i = 0; i < values_.size(); ++i) { var[i] += rhs.values_[i]; }
  } else {
    throw error::MathException(
        "Can't add " + std::to_string(values_.size()) + "-dimension vector and "
        + std::to_string(rhs.values_.size()) + "-dimension vector\n"
        + (currentPosition != Position() ? "at " + currentPosition.toString()
                                         : ""));
  }

  return var;
}

Variable Variable::operator-(const Variable &rhs) const {
  Variable var;
  if (values_.size() == rhs.values_.size()) {
    var = *this;
    for (unsigned i = 0; i < values_.size(); ++i) { var[i] -= rhs.values_[i]; }
  } else {
    throw error::MathException(
        "Can't add " + std::to_string(values_.size()) + "-dimension vector and "
        + std::to_string(rhs.values_.size()) + "-dimension vector\n"
        + (currentPosition != Position() ? "at " + currentPosition.toString()
                                         : ""));
  }

  return var;
}

Variable Variable::operator*(const Variable &rhs) const {
  Variable var;
  if (values_.size() == 1) {
    var = rhs;
    for (auto &variable : var.values_) { variable *= values_[0]; }
  } else if (rhs.values_.size() == 1) {
    var = *this;
    for (auto &variable : var.values_) { variable *= rhs.values_[0]; }
  } else {
    throw error::MathException(
        "Can't multiply " + std::to_string(values_.size())
        + "-dimension vector by " + std::to_string(rhs.values_.size())
        + "-dimension vector\n"
        + (currentPosition != Position() ? "at " + currentPosition.toString()
                                         : ""));
  }

  return var;
}

Variable Variable::operator/(const Variable &rhs) const {
  Variable var;
  if (rhs.values_.size() == 1) {
    var = *this;
    for (auto &variable : var.values_) {
      if (rhs.values_[0]) {
        variable /= rhs.values_[0];
      } else {
        throw error::MathException("Can't divide by 0 \n"
                                   + (currentPosition != Position()
                                          ? "at " + currentPosition.toString()
                                          : ""));
      }
    }
  } else {
    throw error::MathException(
        "Can't divide " + std::to_string(values_.size())
        + "-dimension vector by " + std::to_string(rhs.values_.size())
        + "-dimension vector\n"
        + (currentPosition != Position() ? "at " + currentPosition.toString()
                                         : ""));
  }

  return var;
}

Variable Variable::operator%(const Variable &rhs) const {
  Variable var;
  if (rhs.values_.size() == 1) {
    var = *this;
    for (auto &variable : var.values_) {
      if (rhs.values_[0]) {
        variable %= rhs.values_[0];
      } else {
        throw error::MathException("Can't modulo by 0 \n"
                                   + (currentPosition != Position()
                                          ? "at " + currentPosition.toString()
                                          : ""));
      }
    }
  } else {
    throw error::MathException(
        "Can't modulo " + std::to_string(values_.size())
        + "-dimension vector by " + std::to_string(rhs.values_.size())
        + "-dimension vector\n"
        + (currentPosition != Position() ? "at " + currentPosition.toString()
                                         : ""));
  }

  return var;
}

Variable Variable::operator!() const {
  if (*this) {
    return retFalse;
  } else {
    return retTrue;
  }
}

Variable Variable::operator&&(const Variable &rhs) const {
  if (static_cast<bool>(*this) && static_cast<bool>(rhs)) {
    return retTrue;
  } else {
    return retFalse;
  }
}

Variable Variable::operator||(const Variable &rhs) const {
  if (static_cast<bool>(*this) || static_cast<bool>(rhs)) {
    return retTrue;
  } else {
    return retFalse;
  }
}

Variable::operator bool() const {
  return std::count(values_.begin(), values_.end(), 0) != this->size();
}

void Variable::setPosition(const Position &position) {
  this->currentPosition = position;
}

std::string Variable::toString() const {
  std::string buf;
  if (size() == 1) {
    buf = std::to_string(values_[0]);
  } else {
    buf.append("[ ");
    for (unsigned i = 0; i < values_.size(); ++i) {
      buf.append(std::to_string(values_[i]));
      if (i < values_.size() - 1) {
        buf.append(", ");
      }
    }
    buf.append(" ]");
  }
  return buf;
}