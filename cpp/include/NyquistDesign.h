#ifndef NYQUISTDESIGN_H_
#define NYQUISTDESIGN_H_

#include <vector>
#include <cmath>
#include <complex>
#include <stdexcept>

#include "TransferFunction.h"

class NyquistDesign {
  private:
    TransferFunction transfer_function;

  public:
    // Contructor
    NyquistDesign(const TransferFunction& user_ts);
    // Calculate the resonant peak via gain-factor compensation
    double CalculateResonantPeak(double gain, double max_frequency, size_t num_samples) const;
    // Calculate the Gain-factor for the resonant peak using the bisection method
    double FindGainForResonantPeak(double desired_peak, double min_gain, double max_gain, double max_frequency, size_t num_samples, double tolerance, size_t max_iterations) const;
    // Calculate the lead compensated response
    std::complex<double> CalculateLeadCompensatedResponse(double omega, double compensator_gain, double zero, double pole) const;
    // Calculat the lag compensated response
    std::complex<double> CalculateLagCompensatedResponse(double omega, double compensator_gain, double zero, double pole) const;
};

#endif