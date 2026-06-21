#include <cmath>

#include "TransferFunction.h"

TransferFunction::TransferFunction(const std::vector<double>& num, const std::vector<double>& den) : numerator(num), denominator(den) {

}

double TransferFunction::EvaluatePolynomial(const std::vector<double>& coefficients, double s) const {
  if (coefficients.size() == 0)
    return 0;
  
  double result = 0;
  int degree = static_cast<int>(coefficients.size() - 1);

  for (double coe : coefficients) {
    result += coe * std::pow(s, degree);
    degree--;
  }

  return result;
}

size_t TransferFunction::Degree(const std::vector<double>& coefficients) const {
  if(coefficients.size() == 0)
    return 0;
  
  return coefficients.size() - 1;
}

std::vector<double> TransferFunction::FindRoots(const std::vector<double>& coefficients) const {
  if (Degree(coefficients) == 0)
    return {};

  if (Degree(coefficients) == 1) {
    // a = coefficient[0], b = coefficient[1]
    double root = -coefficients[1] / coefficients[0]; // For now assume that coefficients[0] != 0
    return {root};
  }

  if (Degree(coefficients) == 2) {
    // a = coefficient[0], b = coefficient[1], c = coefficient[2]
    double discriminant = std::pow(coefficients[1], 2) - (4 * coefficients[0] * coefficients[2]);

    if (discriminant >= 0) {
      double root_1 = (-coefficients[1] + std::sqrt(discriminant)) / (2 * coefficients[0]);
      double root_2 = (-coefficients[1] - std::sqrt(discriminant)) / (2 * coefficients[0]);
      return {root_1, root_2};
    }

    return {};
  }

  return {};
}

void TransferFunction::Print() const {
  // Print out numerator values
  std::cout << "Numerator: ";
  for (double val : numerator)
    std::cout << val << " ";
  std::cout << std::endl;

  // Print out denominator values
  std::cout << "Denominator: ";
  for (double val : denominator)
    std::cout << val << " ";
  std::cout << std::endl;
}

std::vector<double> TransferFunction::GetNumerator() const {
  return numerator;
}

std::vector<double> TransferFunction::GetDenominator() const {
  return denominator;
}

size_t TransferFunction::GetNumeratorDegree() const {
  return Degree(numerator);
}

size_t TransferFunction::GetDenominatorDegree() const {
  return Degree(denominator);
}

double TransferFunction::Evaluate(double s) const {
  double numerator_value = EvaluatePolynomial(numerator, s);
  double denominator_value = EvaluatePolynomial(denominator, s);

  return numerator_value / denominator_value;
}

std::vector<double> TransferFunction::GetPoles() const {
  return FindRoots(denominator);
}

std::vector<double> TransferFunction::GetZeros() const {
  return FindRoots(numerator);
}

bool TransferFunction::IsStrictlyProper() const {
  return (Degree(numerator) < Degree(denominator));
}

bool TransferFunction::IsProper() const {
  return (Degree(numerator) <= Degree(denominator));
}

bool TransferFunction::IsImproper() const {
  return (Degree(numerator) > Degree(denominator));
}