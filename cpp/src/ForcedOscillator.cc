#include <cmath>

#include "ForcedOscillator.h"

StateVector ForcedOscillator::Derivative(const StateVector& state, double time) const {
  double x = state[0], v = state[1];

  double input = input_signal.Value(time);

  double dx_dt = v;
  double dv_dt = -damping_coefficient_c * v - stiffness_coefficient_k * x + input;

  return StateVector({dx_dt, dv_dt});
}