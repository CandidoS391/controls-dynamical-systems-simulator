#ifndef TRANSFERFUNCTION_H_
#define TRANSFERFUNCTION_H_

#include <vector>
#include <iostream>
#include <complex>
#include <stdexcept>

#include "StabilityStatus.h"

struct PartialFractionTerm {
  std::complex<double> residue;
  std::complex<double> pole;
  size_t multiplicity;
};

struct PoleGroup {
  std::complex<double> pole;
  size_t multiplicity;
};

class TransferFunction {
  private:
    std::vector<double> numerator;
    std::vector<double> denominator;


    // Evaluate Polynomial at specified value s
    double EvaluatePolynomial(const std::vector<double>& coefficients, double s) const;
    // Additional Polynomial at specified COMPLEX value s
    std::complex<double> EvaluatePolynomial(const std::vector<double>& coefficients, const std::complex<double>& value) const;
    // Find the degree of the polynomial
    size_t Degree(const std::vector<double>& coefficients) const;
    // Find the roots of a polynomial
    std::vector<std::complex<double>> FindRoots(const std::vector<double>& coefficients) const;
    // Operations on two given polynomials
    std::vector<double> MultiplyPolynomials(const std::vector<double>& poly_1, const std::vector<double>& poly_2) const;
    std::vector<double> AddPolynomials(const std::vector<double>& poly_1, const std::vector<double>& poly_2) const;
    std::vector<double> SubtractPolynomials(const std::vector<double>& poly_1, const std::vector<double>& poly_2) const;
    // Find polynomial roots numerically 
    std::vector<std::complex<double>> FindRootsNumerically(const std::vector<double>& coefficients) const;
    // Make initial guesses for Finding Roots numerically
    std::vector<std::complex<double>> GenerateInitialGuesses(const std::vector<double>& coefficients) const;
    // Differentiate Polynomial
    std::vector<double> DifferentiatePolynomial(const std::vector<double>& coefficients) const;
    // Remove Leading Zeros
    static std::vector<double> RemoveLeadingZeros(const std::vector<double>& coefficients);
    // Group the poles for Partial Fraction Expression
    std::vector<PoleGroup> GroupPoles(const std::vector<std::complex<double>>& poles) const;
    // Dividing Polynomials by a real linear factor
    std::vector<double> DividePolynomialByLinearFactor(const std::vector<double>& coefficients, double pole) const;

  public:
    // Constructor
    TransferFunction(const std::vector<double>& num, const std::vector<double>& den);

    // Print out the contents of the Transfer function
    void Print() const;

    // Stability Analysis
    StabilityStatus GetStability() const;
    void PrintStability() const;

    // Getter functions
    std::vector<double> GetNumerator() const;
    std::vector<double> GetDenominator() const;
    size_t GetNumeratorDegree() const;
    size_t GetDenominatorDegree() const;

    // Evaluate the Transfer function
    double Evaluate(double s) const;

    // Retrieve the Zeros and Poles of the Transfer Function
    std::vector<std::complex<double>> GetZeros() const;
    std::vector<std::complex<double>> GetPoles() const;

    // Classifcation functions
    bool IsStrictlyProper() const;
    bool IsProper() const;
    bool IsImproper() const;

    // Series, Feedback, and Parallel functions
    TransferFunction Series(const TransferFunction& other) const;
    TransferFunction Parallel(const TransferFunction& other) const;
    TransferFunction Feedback() const;

    // Test functions
    void TestMultiplyPolynomials() const;
    void TestAddPolynomials() const;

    // Evaluate via Partial Fractions
    std::vector<PartialFractionTerm> PartialFractionExpansion() const;

    // Overloaded Operations
    friend std::ostream& operator<<(std::ostream& os, const TransferFunction& rhs);
    TransferFunction operator-(const TransferFunction& other) const;
    TransferFunction operator/(const TransferFunction& other) const;
};

#endif