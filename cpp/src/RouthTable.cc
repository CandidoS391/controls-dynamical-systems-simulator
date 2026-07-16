#include "RouthTable.h"

constexpr double kZeroTolerance = 1e-12;

RouthTable::RouthTable(const std::vector<double>& coe) : coefficients(coe) {

}

bool RouthTable::RowIsZero(const std::vector<double>& row) const {
  double tolerance = 1e-12;

  for (const auto& value : row) {
    if (std::abs(value) >= tolerance)
      return false;
  }

  return true;
}

void RouthTable::Build() {
  if (coefficients.empty())
    throw std::invalid_argument("Characteristic polynomial cannot be empty.");

  size_t degree = coefficients.size() - 1;

  size_t rows = degree + 1;
  size_t columns = (degree + 2) / 2;

  table.assign(rows, std::vector<double>(columns, 0.0));

  size_t coefficient_index = 0;

  // Fill row 0
  // coefficients of s^degree, s^(degree-2), ...
  for (size_t i = 0; i < columns; i++) {
    if (coefficient_index < coefficients.size()) {
      table[0][i] = coefficients[coefficient_index];
      coefficient_index += 2;
    }
  }

  // Check if row 0 is not zero
  if (RowIsZero(table[0]))
    throw std::runtime_error("First row of Routh table cannot be entirely zero.");

  coefficient_index = 1;

  // Fill row 1
  // Coefficients s^(degree-1), s^(degree-3), ...
  if (rows > 1) {
    for (size_t i = 0; i < columns; i++) {
      if (coefficient_index < coefficients.size()) {
        table[1][i] = coefficients[coefficient_index];
        coefficient_index += 2;
      }
    }

    // Check if row 1 is not zero after populating it
    if (RowIsZero(table[1]))
      throw std::runtime_error("Entire row of zeros detected.");
  }

  // Build rows 2 through rows - 1
  for (size_t i = 2; i < rows; i++) {
    double pivot = table[i - 1][0];

    // Version 1 handling for a zero first-column value
    if (std::abs(pivot) < kZeroTolerance) {
      pivot = kZeroTolerance;
      table[i - 1][0] = kZeroTolerance;
    }

    for (size_t j = 0; j < columns - 1; j++) {
      double upper_left = table[i - 2][0];
      double lower_left = table[i - 1][0];

      double upper_next = table[i - 2][j + 1];
      double lower_next = table[i - 1][j + 1];

      table[i][j] = (lower_left * upper_next - upper_left * lower_next) / lower_left;
    }
    // Check for a zero row after an entire row has been populated
    if (RowIsZero(table[i]))
      throw std::runtime_error("Entire row of zeros detected.");
  }

}

void RouthTable::Print() const {
  std::cout << "Values of Routh Table:\n";
  std::cout << std::endl; 
  for (const auto& row : table) {
    for (const auto& val : row) {
      std::cout << val << "\t";
    }
    std::cout << std::endl;
  }
}

StabilityStatus RouthTable::GetStability() const {
  size_t sign_changes = 0;

  for (size_t i = 0; i < table.size() - 1; i++) {
    double current = table[i][0];
    double next = table[i + 1][0];

    if ((current > 0 && next < 0) || (current < 0 && next > 0)) {
      sign_changes++;
    }
  }

  if (sign_changes == 0)
    return StabilityStatus::k_stable;

  return StabilityStatus::k_unstable;
}