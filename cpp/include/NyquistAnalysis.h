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
    void GenerateNyquistPath(double max_frequency, size_t num_samples, double indentation_radius = 0.0);
    void MapNyquistPath();

    // Getter functions
    const std::vector<std::complex<double>>& GetSPath() const;
    const std::vector<std::complex<double>>& GetMappedPath() const;

    // Count the number of open loop poles for G(S)H(s) at the right hand plane (P)
    int CountOpenLoopRHPPoles() const;
    // Count the number of clockwise encirclements around (-1, 0) (N)
    int CountEncirclements() const;
    // Calculate the number of closed loop RHP Poles from P and N (Z)
    int GetClosedLoopRHPPoles() const;
    // Determine Stability based on if Z <= 0
    bool IsStable() const;

    // ---- CALCULATING RELATIVE STABILITY ----
    // Calculate the phase crossover frequency
    double GetPhaseCrossoverFrequency(double max_frequency, size_t num_samples) const;
    // Calculate the gain crossover frequency
    double GetGainCrossoverFrequency(double max_frequency, size_t num_samples) const;
    // Calculate the gain margin
    double GetGainMargin(double max_frequency, size_t num_samples) const;
    // Calculate the phase margin
    double GetPhaseMargin(double max_frequency, size_t num_samples) const;
};

#endif