#ifndef RLCCIRCUIT_H_
#define RLCCIRCUIT_H_

#include "DynamicalSystem.h"
#include "InputSignal.h"

class RLCCircuit : public DynamicalSystem {
  private:
    double resistance_r;
    double inductance_l;
    double capacity_c;
    const InputSignal& input;

  public:
    RLCCircuit(double r, double l, double c, const InputSignal& in);
    StateVector Derivative(const StateVector& state, double time) const override;
};

#endif