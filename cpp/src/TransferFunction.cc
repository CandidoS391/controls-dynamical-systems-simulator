#include <cmath>
#include <algorithm>
#include <complex>

#include "StabilityStatus.h"
#include "TransferFunction.h"

const double kPi = 3.14159265358979323846;

TransferFunction::TransferFunction(const std::vector<double>& num, const std::vector<double>& den) : numerator(RemoveLeadingZeros(num)), denominator(RemoveLeadingZeros(den)) {
  if (denominator.size() == 1 && std::abs(denominator[0]) < 1e-12)
    throw std::invalid_argument("Invalid denominator");
}

double TransferFunction::EvaluatePolynomial(const std::vector<double>& coefficients, double s) const {
  if (coefficients.empty())
    return 0;
  
  double result = 0;
  size_t degree = coefficients.size() - 1;

  for (double coe : coefficients) {
    result += coe * std::pow(s, degree);
    degree--;
  }

  return result;
}

std::complex<double> TransferFunction::EvaluatePolynomial(const std::vector<double>& coefficients, const std::complex<double>& value) const {
  if (coefficients.empty())
    return std::complex<double>(0.0, 0.0);

  
  std::complex<double> result(0.0, 0.0);
  size_t degree = coefficients.size() - 1;

  for (const auto& coe : coefficients) {
    result += coe * std::pow(value, degree);
    degree--;
  }

  return result;
}

size_t TransferFunction::Degree(const std::vector<double>& coefficients) const {
  if(coefficients.size() == 0)
    return 0;
  
  return coefficients.size() - 1;
}

std::vector<double> TransferFunction::RemoveLeadingZeros(const std::vector<double>& coefficients) {
  constexpr double k_zero_tolerance = 1e-12;

  if (coefficients.empty())
    return {0.0};

  size_t first_nonzero = 0;

  while (first_nonzero < coefficients.size() - 1 && std::abs(coefficients[first_nonzero]) < k_zero_tolerance) {
    first_nonzero++;
  }

  return std::vector<double>(coefficients.begin() + first_nonzero, coefficients.end());
}

std::vector<PoleGroup> TransferFunction::GroupPoles(const std::vector<std::complex<double>>& poles) const {
  double tolerance = 1e-7;

  std::vector<PoleGroup> groups;
  for (const auto& pole : poles) {
    bool found_group = false;

    for (auto& group : groups) {
      double distance = std::abs(pole - group.pole);
      if (distance < tolerance) {
        group.multiplicity++;
        found_group = true;
        break;
      }
    }

    if (found_group == false) {
      PoleGroup new_group;
      new_group.pole = pole;
      new_group.multiplicity = 1;
      groups.push_back(new_group);
    }
  }

  return groups;
}

std::vector<double> TransferFunction::DividePolynomialByLinearFactor(const std::vector<double>& coefficients, double pole) const {
  if (coefficients.size() <= 1)
    throw std::invalid_argument("Invalid number of passed in coefficients.");
  
  double tolerance = 1e-7;
  std::vector<double> quotient;
  double current_value = coefficients[0];
  quotient.push_back(current_value);

  for (size_t i = 1; i < coefficients.size() - 1; i++) {
    current_value = coefficients[i] + pole * current_value;
    quotient.push_back(current_value);
  }

  double remainder = coefficients[coefficients.size() - 1] + pole * current_value;
  if (std::abs(remainder) > tolerance) {
    throw std::runtime_error("Pole is not a root");
  }

  return quotient;
}

std::vector<std::complex<double>> TransferFunction::FindRoots(const std::vector<double>& coefficients) const {
  std::vector<double> cleaned = RemoveLeadingZeros(coefficients);

  if (Degree(cleaned) == 0)
    return {};

  if (Degree(cleaned) == 1) {
    // a = coefficient[0], b = coefficient[1]
    double root = -cleaned[1] / cleaned[0]; // For now assume that coefficients[0] != 0
    return {std::complex<double>(root, 0.0)};
  }

  if (Degree(cleaned) == 2) {
    // a = coefficient[0], b = coefficient[1], c = coefficient[2]
    double discriminant = std::pow(cleaned[1], 2) - (4 * cleaned[0] * cleaned[2]);

    if (discriminant >= 0) {
      double root_1 = (-cleaned[1] + std::sqrt(discriminant)) / (2 * cleaned[0]);
      double root_2 = (-cleaned[1] - std::sqrt(discriminant)) / (2 * cleaned[0]);
      return {std::complex<double>(root_1, 0.0), std::complex<double>(root_2, 0.0)};
    } else {
      double real_part = -cleaned[1] / (2 * cleaned[0]);
      double imag_part = std::sqrt(-discriminant) / std::abs(2 * cleaned[0]);
      return {std::complex<double>(real_part, imag_part), std::complex<double>(real_part, -imag_part)};
    }
  }

  return FindRootsNumerically(cleaned);
}

std::vector<std::complex<double>> TransferFunction::GenerateInitialGuesses(const std::vector<double>& coefficients) const {
  size_t degree = Degree(coefficients);
  if (degree <= 0) {
    throw std::invalid_argument("Polynomial degrees must be greater than 0");
  }

  std::vector<double> normalized = coefficients;

  double leading_coefficient = normalized[0];

  // Normalize the vector
  for (auto& coefficient : normalized) {
    coefficient /= leading_coefficient;
  }

  double radius = 1.0;

  for (size_t i = 1; i < normalized.size(); i++) {
    radius = std::max(radius, 1 + std::abs(normalized[i]));
  }

  std::vector<std::complex<double>> guesses;
  

  for (size_t k = 0; k < degree; k++) {
    double angle = (2 * kPi * k) / degree + (kPi / (2 * degree));
    double real_part = radius * std::cos(angle);
    double imag_part = radius * std::sin(angle);

    guesses.push_back(std::complex<double>(real_part, imag_part));
  }

  return guesses;
}

