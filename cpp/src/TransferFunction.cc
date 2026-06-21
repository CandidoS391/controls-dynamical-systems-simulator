#include "TransferFunction.h"

TransferFunction::TransferFunction(const std::vector<double>& num, const std::vector<double>& den) : numerator(num), denominator(den) {

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