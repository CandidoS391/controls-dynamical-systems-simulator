#ifndef FORCEDOSCILLATOR_H_
#define FORCEDOSCILLATOR_H_

#include "DynamicalSystem.h"
#include "InputSignal.h"

class ForcedOscillator : public DynamicalSystem {
  private:
    double damping_coefficient_c;
    double stiffness_coefficient_k;
    const InputSignal& input_signal;
  public:
    ForcedOscillator(double c, double k, const InputSignal& reference) : damping_coefficient_c(c), stiffness_coefficient_k(k), input_signal(reference) {

    }
    StateVector Derivative(const StateVector& , double ) const override;
};

#endif