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

std::vector<double> FrequencyResponse::GenerateFrequencySweep(double start_frequency, double end_frequency, size_t num_samples) {
  // Check if the starting frequency is negative. If true, then throw an invalid argument
  if (start_frequency < 0)
    throw std::invalid_argument("The starting frequency cannot be negative!");

  // Check if the end frequency is less than the starting frequency. If true, then throw
  if (end_frequency < start_frequency)
    throw std::invalid_argument("The end frequency cannot be less than the starting frequency!");

  // Check if the number of samples is less than 2. If true, then throw
  if (num_samples < 2)
    throw std::invalid_argument("The number of samples cannot be less than 2!");

  // Main frequency vector
  std::vector<double> frequency_sweep;

  // Compute the step
  double step = (end_frequency - start_frequency) / (num_samples - 1);

  // Populate the frequency vector
  for (size_t i = 0; i < num_samples; i++) {
    double frequency = start_frequency + i * step;
    frequency_sweep.push_back(frequency);
  }

  return frequency_sweep;
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