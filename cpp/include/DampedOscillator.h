#ifndef DAMPEDOSCILLATOR_H_
#define DAMPEDOSCILLATOR_H_

#include "DynamicalSystem.h"

class DampedOscillator : public DynamicalSystem {
  private:
    double damp_coefficient_c;
    double stiff_coefficient_k;

  public:
    DampedOscillator(double c, double k) : damp_coefficient_c(c), stiff_coefficient_k(k) {

    }
    StateVector Derivative(const StateVector& , double ) const override;
};

#endif