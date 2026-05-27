#include "HarmonicOscillator.h"

StateVector HarmonicOscillator::Derivative(const StateVector& state, double time) const {
  double x = state.Get(0), v = state.Get(1);

  double dx_dt = v, dv_dt = -angular_freq_omega * angular_freq_omega * x;

  std::vector<double> derivative_values {dx_dt, dv_dt};
  StateVector derivative(derivative_values);

  return derivative;
}