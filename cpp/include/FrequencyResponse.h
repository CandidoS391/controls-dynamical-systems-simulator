#ifndef FREQUENCYRESPONSE_H_
#define FREQUENCYRESPONSE_H_

#include <vector>
#include <complex>
#include <cmath>
#include <stdexcept>

#include "TransferFunction.h"

class FrequencyResponse {
  private:
    // Private variables
    TransferFunction transfer_function;
    std::vector<double> frequencies;
    std::vector<std::complex<double>> responses;
    std::vector<double> magnitudes;
    std::vector<double> phases;

    // Private helper function for constructor
    void BuildResponse();


  public:
    // Constructor
    FrequencyResponse(const TransferFunction& user_ts, const std::vector<double>& user_freq);

    // Getter functions
    const std::vector<double>& GetFrequencies() const;
    const std::vector<std::complex<double>>& GetResponses() const;
    const std::vector<double>& GetMagnitudes() const;
    const std::vector<double>& GetPhases() const;

    // Frequency sweep generator
    static std::vector<double> GenerateFrequencySweep(double start_frequency, double end_frequency, size_t num_samples);
};

#endif