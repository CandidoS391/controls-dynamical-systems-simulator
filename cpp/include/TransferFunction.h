#ifndef TRANSFERFUNCTION_H_
#define TRANSFERFUNCTION_H_

#include <vector>
#include <iostream>

class TransferFunction {
  private:
    std::vector<double> numerator;
    std::vector<double> denominator;


    // Evaluate Polynomial at specified value s
    double EvaluatePolynomial(const std::vector<double>& coefficients, double s) const;
    // Find the degree of the polynomial
    size_t Degree(const std::vector<double>& coefficients) const;
    // Find the roots of a polynomial
    std::vector<double> FindRoots(const std::vector<double>& coefficients) const;
    // Operations on two given polynomials
    std::vector<double> MultiplyPolynomials(const std::vector<double>& poly_1, const std::vector<double>& poly_2) const;
    std::vector<double> AddPolynomials(const std::vector<double>& poly_1, const std::vector<double>& poly_2) const;

  public:
    // Constructor
    TransferFunction(const std::vector<double>& num, const std::vector<double>& den);

    // Print out the contents of the Transfer function
    void Print() const;

    // Getter functions
    std::vector<double> GetNumerator() const;
    std::vector<double> GetDenominator() const;
    size_t GetNumeratorDegree() const;
    size_t GetDenominatorDegree() const;

    // Evaluate the Transfer function
    double Evaluate(double s) const;

    // Retrieve the Zeros and Poles of the Transfer Function
    std::vector<double> GetZeros() const;
    std::vector<double> GetPoles() const;

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
    
};

#endif