#include "StateVector.h"

StateVector StateVector::operator+(const StateVector& other) const {
  if (this->Size() != other.Size())
    throw std::invalid_argument("Incompatible vectors!");

  std::vector<double> result;

  for (size_t i = 0; i < this->Size(); i++) {
    result.push_back(this->Get(i) + other.Get(i));
  }

  StateVector new_vector(result);
  return new_vector;
}

StateVector StateVector::operator*(double scalar) const {
  std::vector<double> result;
  for (auto val : this->values) {
    result.push_back(val * scalar);
  }

  StateVector new_vector(result);
  return new_vector;
}

double& StateVector::operator[](size_t index) {
  return values.at(index);
}

const double& StateVector::operator[](size_t index) const {
  return values.at(index);
}

StateVector operator*(double scalar, const StateVector& vec) {
  return vec * scalar;
}

std::ostream& operator<<(std::ostream& os, const StateVector& vec) {
  for (auto value : vec.values) {
    os << value << " ";
  }
  os << std::endl;

  return os;
}