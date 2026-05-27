#include "EulerIntegration.h"

StateVector EulerIntegration::Integrate(const DynamicalSystem& system, const StateVector& current_state, double time, double dt) const {
  // Calculate Derivative
  StateVector derivative = system.Derivative(current_state, time);

  // Create the list of state_values
  std::vector<double> next_state_values;

  // For each element in current_state. Use Euler's method to calculate the next state
  for (size_t i = 0; i < current_state.Size(); i++) {
    double current_value = current_state.Get(i);
    double derivative_value = derivative.Get(i);

    double next_value = current_value + dt * derivative_value;

    next_state_values.push_back(next_value);
  }

  StateVector new_state(next_state_values);

  return new_state;
}