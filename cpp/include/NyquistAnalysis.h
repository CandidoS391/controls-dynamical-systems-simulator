#ifndef NYQUISTANALYSIS_H_
#define NYQUISTANALYSIS_H_

#include <vector>
#include <complex>
#include <cmath>
#include <stdexcept>

#include "TransferFunction.h"

class NyquistAnalysis {
  private:
    TransferFunction transfer_function;

    std::vector<std::complex<double>> s_path;
    std::vector<std::complex<double>> mapped_path;

  public:
    // Constructor
    NyquistAnalysis(const TransferFunction& user_ts);

    // Nyquist path
    void GenerateNyquistPath(double max_frequency, size_t num_samples);
    void MapNyquistPath();

    const std::vector<std::complex<double>>& GetSPath() const;
    const std::vector<std::complex<double>>& GetMappedPath() const;
};

#endif