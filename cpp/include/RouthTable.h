#ifndef ROUTHTABLE_H_
#define ROUTHTABLE_H_

#include <vector>
#include <cmath>
#include <stdexcept>
#include <iostream>

#include "StabilityStatus.h"

class RouthTable {
  private:
    std::vector<double> coefficients;
    std::vector<std::vector<double>> table;
    size_t zero_row_count = 0;

    // Check if row in the table is completely zero
    bool RowIsZero(const std::vector<double>& row) const;
    // Replace row if its a zero row
    void ReplaceZeroRow(size_t row_index);

  public:
    explicit RouthTable(const std::vector<double>& coe);
    void Build();
    void Print() const;
    StabilityStatus GetStability() const;
};

#endif