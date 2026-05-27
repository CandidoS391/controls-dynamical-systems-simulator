#ifndef FORCEDOSCILLATOR_H_
#define FORCEDOSCILLATOR_H_

#include "DynamicalSystem.h"

class ForcedOscillator : public DynamicalSystem {
  private:
    double damping_coefficient_c;
    double stiffness_coefficient_k;
    double forcing_amp_a;
    double forcing_ang_freq;
  public:
    ForcedOscillator(double c, double k, double a, double omega) : damping_coefficient_c(c), stiffness_coefficient_k(k), forcing_amp_a(a), forcing_ang_freq(omega) {

    }
    StateVector Derivative(const StateVector& , double ) const override;
};

#endif