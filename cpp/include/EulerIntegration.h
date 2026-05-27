#ifndef EULERINTEGRATION_H_
#define EULERINTEGRATION_H_

#include "DynamicalSystem.h"
#include "StateVector.h"

class EulerIntegration {
  public:
    StateVector Integrate(const DynamicalSystem& system, const StateVector& current_state, double time, double dt) const;
};

#endif