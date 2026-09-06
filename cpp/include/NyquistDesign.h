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
};

#endif