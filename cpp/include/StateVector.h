#ifndef STATEVECTOR_H_
#define STATEVECTOR_H_

#include <vector>
#include <iostream>
#include <stdexcept>

class StateVector {
  private:
    std::vector<double> values;
    
  public:
    // Default constructor
    StateVector() : values() {

    }
    // Constructor that takes in existing vector
    StateVector(const std::vector<double>& list) : values(list) {

    }
    // Returns number of state variables
    size_t Size() const {
      return values.size();
    }
    // Access a value at a given index
    double Get(size_t index) const {
      return values[index];
    }
    // Modify a values at a given index
    void Set(size_t index, double value) {
      values[index] = value;
    }

    // Overloaded functions
    StateVector operator+(const StateVector& other) const;
    StateVector operator*(double scalar) const;
    double& operator[](size_t index);
    const double& operator[](size_t index) const;
    friend StateVector operator*(double scalar, const StateVector& vec);
    friend std::ostream& operator<<(std::ostream& os, const StateVector& vec);

};

#endif