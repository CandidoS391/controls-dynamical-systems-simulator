#ifndef TRANSFERFUNCTION_H_
#define TRANSFERFUNCTION_H_

#include <vector>
#include <iostream>

class TransferFunction {
  private:
    std::vector<double> numerator;
    std::vector<double> denominator;

    double EvaluatePolynomial(const std::vector<double>& coefficients, double s) const;
    size_t Degree(const std::vector<double>& coefficients) const;

  public:
    TransferFunction(const std::vector<double>& num, const std::vector<double>& den);
    void Print() const;
    std::vector<double> GetNumerator() const;
    std::vector<double> GetDenominator() const;
    size_t GetNumeratorDegree() const;
    size_t GetDenominatorDegree() const;
    double Evaluate(double s) const;
};

#endif