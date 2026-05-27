#ifndef HARMONICOSCILLATOR_H_
#define HARMONICOSCILLATOR_H_

#include "DynamicalSystem.h"

class HarmonicOscillator : public DynamicalSystem {
  private:
    double angular_freq_omega;

  public:
    HarmonicOscillator(double omega) : angular_freq_omega(omega) {

    }
    StateVector Derivative(const StateVector& state, double time) const override;
};

#endif