std::vector<std::complex<double>> TransferFunction::FindRootsNumerically(const std::vector<double>& coefficients) const {
  size_t degree = Degree(coefficients);
  if (degree <= 0) {
    throw std::invalid_argument("Polynomial degrees must be greater than 0");
  }
  std::vector<std::complex<double>> roots = GenerateInitialGuesses(coefficients);

  double tolerance = 1e-10;
  size_t max_iterations = 1000;

  for (size_t iteration = 0; iteration < max_iterations; iteration++) {
    std::vector<std::complex<double>> updated_roots;
    double max_change = 0;
    for (size_t i = 0; i < roots.size(); i++) {
      std::complex<double> curr_root(roots[i]);
      std::complex<double> numerator(EvaluatePolynomial(coefficients, curr_root));
      std::complex<double> denominator(1.0, 0.0);

      for (size_t j = 0; j < roots.size(); j++) {
        if (i == j)
          continue;

        std::complex<double> difference(roots[i] - roots[j]);
        denominator = denominator * difference;
      }

      std::complex<double> new_root = curr_root - (numerator / denominator);
      double change = std::abs(new_root - curr_root);
      max_change = std::max(max_change, change);
      updated_roots.push_back(new_root);
    }
    roots = updated_roots;

    if (max_change < tolerance)
      break;
  }

  return roots;
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

std::vector<double> TransferFunction::DifferentiatePolynomial(const std::vector<double>& coefficients) const {
  if (coefficients.empty())
    return {};

  std::vector<double> cleaned = RemoveLeadingZeros(coefficients);

  size_t degree = Degree(cleaned);

  if (degree == 0)
    return {0};

  std::vector<double> derivative;
  for (size_t i = 0; i < cleaned.size() - 1; i++) {
    size_t curr_power = degree - i;
    double derivative_coefficient = cleaned[i] * curr_power;
    derivative.push_back(derivative_coefficient);
  }

  return derivative;
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

StabilityStatus TransferFunction::GetStability() const {
  bool has_imaginary_axis_pole = false;
  std::vector<std::complex<double>> poles = GetPoles();

  for (const auto& pole : poles) {
    if (pole.real() > 0)
      return StabilityStatus::k_unstable;

    if (pole.real() == 0)
      has_imaginary_axis_pole = true;

  }

  if (has_imaginary_axis_pole)
    return StabilityStatus::k_marginally_stable;
  
  return StabilityStatus::k_stable;
}

void TransferFunction::PrintStability() const {
  StabilityStatus stability = GetStability();

  switch (stability) {
    case StabilityStatus::k_stable:
      std::cout << "System is stable\n";
      break;
    case StabilityStatus::k_marginally_stable:
      std::cout << "System is marginally stable\n";
      break;
    case StabilityStatus::k_unstable:
      std::cout << "System is unstable\n";
      break;
  }
}

std::vector<PartialFractionTerm> TransferFunction::PartialFractionExpansion() const {
  if (Degree(numerator) >= Degree(denominator))
    throw std::invalid_argument("Partial fraction decomposition requires a proper transfer function.");

  std::vector<std::complex<double>> poles = GetPoles();
  std::vector<PoleGroup> groups = GroupPoles(poles);
  double tolerance = 1e-8;

  std::vector<double> denominator_derivative = DifferentiatePolynomial(denominator);

  std::vector<PartialFractionTerm> terms;
  for (const auto& group : groups) {
    if (group.multiplicity == 1) {
      const std::complex<double>& pole = group.pole;

      std::complex<double> numerator_value = EvaluatePolynomial(numerator, pole);
      std::complex<double> derivative_value = EvaluatePolynomial(denominator_derivative, pole);
      std::complex<double> residue = numerator_value / derivative_value;

      PartialFractionTerm term;
      term.residue = residue;
      term.pole = pole;
      term.multiplicity = 1;

      terms.push_back(term);
    } else if (group.multiplicity == 2) {
      if (std::abs(group.pole.imag()) >= tolerance)
        throw std::invalid_argument("Imaginary part of pole is over tolerance");

      double real_pole = group.pole.real();

      std::vector<double> q_coefficients = denominator;
      q_coefficients = DividePolynomialByLinearFactor(q_coefficients, real_pole);
      q_coefficients = DividePolynomialByLinearFactor(q_coefficients, real_pole);

      std::complex<double> pole_complex = group.pole;
      std::complex<double> n_at_p = EvaluatePolynomial(numerator, pole_complex);
      std::complex<double> q_at_p = EvaluatePolynomial(q_coefficients, pole_complex);
      std::complex<double> a_2 = n_at_p / q_at_p;

      std::vector<double> numerator_derivative = DifferentiatePolynomial(numerator);
      std::vector<double> q_derivative = DifferentiatePolynomial(q_coefficients);
      std::complex<double> n_prime_at_p = EvaluatePolynomial(numerator_derivative, pole_complex);
      std::complex<double> q_prime_at_p = EvaluatePolynomial(q_derivative, pole_complex);
      std::complex<double> a_1 = (n_prime_at_p * q_at_p - n_at_p * q_prime_at_p) / (q_at_p * q_at_p);

      PartialFractionTerm term_1;
      term_1.residue = a_1;
      term_1.pole = group.pole;
      term_1.multiplicity = 1;
      terms.push_back(term_1);

      PartialFractionTerm term_2;
      term_2.residue = a_2;
      term_2.pole = group.pole;
      term_2.multiplicity = 2;
      terms.push_back(term_2);
    } else {
      throw std::invalid_argument("Pole multiplicities greater than two are not supported.");
    }
  }

  return terms;
}