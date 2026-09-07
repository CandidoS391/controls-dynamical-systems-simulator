#include "NyquistDesign.h"

NyquistDesign::NyquistDesign(const TransferFunction& user_ts) : transfer_function(user_ts) {

}

double NyquistDesign::CalculateResonantPeak(double gain, double max_frequency, size_t num_samples) const {
  // Validate all inputs
  if (gain <= 0)
    throw std::invalid_argument("The gain factor must be greater than 0.");

  if (max_frequency <= 0)
    throw std::invalid_argument("The max frequency must be greater than 0.");

  if (num_samples <= 2)
    throw std::invalid_argument("The number of samples must be greater than 2.");

  // Initialize the search
  double resonant_peak = 0.0;
  double frequency_step = max_frequency / (num_samples - 1);

  // Sweep through the frequencies
  for (size_t i = 0; i < num_samples; i++) {
    double omega = i * frequency_step;
    std::complex<double> comp_s(0, omega);

    // Evaluate the uncompensated frequency response function
    std::complex<double> response = transfer_function.Evaluate(comp_s);

    // Apply the gain compensation
    std::complex<double> compensated_response = gain * response;

    // Construct closed-loop denominator
    std::complex<double> denominator = 1.0 + compensated_response;

    // Handle singularity
    if (std::abs(denominator) < 1e-8)
      throw std::runtime_error("Closed loop response approaches infinity.");

    // Calculate the closed-loop response
    std::complex<double> closed_loop_response = compensated_response / denominator;
    double m = std::abs(closed_loop_response);

    // Update the maximum
    if (m > resonant_peak)
      resonant_peak = m;
  }

  return resonant_peak;
}

double NyquistDesign::FindGainForResonantPeak(double desired_peak, double min_gain, double max_gain, double max_frequency, size_t num_samples, double tolerance, size_t max_iterations) const {
  // Validate the basic inputs
  if (desired_peak <= 0)
    throw std::invalid_argument("The desired peak must be greater than 0.");

  if (min_gain <= 0)
    throw std::invalid_argument("The minimum gain must be greater than 0.");

  if (max_gain <= min_gain)
    throw std::invalid_argument("The max gain passed in must be greater than the minimum gain.");

  if (tolerance <= 0)
   throw std::invalid_argument("The tolerance must be greater than 0.");

  if (max_iterations == 0)
    throw std::invalid_argument("The maximum iterations must not equal 0.");

  // Evaluate both ends of the gain interval
  double min_peak = CalculateResonantPeak(min_gain, max_frequency, num_samples);
  double max_peak = CalculateResonantPeak(max_gain, max_frequency, num_samples);

  // Verify that the desired peak is bracketed
  if (desired_peak < min_peak || desired_peak > max_peak)
    throw std::runtime_error("The desired peak in not within the min and max peaks.");

  // Begin the bisection
  double lower_gain = min_gain, upper_gain = max_gain;

  for (size_t i = 0; i < max_iterations; i++) {
    double candidate_gain = (lower_gain + upper_gain) / 2;
    double candidate_peak = CalculateResonantPeak(candidate_gain, max_frequency, num_samples);
    double error = candidate_peak - desired_peak;

    // Determine if the desired resonant peak has been reached
    if (std::abs(error) < tolerance)
      return candidate_gain;

    // If the M_p increases as K increases
    if (candidate_peak < desired_peak)
      lower_gain = candidate_gain;
    else
      upper_gain = candidate_gain;
  }

  // If convergence was not reached, throw
  throw std::runtime_error("Bisection method diverged.");
}