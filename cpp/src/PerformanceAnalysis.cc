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
  // Check if the steady-state value is approaching zero
  if (std::abs(steady_state_value) < 1e-8)
    throw std::domain_error("Steady-state value cannot be zero");

  double overshoot = 0;

  // If response is positive, find the max response
  if (steady_state_value > 0) {
    double max_response = *std::max_element(response_values.begin(), response_values.end());

    overshoot = max_response - steady_state_value;
  }
  // If the response is negative, find the minimum response
  else {
    double min_response = *std::min_element(response_values.begin(), response_values.end());

    overshoot = steady_state_value - min_response;
  }

  // If there was no overshoot, return zero. Otherwise return the overshoot
  if (overshoot < 0)
    return 0;

  return overshoot;
}

double PerformanceAnalysis::GetPercentOvershoot() const {
  // Check if steady_state_error is approximately zero
  // if true, then stop as percent overshoot is underfined relative to a zero final value
  if (std::abs(steady_state_value) < 1e-8)
    throw std::domain_error("Percent overshoot is undefined");

  double overshoot = GetOvershoot();

  return (overshoot / std::abs(steady_state_value)) * 100;
}

double PerformanceAnalysis::GetDelayTime() const {
  if (std::abs(steady_state_value) < 1e-8)
    throw std::domain_error("Steady-state values cannot be zero");

  double target = steady_state_value * 0.5;

  // From the beginning of the response values, if a sample is greater than or equal to
  // the target at the direction of the steady_state_value, 
  // then return that value. Otherwise, throw a runtime_error
  for (size_t i = 0; i < response_values.size(); i++) {
    if ((steady_state_value > 0 && response_values[i] >= target) || (steady_state_value < 0 && response_values[i] <= target))
      return time_values[i];
  }

  throw std::runtime_error("No response values have reached 50 percent of its final value.");
}

double PerformanceAnalysis::GetRiseTime() const {
  if (std::abs(steady_state_value) < 1e-8)
    throw std::domain_error("Steady-state error cannot be zero.");

  // Calculate the lower and upper targets using 10 percent and 90 percent of the steady_state_value
  double lower_target = 0.10 * steady_state_value;
  double upper_target = 0.90 * steady_state_value;

  bool lower_time_found = false, upper_time_found = false;
  double lower_time, upper_time;

  // Iterate through the response samples from beginning to end
  for (size_t i = 0; i < response_values.size(); i++) {
    // If there's yet to be a lower_time
    if (!lower_time_found) {
      // Check if the response value has reached or crossed
      // The lower target at the direction of the steady_state_value. If yes, store the lower_time as the current_time 
      if ((steady_state_value > 0 && response_values[i] >= lower_target) || (steady_state_value < 0 && response_values[i] <= lower_target)) {
        lower_time = time_values[i];
        lower_time_found = true;
      }
    } // Otherwise, find the upper_time 
    else {
      // Check if the response value has reached or crossed
      // The upper_target at the direction of the steady_state_value. If yes, store the upper_time as the current_time
      if ((steady_state_value > 0 && response_values[i] >= upper_target) || (steady_state_value < 0 && response_values[i] <= upper_target)) {
        upper_time = time_values[i];
        upper_time_found = true;
        break;
      }
    }
  }

  // If lower_time_found or upper_time_found is false, then throw runtime_error
  if (!lower_time_found)
    throw std::runtime_error("Response never reaches 10 percent of its final value");

  if (!upper_time_found)
    throw std::runtime_error("Response never reaches 90 percent of its final value");

  return upper_time - lower_time;
}

