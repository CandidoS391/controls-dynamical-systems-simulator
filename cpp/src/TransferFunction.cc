#include <cmath>
#include <algorithm>
#include <complex>


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

std::vector<std::complex<double>> TransferFunction::FindRoots(const std::vector<double>& coefficients) const {
  if (Degree(coefficients) == 0)
    return {};

  if (Degree(coefficients) == 1) {
    // a = coefficient[0], b = coefficient[1]
    double root = -coefficients[1] / coefficients[0]; // For now assume that coefficients[0] != 0
    return {std::complex<double>(root, 0.0)};
  }

  if (Degree(coefficients) == 2) {
    // a = coefficient[0], b = coefficient[1], c = coefficient[2]
    double discriminant = std::pow(coefficients[1], 2) - (4 * coefficients[0] * coefficients[2]);

    if (discriminant >= 0) {
      double root_1 = (-coefficients[1] + std::sqrt(discriminant)) / (2 * coefficients[0]);
      double root_2 = (-coefficients[1] - std::sqrt(discriminant)) / (2 * coefficients[0]);
      return {std::complex<double>(root_1, 0.0), std::complex<double>(root_2, 0.0)};
    } else {
      double real_part = -coefficients[1] / std::abs(2 * coefficients[0]);
      double imag_part = std::sqrt(-discriminant) / (2 * coefficients[0]);
      return {std::complex<double>(real_part, imag_part), std::complex<double>(real_part, -imag_part)};
    }
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

std::vector<std::complex<double>> TransferFunction::GetPoles() const {
  return FindRoots(denominator);
}

std::vector<std::complex<double>> TransferFunction::GetZeros() const {
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

std::vector<double> TransferFunction::MultiplyPolynomials(const std::vector<double>& poly_1, const std::vector<double>& poly_2) const {
  std::vector<double> result(poly_1.size() + poly_2.size() - 1, 0);

  for (size_t i = 0; i < poly_1.size(); i++) {
    for (size_t j = 0; j < poly_2.size(); j++) {
      result[i + j] += poly_1[i] * poly_2[j];
    }
  }

  return result;
}

std::vector<double> TransferFunction::AddPolynomials(const std::vector<double>& poly_1, const std::vector<double>& poly_2) const {
  size_t result_size = std::max(poly_1.size(), poly_2.size());
  std::vector<double> result(result_size, 0);

  // Align the vectors by their ends
  size_t poly_1_idx = result_size - poly_1.size();
  size_t poly_2_idx = result_size - poly_2.size();

  // Copy the elements of polynomial 1
  for (size_t i = 0; i < poly_1.size(); i++) {
    result[poly_1_idx + i] = poly_1[i];
  }

  // Add polynomial 2 to the results vector
  for (size_t i = 0; i < poly_2.size(); i++) {
    result[poly_2_idx + i] += poly_2[i];
  }

  return result;
}

std::vector<double> TransferFunction::SubtractPolynomials(const std::vector<double>& poly_1, const std::vector<double>& poly_2) const {
  size_t result_size = std::max(poly_1.size(), poly_2.size());
  std::vector<double> result(result_size, 0);

  // Align the vectors by their ends
  size_t poly_1_idx = result_size - poly_1.size();
  size_t poly_2_idx = result_size - poly_2.size();

  // Copy the elements of polynomial 1
  for (size_t i = 0; i < poly_1.size(); i++) {
    result[poly_1_idx + i] = poly_1[i];
  }
  
  // Subtract Polynomial 2 to the results vector
  for (size_t i = 0; i < poly_2.size(); i++) {
    result[poly_2_idx + i] -= poly_2[i];
  }

  return result;
}

void TransferFunction::TestMultiplyPolynomials() const {
  std::vector<double> result = MultiplyPolynomials({1, 1}, {1, 2});
  std::cout << "Result ";
  for (double coefficient : result)
    std::cout << coefficient << " ";
  std::cout << std::endl;
}

void TransferFunction::TestAddPolynomials() const {
  std::vector<double> poly_1 = {1, 3, 2};
  std::vector<double> poly_2 = {1, 5};

  std::vector<double> result = AddPolynomials(poly_1, poly_2);

  std::cout << "AddPolynomials test result: ";
  for (double coeff : result) {
    std::cout << coeff << " ";
  }
  std::cout << std::endl;
}

TransferFunction TransferFunction::Series(const TransferFunction& other) const {
  std::vector<double> new_numerator = MultiplyPolynomials(this->numerator, other.numerator);
  std::vector<double> new_denominator = MultiplyPolynomials(this->denominator, other.denominator);

  return TransferFunction(new_numerator, new_denominator);
}

TransferFunction TransferFunction::Parallel(const TransferFunction& other) const {
  std::vector<double> left_numerator = MultiplyPolynomials(this->numerator, other.denominator);
  std::vector<double> right_numerator = MultiplyPolynomials(other.numerator, this->denominator);

  std::vector<double> new_numerator = AddPolynomials(left_numerator, right_numerator);
  std::vector<double> new_denominator = MultiplyPolynomials(this->denominator, other.denominator);

  return TransferFunction(new_numerator, new_denominator);
}

TransferFunction TransferFunction::Feedback() const {
  std::vector<double> new_denominator = AddPolynomials(denominator, numerator);
  
  return TransferFunction(numerator, new_denominator);
}

std::ostream& operator<<(std::ostream& os, const TransferFunction& rhs) {
  os << "Numerator: ";
  for (auto i : rhs.numerator) {
    os << i << " ";
  }
  os << " / Denominator: ";
  for (auto i : rhs.denominator) {
    os << i << " ";
  }

  return os;
}

TransferFunction TransferFunction::operator-(const TransferFunction& other) const {
  std::vector<double> left_numerator = MultiplyPolynomials(this->numerator, other.denominator);
  std::vector<double> right_numerator = MultiplyPolynomials(this->denominator, other.numerator);

  std::vector<double> new_numerator = SubtractPolynomials(left_numerator, right_numerator);
  std::vector<double> new_denominator = MultiplyPolynomials(this->denominator, other.denominator);

  return TransferFunction(new_numerator, new_denominator);
}

TransferFunction TransferFunction::operator/(const TransferFunction& other) const {
  std::vector<double> new_numerator = MultiplyPolynomials(this->numerator, other.denominator);
  std::vector<double> new_denominator = MultiplyPolynomials(this->denominator, other.numerator);

  return TransferFunction(new_numerator, new_denominator);
}

bool TransferFunction::IsStable() const {
  std::vector<std::complex<double>> poles = GetPoles();

  for (const auto& pole : poles) {
    if (pole.real() >= 0)
      return false;
  }

  return true;
}

void TransferFunction::PrintStability() const {
  if (IsStable()) {
    std::cout << "System is stable" << std::endl;
  } else {
    std::cout << "System is unstable" << std::endl;
  }
}