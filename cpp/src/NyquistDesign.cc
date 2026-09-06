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