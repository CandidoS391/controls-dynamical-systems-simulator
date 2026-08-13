#include "FrequencyResponse.h"

void FrequencyResponse::BuildResponse() {
  // Check if the frequencies vector is empty. If so, throw an invalid argument
  if (frequencies.empty())
    throw std::invalid_argument("The frequencies vector is empty!");

  // Clear out the responses, magnitudes, and phases vectors
  responses.clear(); magnitudes.clear(); phases.clear();

  for (const auto& omega : frequencies) {
    if (omega < 0)
      throw std::invalid_argument("All frequencies must be >= 0!");

    // Declare a complex value s = 0 + j * omega
    std::complex<double> complex_s(0.0, omega);

    // Evaluate the transfer function and store the resulting response in the responses vector
    std::complex<double> response = transfer_function.Evaluate(complex_s);
    responses.push_back(response);

    // Compute the magnitude and store it
    double magnitude = std::abs(response);
    magnitudes.push_back(magnitude);

    // Compute the phase and store it
    double phase = std::arg(response);
    phases.push_back(phase);
  }
}

FrequencyResponse::FrequencyResponse(const TransferFunction& user_ts, const std::vector<double>& user_freq) : transfer_function(user_ts), frequencies(user_freq) {
  // Use the already stored transfer function and frquencies and call BuildResponse()
  BuildResponse();
}

const std::vector<double>& FrequencyResponse::GetFrequencies() const {
  return frequencies;
}

const std::vector<std::complex<double>>& FrequencyResponse::GetResponses() const {
  return responses;
}

const std::vector<double>& FrequencyResponse::GetMagnitudes() const {
  return magnitudes;
}

const std::vector<double>& FrequencyResponse::GetPhases() const {
  return phases;
}