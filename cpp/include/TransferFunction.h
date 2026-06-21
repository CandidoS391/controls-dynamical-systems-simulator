#ifndef TRANSFERFUNCTION_H_
#define TRANSFERFUNCTION_H_

#include <vector>
#include <iostream>

class TransferFunction {
  private:
    std::vector<double> numerator;
    std::vector<double> denominator;

  public:
    TransferFunction(const std::vector<double>& num, const std::vector<double>& den);
    void Print() const;
    std::vector<double> GetNumerator() const;
    std::vector<double> GetDenominator() const;
};

#endif