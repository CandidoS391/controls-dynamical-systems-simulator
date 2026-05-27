#include "FirstOrderDecay.h"

StateVector FirstOrderDecay::Derivative(const StateVector& state, double time) const {
  double x = state.Get(0);
  double dx_dt = -decay_k * x;

  std::vector<double> derivative_values = {dx_dt};

  StateVector derivative(derivative_values);

  return derivative;
}
