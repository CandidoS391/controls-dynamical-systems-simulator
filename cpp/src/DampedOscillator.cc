#include "DampedOscillator.h"

StateVector DampedOscillator::Derivative(const StateVector& curr_state, double time) const {
  double x = curr_state[0], v = curr_state[1];

  double dx_dt = v;
  double dv_dt = -damp_coefficient_c * v - stiff_coefficient_k * x;

  return StateVector({dx_dt, dv_dt});
}