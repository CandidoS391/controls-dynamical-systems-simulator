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

    // Private helper functions
    void BuildResponse();
  public:
    FrequencyResponse(const TransferFunction& user_ts, const std::vector<double>& user_freq);
};

#endif