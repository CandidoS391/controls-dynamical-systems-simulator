#include "NyquistAnalysis.h"

const double kPi = 3.14159265358979323846;

NyquistAnalysis::NyquistAnalysis(const TransferFunction& user_ts) : transfer_function(user_ts) {

}

void NyquistAnalysis::GenerateNyquistPath(double max_frequency, size_t num_samples, double indentation_radius) {
  // If max_frequency is negative, then it's invalid
  if (max_frequency <= 0)
    throw std::invalid_argument("The max frequency must be greater than 0!");

  // If the number of samples is less than 2, then it's invalid
  if (num_samples < 2)
    throw std::invalid_argument("Invalid number of samples");

  // If the indentation radius is NOT greater than 0 or less than the max_frequency, then throw
  if (indentation_radius < 0)
    throw std::invalid_argument("The indentation radius cannot be less than 0!");

  if (indentation_radius >= max_frequency)
    throw std::invalid_argument("The indentiation radius cannot be greater than or equal to the max frequency!");
  
  s_path.clear();

  // ------ TYPE 0 PATH (indentiation_radius == 0) ------
  if (indentation_radius == 0) {
    // ------ Part 1: Computing the positive imaginary axis ------
    double freq_step = max_frequency / (num_samples - 1);

    for (size_t i = 0; i < num_samples; i++) {
      double omega = i * freq_step;
      
      // Construct a complex number s and then store it to s_path
      std::complex<double> comp_s(0.0, omega);
      s_path.push_back(comp_s);
    }

    // ------ Part 2: Large right-half-plane semicricle ------
    double radius = max_frequency;

    // Compute angle theta from +pi/2 to -pi/2
    double angle_step = kPi / (num_samples - 1);

    for (size_t i = 1; i < num_samples; i++) {
      double theta = kPi / 2 - i * angle_step;
      
      // Build the real and imaginary parts for complex number s from theta
      double real_part = radius * std::cos(theta);
      double imaginary_part = radius * std::sin(theta);

      std::complex<double> complex_s(real_part, imaginary_part);
      s_path.push_back(complex_s);
    }

    // ------ Part 3: Negative imaginary axis ------
    // Do the same thing from part 1, only -omega this time
    for (int i = static_cast<int>(num_samples) - 2; i >= 0; i--) {
      double omega = i * freq_step;
      std::complex<double> s(0.0, -omega);

      s_path.push_back(s);
    }

    // Exit from type 0
    return;
  }

  // ------ INDENTED PATH (INDENTATION_RADIUS >= 1) ------
  // Let rho and R be equal to the indentation radius and the max frequency respectively
  // Use them to compute the frequency step
  double rho = indentation_radius, r = max_frequency;
  double freq_step = (r - rho) / (num_samples - 1);

  // Compute the large angle and small angle steps
  double angle_step = kPi / (num_samples - 1);

  // ---- Part 1: The Positive Imaginary Axis ----
  for (size_t i = 0; i < num_samples; i++) {
    double omega = rho + i * freq_step;

    // Build the real and imaginary parts of s
    double real_s = 0.0, imag_s = omega;
    
    // Build complex number s and then push it onto s_path
    std::complex<double> comp_s(real_s, imag_s);
    s_path.push_back(comp_s);
  }

  // ---- Part 2: Large RHP Semicircle ----
  for (size_t i = 1; i < num_samples; i++) {
    double theta = kPi / 2 - i * angle_step;

    // Build the real and imaginary parts
    double real_part = r * std::cos(theta), imag_part = r * std::sin(theta);

    std::complex<double> comp_s(real_part, imag_part);
    s_path.push_back(comp_s);
  }

  // ---- Part 3: Negative Imaginary Axis ----
  for (int i = static_cast<int>(num_samples) - 2; i >= 0; i--) {
    double omega = rho + i * freq_step;

    std::complex<double> comp_s(0.0, -omega);
    s_path.push_back(comp_s);
  }

  // ---- Part 4: Small Indentation Around the Origin ----
  for (size_t i = 1; i < num_samples; i++) {
    double theta = -kPi / 2 + i * angle_step;

    // Calculate the real and imaginary parts
    double real_part = rho * std::cos(theta), imag_part = rho * std::sin(theta);

    // Construct s from the real and imaginary parts
    std::complex<double> comp_s(real_part, imag_part);
    s_path.push_back(comp_s);
  }
}

void NyquistAnalysis::MapNyquistPath() {
  mapped_path.clear();

  // If the s path is empty, then the nyquist path hasn't been generated yet
  if (s_path.empty())
    throw std::runtime_error("The Nyquist path doesn't exist!");

  // For each complex value s in the s-path, evaluate the transfer function then store the result
  for (const auto& s : s_path) {
    std::complex<double> mapped_point = transfer_function.Evaluate(s);
    mapped_path.push_back(mapped_point);
  }
}

const std::vector<std::complex<double>>& NyquistAnalysis::GetSPath() const {
  return s_path;
}

const std::vector<std::complex<double>>& NyquistAnalysis::GetMappedPath() const {
  return mapped_path;
}

int NyquistAnalysis::CountOpenLoopRHPPoles() const {
  // Calculate the number of poles of the transfer function
  std::vector<std::complex<double>> poles = transfer_function.GetPoles();
  int count = 0;

  // For each pole found, if the real part of the pole > 0, increment count
  for (const auto& pole: poles) {
    if (pole.real() > 1e-8)
      count++;
  }

  // Return P (the count)
  return count;
}

