#include "PerformanceAnalysis.h"

PerformanceAnalysis::PerformanceAnalysis(const std::vector<double>& time_vals, const std::vector<double>& response_vals) {
  // Check vector to ensure that they're both the same size, 
  if (time_vals.empty() || response_vals.empty())
    throw std::invalid_argument("Passed in vector(s) are empty.");

  if (time_vals.size() != response_vals.size())
    throw std::invalid_argument("Passed in vector(s) are of different size to each other!");

  // Verify that time values are strictly increasing
  for (size_t i = 0; i + 1 < time_vals.size(); ++i) {
    if (time_vals[i] >= time_vals[i + 1])
      throw std::invalid_argument("Passed in time values are not strictly increasing!");
  }

  // Store both passed in vectors
  time_values = time_vals;
  response_values = response_vals;

  // Steady_state_value is the value stored as the last response value
  steady_state_value = response_values[response_values.size() - 1];
}

double PerformanceAnalysis::GetSteadyStateValue() const {
  return steady_state_value;
}

double PerformanceAnalysis::GetOvershoot() const {
  // Find the max value in the response values list
  auto max_it = std::max_element(response_values.begin(), response_values.end());
  double max_value = *max_it;

  // Compute the overshoot
  double overshoot = max_value - steady_state_value;
  if (overshoot < 0)
    return 0;

  return overshoot;
}

