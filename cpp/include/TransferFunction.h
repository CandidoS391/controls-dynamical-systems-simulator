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
    std::vector<double> FindRoots(const std::vector<double>& coefficients) const;
    std::vector<double> MultiplyPolynomials(const std::vector<double>& poly_1, const std::vector<double>& poly_2) const;
    std::vector<double> AddPolynomials(const std::vector<double>& poly_1, const std::vector<double>& poly_2) const;

  public:
    TransferFunction(const std::vector<double>& num, const std::vector<double>& den);
    void Print() const;
    std::vector<double> GetNumerator() const;
    std::vector<double> GetDenominator() const;
    size_t GetNumeratorDegree() const;
    size_t GetDenominatorDegree() const;
    double Evaluate(double s) const;
    std::vector<double> GetZeros() const;
    std::vector<double> GetPoles() const;
    bool IsStrictlyProper() const;
    bool IsProper() const;
    bool IsImproper() const;

    // Test functions
    void TestMultiplyPolynomials() const;
    void TestAddPolynomials() const;
    
};

#endif