int NyquistAnalysis::CountEncirclements() const {
  // Throw error if the mapped_path hasn't been made
  if (mapped_path.empty())
    throw std::runtime_error("Nyquist path hasn't been mapped.");

  double total_angle_change = 0;

  // Iterate through each pair of mapped points
  for (size_t i = 0; i < mapped_path.size() - 1; i++) {
    std::complex<double> current_point = mapped_path[i];
    std::complex<double> next_point = mapped_path[i + 1];

    // Shift the points by +1
    std::complex<double> current_shifted = current_point + 1.0;
    std::complex<double> next_shifted = next_point + 1.0;

    // Check if the path doesn't pass directly through the critical point
    if (std::abs(current_shifted) < 1e-8 || std::abs(next_shifted) < 1e-8)
      throw std::domain_error("Shifted point passes directly through the critical point (-1, 0).");

    // Calculate the angles of each shifted point
    double curr_angle = std::arg(current_shifted);
    double next_angle = std::arg(next_shifted);

    double angle_change = next_angle - curr_angle;

    // Correct the angle arapping
    if (angle_change > kPi)
      angle_change -= 2 * kPi;
    else if (angle_change < -kPi)
      angle_change += 2 * kPi;

    total_angle_change += angle_change;
  }

  // Convert the total angular motion into full revolutions
  double rotations = total_angle_change / (2 * kPi);

  // Let N be equal to -rotations
  int N = -static_cast<int>(std::round(rotations));

  return N;
}

int NyquistAnalysis::GetClosedLoopRHPPoles() const {
  int p_0 = CountOpenLoopRHPPoles();
  int n = CountEncirclements();

  // Return Z_0 = n + p_0
  int z_0 = n + p_0;
  if (z_0 < 0)
    throw std::runtime_error("Double check the functions, something is inconsistent with the numerical calculations.");

  return z_0;
}

bool NyquistAnalysis::IsStable() const {
  int z_0 = GetClosedLoopRHPPoles();

  if (z_0 == 0)
    return true;


  return false;
}

double NyquistAnalysis::GetPhaseCrossoverFrequency(double max_frequency, size_t num_samples) const {
  // Validate the inputs
  if (max_frequency <= 0)
    throw std::invalid_argument("The maximum frequency must be greater than 0.");

  if (num_samples <= 2)
    throw std::invalid_argument("The number of samnples must be greater than 2.");

  // Set up the frequency sweep
  double min_frequency = 1e-6;
  if (max_frequency <= min_frequency)
    throw std::invalid_argument("The max frequency passed in should not be less than or equal to 1e-8.");
  
  double freq_step = (max_frequency - min_frequency) / (num_samples - 1);

  // Evaluate the first usable frequency
  double prev_omega = min_frequency;
  std::complex<double> prev_s(0.0, prev_omega);
  std::complex<double> prev_response = transfer_function.Evaluate(prev_s);

  // Evaluate the remaining frequencies
  for (size_t i = 1; i < num_samples; i++) {
    // Get the current frequency
    double curr_omega = min_frequency + i * freq_step;
    std::complex<double> curr_s(0.0, curr_omega);
    std::complex<double> curr_response = transfer_function.Evaluate(curr_s);

    // Check for the imaginary-axis sign change
    double prev_imag = prev_response.imag();
    double curr_imag = curr_response.imag();

    // Tolerance check to check if the crossover frequency has already been hit
    if (curr_imag == 0.0 && curr_response.real() < 0)
      return curr_omega;

    // Here, compare the signs between the previous imaginary part and the current imaginary part
    // This means that a real-axis crossing has a occured between the two frequencies
    if (std::signbit(prev_imag) != std::signbit(curr_imag)) {
      // Interpolate between the two frequencies based on their imaginary components
      double fraction = -prev_imag / (curr_imag - prev_imag);
      double crossover_omega = prev_omega + fraction * (curr_omega - prev_omega);

      // Evaluate at the estimated crossover
      std::complex<double> crossover_s(0, crossover_omega);
      std::complex<double> crossover_response = transfer_function.Evaluate(crossover_s);

      // Evaluate the negative real axis
      if (crossover_response.real() < 0)
        return crossover_omega;
    }

    // Advance to the next frequency
    prev_omega = curr_omega;
    prev_response = curr_response;
  }

  // If there's no crossover found, then throw
  throw std::runtime_error("Phase crossover was not found.");
}

double NyquistAnalysis::GetGainMargin(double max_frequency, size_t num_samples) const {
  // Validate the inputs
  if (max_frequency <= 0)
    throw std::invalid_argument("The maximum frequency must be greater than 0.");

  if (num_samples <= 2)
    throw std::invalid_argument("The number of samples must be greater than 2.");

  // Calculate the phase crossover frequency
  double omega_pc = GetGainCrossoverFrequency(max_frequency, num_samples);
  std::complex<double> s_pc(0.0, omega_pc);
  std::complex<double> response = transfer_function.Evaluate(s_pc);

  // Calculate the magnitude
  double magnitude = std::abs(response);
  if (magnitude < 1e-8)
    throw std::domain_error("Calculated magnitude is approximately close to zero.");

  // Calculate the margin as 1 / magnitude, then return
  double gain_margin = 1 / magnitude;
  return gain_margin;
}

