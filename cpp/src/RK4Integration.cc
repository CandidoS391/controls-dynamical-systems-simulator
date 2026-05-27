#include "RK4Integration.h"

StateVector RK4Integration::Integrate(const DynamicalSystem& system, const StateVector& curr_state, double time, double dt) {
  // Calculate k1, k2, k3, k4 using Derivative functions
  StateVector k1 = system.Derivative(curr_state, time);

  StateVector temp_state_k2 = curr_state + 0.5 * dt * k1;
  StateVector k2 = system.Derivative(temp_state_k2, time + 0.5 * dt);

  StateVector temp_state_k3 = curr_state + 0.5 * dt * k2;
  StateVector k3 = system.Derivative(temp_state_k3, time + 0.5 * dt);

  StateVector temp_state_k4 = curr_state + dt * k3;
  StateVector k4 = system.Derivative(temp_state_k4, time + dt);
  
  // Compute the final state
  std::vector<double> next_state_values;
  for (size_t i = 0; i < curr_state.Size(); i++) {
    double curr_val = curr_state[i];

    double weighted_slope = k1[i] + 2 * k2[i] + 2 * k3[i] + k4[i];
    double next_value = curr_val + (dt / 6.0) * weighted_slope;

    next_state_values.push_back(next_value);
  }

  StateVector result(next_state_values);
  return result;
}