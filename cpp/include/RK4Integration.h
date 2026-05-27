#ifndef RK4INTEGRATION_H_
#define RK4INTEGRATION_H_

#include "DynamicalSystem.h"
#include "StateVector.h"

class RK4Integration {
  public:
    StateVector Integrate(const DynamicalSystem& , const StateVector& , double time, double dt);
};

#endif