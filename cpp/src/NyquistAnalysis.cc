#include "NyquistAnalysis.h"

const double kPi = 3.14159265358979323846;

NyquistAnalysis::NyquistAnalysis(const TransferFunction& user_ts) : transfer_function(user_ts) {

}

void NyquistAnalysis::GenerateNyquistPath(double max_frequency, size_t num_samples) {
  // If max_frequency is negative, then it's invalid
  if (max_frequency <= 0)
    throw std::invalid_argument("The max frequency cannot be negative!");

  // If the number of samples is less than 2, then it's invalid
  if (num_samples < 2)
    throw std::invalid_argument("Invalid number of samples");

  
  s_path.clear();

  // ------ Part 1: Computing the positive imaginary axis ------
  double freq_step = max_frequency / (num_samples - 1);

  for (size_t i = 0; i < num_samples; i++) {
    double omega = i * freq_step;
    
    // Construct a complex number s and then store it to s_path
    std::complex<double> comp_s(0.0, omega);
    s_path.push_back(comp_s);
  }

  // ------ Part 2: Large right-half-plane semicricle ------
  double radius = max_frequency;

  // Compute angle theta from +pi/2 to -pi/2
  double angle_step = kPi / (num_samples - 1);

  for (size_t i = 1; i < num_samples; i++) {
    double theta = kPi / 2 - i * angle_step;
    
    // Build the real and imaginary parts for complex number s from theta
    double real_part = radius * std::cos(theta);
    double imaginary_part = radius * std::sin(theta);

    std::complex<double> complex_s(real_part, imaginary_part);
    s_path.push_back(complex_s);
  }

  // ------ Part 3: Negative imaginary axis ------
  // Do the same thing from part 1, only -omega this time
  for (int i = static_cast<int>(num_samples) - 2; i >= 0; i--) {
    double omega = i * freq_step;
    std::complex<double> s(0.0, -omega);

    s_path.push_back(s);
  }
}

void NyquistAnalysis::MapNyquistPath() {
  mapped_path.clear();

  // If the s path is empty, then the nyquist path hasn't been generated yet
  if (s_path.empty())
    throw std::runtime_error("The Nyquist path doesn't exist!");

  // For each complex value s in the s-path, evaluate the transfer function then store the result
  for (const auto& s : s_path) {
    std::complex<double> mapped_point = transfer_function.Evaluate(s);
    mapped_path.push_back(mapped_point);
  }
}

const std::vector<std::complex<double>>& NyquistAnalysis::GetSPath() const {
  return s_path;
}

const std::vector<std::complex<double>>& NyquistAnalysis::GetMappedPath() const {
  return mapped_path;
}