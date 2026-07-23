#ifndef SENSITIVITYANALYSIS_H_
#define SENSITIVITYANALYSIS_H_

#include <vector>
#include <complex>
#include <cmath>
#include <stdexcept>
#include <algorithm>

#include "TransferFunction.h"

class SensitivityAnalysis {
  private:
    // polynomials
    std::vector<double> a_1;
    std::vector<double> a_2;
    std::vector<double> a_3;
    std::vector<double> a_4;
    // Parameter k
    double k_parameter;
    // Private polynomial operations
    static std::vector<double> RemoveLeadingZeros(const std::vector<double>& coefficients);
    static std::vector<double> ScalePolynomial(const std::vector<double>& polynomial, double scalar);
    static std::vector<double> AddPolynomials(const std::vector<double>& first, const std::vector<double>& second);
    static std::vector<double> SubtractPolynomials(const std::vector<double>& first, const std::vector<double>& second);
    static std::vector<double> MultiplyPolynomials(const std::vector<double>& first, const std::vector<double>& second);
    static bool IsZeroPolynomial(const std::vector<double>& polynomial);
  public:
    // Constructor
    SensitivityAnalysis(const std::vector<double>& a1, const std::vector<double>& a2, const std::vector<double>& a3, const std::vector<double>& a4, double parameter);
    TransferFunction GetNominalTransferFunction() const;
    TransferFunction GetTransferFunctionSensitivity() const;

};

#endif