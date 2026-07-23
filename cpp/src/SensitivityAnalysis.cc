#include "SensitivityAnalysis.h"

SensitivityAnalysis::SensitivityAnalysis(const std::vector<double>& a1, const std::vector<double>& a2, const std::vector<double>& a3, const std::vector<double>& a4, double parameter) : a_1(a1), a_2(a2), a_3(a3), a_4(a4), k_parameter(parameter) {
  
}

std::vector<double> SensitivityAnalysis::ScalePolynomial(const std::vector<double>& polynomial, double scalar) {
  if (polynomial.empty())
    throw std::invalid_argument("Empty Polynomial!");

  // Copy the passed in polynomial and make that the result  
  std::vector<double> result = polynomial;

  // Go through each element of the result polynomial and multiply it by the scalar
  for (size_t i = 0; i < result.size(); i++) {
    result[i] *= scalar;
  }

  return result;
}

std::vector<double> SensitivityAnalysis::AddPolynomials(const std::vector<double>& first, const std::vector<double>& second) {
  // Double check if passed in vectors are nonzero
  if (first.empty() || second.empty())
    throw std::invalid_argument("Invalid polynomial(s)!");

  size_t result_size = std::max(first.size(), second.size());
  std::vector<double> result(result_size, 0);

  // Align the vectors
  size_t poly_1_idx = result_size - first.size();
  size_t poly_2_idx = result_size - second.size();

  // Copy the elements of polynomial 1 into results
  for (size_t i = 0; i < first.size(); i++) {
    result[poly_1_idx + i] = first[i];
  }

  // Add polynomial 2 to the results vector
  for (size_t i = 0; i < second.size(); i++) {
    result[poly_2_idx + i] += second[i];
  }

  return RemoveLeadingZeros(result);
}

std::vector<double> SensitivityAnalysis::SubtractPolynomials(const std::vector<double>& first, const std::vector<double>& second) {
  // Multiply the second polynomial by negative 1
  // Then add the first polynomial with the now negative second polynomial
  std::vector<double> negative_second = second;
  for (size_t i = 0; i < negative_second.size(); i++) {
    negative_second[i] *= 1;
  }

  return AddPolynomials(first, negative_second);
}



std::vector<double> TransferFunction::RemoveLeadingZeros(const std::vector<double>& coefficients) {
  constexpr double k_zero_tolerance = 1e-8;

  if (coefficients.empty())
    return {0.0};

  size_t first_nonzero = 0;
  while (first_nonzero < coefficients.size() - 1 && std::abs(coefficients[first_nonzero]) < k_zero_tolerance) {
    first_nonzero++;
  }

  return std::vector<double>(coefficients.begin() + first_nonzero, coefficients.end());
}