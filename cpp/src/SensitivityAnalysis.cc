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
    negative_second[i] *= -1;
  }

  return AddPolynomials(first, negative_second);
}

std::vector<double> SensitivityAnalysis::MultiplyPolynomials(const std::vector<double>& first, const std::vector<double>& second) {
  if (first.empty() || second.empty())
    throw std::invalid_argument("Polynomial(s) are zero!");

  std::vector<double> result(first.size() + second.size() - 1, 0.0);

  // Add the product to the result position corresponding to the sum of their indices
  for (size_t i = 0; i < first.size(); i++) {
    for (size_t j = 0; j < second.size(); j++) {
      result[i + j] += first[i] * second[j];
    }
  }

  return RemoveLeadingZeros(result);
}

bool SensitivityAnalysis::IsZeroPolynomial(const std::vector<double>& polynomial) {
  if (polynomial.empty())
    throw std::invalid_argument("Polynomial is empty");

  constexpr double k_zero_tolerance = 1e-8;

  for (double coefficient : polynomial) {
    if (std::abs(coefficient) >= k_zero_tolerance)
      return false;
  }

  return true;
} 

std::vector<double> SensitivityAnalysis::RemoveLeadingZeros(const std::vector<double>& coefficients) {
  constexpr double k_zero_tolerance = 1e-8;

  if (coefficients.empty())
    return {0.0};

  size_t first_nonzero = 0;
  while (first_nonzero < coefficients.size() - 1 && std::abs(coefficients[first_nonzero]) < k_zero_tolerance) {
    first_nonzero++;
  }

  return std::vector<double>(coefficients.begin() + first_nonzero, coefficients.end());
}

TransferFunction SensitivityAnalysis::GetNominalTransferFunction() const {
  // build the nominal numerator A_1 + kA_2
  std::vector<double> new_a2 = ScalePolynomial(a_2, k_parameter);
  std::vector<double> nominal_numerator = AddPolynomials(a_1, new_a2);

  // Build the nominal denominator A_3 + kA_4
  std::vector<double> new_a4 = ScalePolynomial(a_4, k_parameter);
  std::vector<double> nominal_denominator = AddPolynomials(a_3, new_a4);

  // Check if the nominal denominator is a zero vector
  if (IsZeroPolynomial(nominal_denominator))
    throw std::invalid_argument("Denominator cannot be zero.");

  return TransferFunction(nominal_numerator, nominal_denominator);
}

TransferFunction SensitivityAnalysis::GetTransferFunctionSensitivity() const {
  /*
  Sensitivity here is defined by:
  k(A_2*A_3 - A_1*A_4) / (A_1 + kA_2)(A_3 + kA_4)
  */

  // Multiply A_2 and A_3 together, and A_1 and A_4 together
  std::vector<double> a2_by_a3 = MultiplyPolynomials(a_2, a_3);
  std::vector<double> a1_by_a4 = MultiplyPolynomials(a_1, a_4);

  // Subtract the differences
  std::vector<double> difference = SubtractPolynomials(a2_by_a3, a1_by_a4);
  std::vector<double> sensitivity_numerator = ScalePolynomial(difference, k_parameter);

  // Scale A_2 by parameter k, then add the result to A_1 as the first denominator factor
  std::vector<double> first_denom_factor = AddPolynomials(a_1, ScalePolynomial(a_2, k_parameter));

  // Scale A_4 by parameter k, then add the result to A_3 as the second denominator factor
  std::vector<double> second_denom_factor = AddPolynomials(a_3, ScalePolynomial(a_4, k_parameter));

  if (IsZeroPolynomial(first_denom_factor) || IsZeroPolynomial(second_denom_factor))
    throw std::invalid_argument("Denominator cannot be zero.");

  std::vector<double> sensitivity_denominator = MultiplyPolynomials(first_denom_factor, second_denom_factor);

  return TransferFunction(sensitivity_numerator, sensitivity_denominator);
}