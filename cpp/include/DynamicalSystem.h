#ifndef DYNAMICALSYSTEM_H_
#define DYNAMICALSYSTEM_H_

#include "StateVector.h"

class DynamicalSystem {
  public:
    virtual StateVector Derivative (const StateVector& state, double time) const = 0;

    virtual ~DynamicalSystem() = default;
};

#endif