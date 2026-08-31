#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <complex>
#include <cmath>

#include "StateVector.h"
#include "DynamicalSystem.h"
#include "FirstOrderDecay.h"
#include "EulerIntegration.h"
#include "HarmonicOscillator.h"
#include "RK4Integration.h"
#include "DampedOscillator.h"
#include "ForcedOscillator.h"
#include "SineSignal.h"
#include "StepSignal.h"
#include "ConstantSignal.h"
#include "RampSignal.h"
#include "ImpulseSignal.h"
#include "TransferFunction.h"
#include "RLCCircuit.h"
#include "SignalFlowGraph.h"
#include "RouthTable.h"
#include "StabilityStatus.h"
#include "FeedbackSystem.h"
#include "SensitivityAnalysis.h"
#include "PerformanceAnalysis.h"
#include "FrequencyResponse.h"
#include "NyquistAnalysis.h"

//const double kPi = 3.14159265358979323846;

void SimulateFirstOrderDecayEuler() {
  FirstOrderDecay decay(0.5);
  EulerIntegration euler;

  StateVector state({10.0});

  double time = 0.0, dt = 0.01;
  int steps = 1000;
  std::ofstream ofs("output/decay_euler.csv");
  if (!ofs.is_open()) {
    std::cerr << "Error opening file: output/decay_euler.csv" << std::endl;
    return;
  }

  ofs << "time,x\n";
  for (int i = 0; i <= steps; i++) {
    ofs << time << "," << state.Get(0) << "\n";
    state = euler.Integrate(decay, state, time, dt);
    time += dt;
  }
}

void SimulateFirstOrderDecayRK4() {
  FirstOrderDecay decay(0.5);
  RK4Integration rk4;
  StateVector state({10.0});

  double time = 0.0;
  double dt = 0.01;
  int steps = 1000;

  std::ofstream ofs("output/decay_rk4.csv");
  if (!ofs.is_open()) {
    std::cerr << "Error opening file: output/decay_rk4.csv" << std::endl;
    return;
  }

  ofs << "time,x\n";
  for (int i = 0; i <= steps; i++) {
    ofs << time << "," << state.Get(0) << "\n";
    state = rk4.Integrate(decay, state, time, dt);
    time += dt;
  }
}

void SimulateHarmonicOscillatorEuler() {
  HarmonicOscillator oscillator(1.0);
  EulerIntegration euler;

  StateVector state({1.0, 0.0});

  double time = 0.0;
  double dt = 0.01;
  int steps = 1000;

  std::ofstream ofs("output/harmonic_oscillator_euler.csv");
  if (!ofs.is_open()) {
    std::cerr << "Error opening file: output/harmonic_oscillator_euler.csv" << std::endl;
    return;
  }

  ofs << "time,x,v\n";
  for (int i = 0; i <= steps; i++) {
    ofs << time << "," << state.Get(0) << "," << state.Get(1) << "\n";
    state = euler.Integrate(oscillator, state, time, dt);
    time += dt;
  }
}

void SimulateHarmonicOscillatorRK4() {
  HarmonicOscillator oscillator(1.0);
  RK4Integration rk4;
  StateVector state({1.0, 0.0});

  double time = 0.0;
  double dt = 0.01;
  int steps = 1000;

  std::ofstream ofs("output/harmonic_oscillator_rk4.csv");
  if (!ofs.is_open()) {
    std::cerr << "Error opening file output/harmonic_oscillator_rk4.csv" << std::endl;
    return;
  }

  ofs << "time,x,v\n";
  for (int i = 0; i <= steps; i++) {
    ofs << time << "," << state.Get(0) << "," << state.Get(1) << "\n";
    state = rk4.Integrate(oscillator, state, time, dt);
    time += dt;
  }
}

void SimulateDampedOscillatorEuler() {
  DampedOscillator damped(0.5, 1.0);
  EulerIntegration euler;

  StateVector state({1.0, 0.0});

  double time = 0.0;
  double dt = 0.01;
  int steps = 3000;

  std::ofstream ofs("../output/damped_oscillator_euler.csv");
  if (!ofs.is_open()) {
    std::cerr << "Error opening file output/damped_oscillator_euler.csv" << std::endl;
    return;
  }

  ofs << "time,x,v\n";

  for (int i = 0; i <= steps; i++) {
    ofs << time << "," << state[0] << "," << state[1] << "\n";

    state = euler.Integrate(damped, state, time, dt);
    time += dt;
  }
}

void SimulateDampedOscillatorRK4() {
  DampedOscillator damped(0.5, 1.0);
  RK4Integration rk4;

  StateVector state({1.0, 0.0});

  double time = 0.0, dt = 0.01;
  int steps = 3000;

  std::string filename = "../output/damped_oscillator_rk4.csv";
  std::ofstream ofs(filename);
  if (!ofs.is_open()) {
    std::cerr << "Error opening file " << filename << std::endl;
    return;
  }

  ofs << "time,x,v\n";
  for (int i = 0; i <= steps; i++) {
    ofs << time << "," << state[0] << "," << state[1] << "\n";
    
    state = rk4.Integrate(damped, state, time, dt);
    time += dt;
  }

}

void SimulateForcedOscillatorEuler() {
  SineSignal sine_input(1.0, 1.0);
  ForcedOscillator forced(0.3, 1.0, sine_input);
  EulerIntegration euler;

  StateVector state({0.0, 0.0});

  double time = 0.0;
  double dt = 0.01;
  int steps = 5000;

  std::string filename = "../output/forced_oscillator_euler.csv";
  std::ofstream ofs(filename);
  if (!ofs.is_open()) {
    std::cerr << "Error opening file " << filename << std::endl;
    return;
  }

  ofs << "time,x,v\n";
  for (int i = 0; i <= steps; i++) {
    ofs << time << "," << state[0] << "," << state[1] << "\n";

    state = euler.Integrate(forced, state, time, dt);
    time += dt;
  }
}

void SimulateForcedOscillatorRK4() {
  SineSignal sine_input(1.0, 1.0);
  ForcedOscillator forced(0.3, 1.0, sine_input);
  RK4Integration rk4;

  StateVector state({0.0, 0.0});

  double time = 0.0;
  double dt = 0.01;
  int steps = 5000;

  std::string filename = "../output/forced_oscillator_rk4.csv";
  std::ofstream ofs(filename);
  if (!ofs.is_open()) {
    std::cerr << "Error opening file " << filename << std::endl;
    return;
  }

  ofs << "time,x,v\n";
  for (int i = 0; i <= steps; i++) {
    ofs << time << "," << state[0] << "," << state[1] << "\n";

    state = rk4.Integrate(forced, state, time, dt);
    time += dt;
  } 
}

void SimulateStepResponseEuler() {
  StepSignal step_input(1.0, 0.0);
  ForcedOscillator forced(0.3, 1.0, step_input);

  EulerIntegration euler;

  StateVector state({0.0, 0.0});

  double time = 0.0;
  double dt = 0.01;
  int steps = 5000;

  std::string filename = "../output/step_response_euler.csv";
  std::ofstream ofs(filename);
  if (!ofs.is_open()) {
    std::cerr << "Error opening file " << filename << std::endl;
    return;
  }

  ofs << "time,x,v\n";
  for (int i = 0; i <= steps; i++) {
    ofs << time << "," << state[0] << "," << state[1] << "\n";

    state = euler.Integrate(forced, state, time, dt);
    time += dt;
  }  
}

void SimulateStepResponseRK4() {
  StepSignal step_input(1.0, 0.0);
  ForcedOscillator forced(0.3, 1.0, step_input); 

  RK4Integration rk4;

 StateVector state({0.0, 0.0});

  double time = 0.0;
  double dt = 0.01;
  int steps = 5000; 

  std::string filename = "../output/step_response_rk4.csv";
  std::ofstream ofs(filename);
  if (!ofs.is_open()) {
    std::cerr << "Error opening file " << filename << std::endl;
    return;
  }

  ofs << "time,x,v\n";
  for (int i = 0; i <= steps; i++) {
    ofs << time << "," << state[0] << "," << state[1] << "\n";

    state = rk4.Integrate(forced, state, time, dt);
    time += dt;
  } 

}

void SimulateConstantResponseEuler() {
  ConstantSignal constant_input(1.0);
  ForcedOscillator forced(0.3, 1.0, constant_input);

  EulerIntegration euler;

  StateVector state({0.0, 0.0});

  double time = 0.0;
  double dt = 0.01;
  int steps = 5000;

  std::string filename = "../output/constant_response_euler.csv";
  std::ofstream ofs(filename);
  if (!ofs.is_open()) {
    std::cerr << "Error opening file " << filename << std::endl;
    return;
  }

  ofs << "time,x,v\n";
  for (int i = 0; i <= steps; i++) {
    ofs << time << "," << state[0] << "," << state[1] << "\n";

    state = euler.Integrate(forced, state, time, dt);
    time += dt;
  }
}

void SimulateConstantResponseRK4() {
  ConstantSignal constant_input(1.0);
  ForcedOscillator forced(0.3, 1.0, constant_input);

  RK4Integration rk4;

  StateVector state({0.0, 0.0});

  double time = 0.0;
  double dt = 0.01;
  int steps = 5000;

  std::string filename = "../output/constant_response_rk4.csv";
  std::ofstream ofs(filename);
  if (!ofs.is_open()) {
    std::cerr << "Error opening file " << filename << std::endl;
    return;
  }

  ofs << "time,x,v\n";
  for (int i = 0; i <= steps; i++) {
    ofs << time << "," << state[0] << "," << state[1] << "\n";

    state = rk4.Integrate(forced, state, time, dt);
    time += dt;
  }
}

void SimulateRampResponseEuler() {
  RampSignal ramp_input(1.0, 0.0);
  ForcedOscillator forced(0.3, 1.0, ramp_input);

  EulerIntegration euler;

  StateVector state({0.0, 0.0});

  double time = 0.0;
  double dt = 0.01;
  int steps = 5000;

  std::string filename = "../output/ramp_response_euler.csv";
  std::ofstream ofs(filename);
  if (!ofs.is_open()) {
    std::cerr << "Error opening file " << filename << std::endl;
    return;
  }

  ofs << "time,x,v\n";
  for (int i = 0; i <= steps; i++) {
    ofs << time << "," << state[0] << "," << state[1] << "\n";

    state = euler.Integrate(forced, state, time, dt);
    time += dt;
  }
}

void SimulateRampResponseRK4() {
  RampSignal ramp_input(1.0, 0.0);
  ForcedOscillator forced(0.3, 1.0, ramp_input);

  RK4Integration rk4;

  StateVector state({0.0, 0.0});

  double time = 0.0;
  double dt = 0.01;
  int steps = 5000;

  std::string filename = "../output/ramp_response_rk4.csv";
  std::ofstream ofs(filename);
  if (!ofs.is_open()) {
    std::cerr << "Error opening file " << filename << std::endl;
    return;
  }

  ofs << "time,x,v\n";
  for (int i = 0; i <= steps; i++) {
    ofs << time << "," << state[0] << "," << state[1] << "\n";

    state = rk4.Integrate(forced, state, time, dt);
    time += dt;
  }
}

void SimulatePulseResponseEuler() {
  ImpulseSignal pulse_input(1.0, 5.0, 10.0);
  ForcedOscillator forced(0.3, 1.0, pulse_input);

  EulerIntegration euler;

  StateVector state({0.0, 0.0});

  double time = 0.0;
  double dt = 0.01;
  int steps = 5000;

  std::string filename = "../output/pulse_response_euler.csv";
  std::ofstream ofs(filename);
  if (!ofs.is_open()) {
    std::cerr << "Error opening file " << filename << std::endl;
    return;
  }

  ofs << "time,x,v\n";
  for (int i = 0; i <= steps; i++) {
    ofs << time << "," << state[0] << "," << state[1] << "\n";

    state = euler.Integrate(forced, state, time, dt);
    time += dt;
  }
}

void SimulatePulseResponseRK4() {
  ImpulseSignal pulse_input(1.0, 5.0, 10.0);
  ForcedOscillator forced(0.3, 1.0, pulse_input);

  RK4Integration rk4;

  StateVector state({0.0, 0.0});

  double time = 0.0;
  double dt = 0.01;
  int steps = 5000;

  std::string filename = "../output/pulse_response_rk4.csv";
  std::ofstream ofs(filename);
  if (!ofs.is_open()) {
    std::cerr << "Error opening file " << filename << std::endl;
    return;
  }

  ofs << "time,x,v\n";
  for (int i = 0; i <= steps; i++) {
    ofs << time << "," << state[0] << "," << state[1] << "\n";

    state = rk4.Integrate(forced, state, time, dt);
    time += dt;
  }
}

void SimulateRLCStepResponseEuler() {
  StepSignal step_input(1.0, 0.0);
  RLCCircuit rlc(0.3, 1.0, 1.0, step_input);

  EulerIntegration euler;

  StateVector state({0.0, 0.0});

  double time = 0.0;
  double dt = 0.01;
  int steps = 5000;

  std::string filename = "../output/rlc_step_response_euler.csv";
  std::ofstream ofs(filename);
  if (!ofs.is_open()) {
    std::cerr << "Error opening file " << filename << std::endl;
    return;
  }

  ofs << "time,q,i\n";
  for (int k = 0; k <= steps; k++) {
    ofs << time << "," << state[0] << "," << state[1] << "\n";

    state = euler.Integrate(rlc, state, time, dt);
    time += dt;
  }
}

void SimulateRLCStepResponseRK4() {
  StepSignal step_input(1.0, 0.0);
  RLCCircuit rlc(0.3, 1.0, 1.0, step_input);

  RK4Integration rk4;

  StateVector state({0.0, 0.0});

  double time = 0.0;
  double dt = 0.01;
  int steps = 5000;

  std::string filename = "../output/rlc_step_response_rk4.csv";
  std::ofstream ofs(filename);
  if (!ofs.is_open()) {
    std::cerr << "Error opening file " << filename << std::endl;
    return;
  }

  ofs << "time,q,i\n";
  for (int k = 0; k <= steps; k++) {
    ofs << time << "," << state[0] << "," << state[1] << "\n";

    state = rk4.Integrate(rlc, state, time, dt);
    time += dt;
  }
}

void ExportPoleZeroData() {
  // Test 1 (simple case)
  TransferFunction g({1, 1}, {1, 5, 4});

  std::vector<std::complex<double>> zeros = g.GetZeros();
  std::cout << "Zero:\n";
  for (const auto& zero : zeros) {
    std::cout << zero << std::endl;
  }
  std::cout << std::endl;

  std::vector<std::complex<double>> poles = g.GetPoles();
  std::cout << "Pole:\n";
  for (const auto& pole : poles) {
    std::cout << pole << std::endl;
  }
  std::cout << std::endl;


  // Test 2: (Complex)
  TransferFunction g_2({1}, {1, 2, 5});
  
  std::vector<std::complex<double>> comp_zeros = g_2.GetZeros();
  std::cout << "Zero:\n";
  for (const auto& zero : comp_zeros) {
    std::cout << zero << std::endl;
  }
  std::cout << std::endl; 
  
  std::vector<std::complex<double>> comp_poles = g_2.GetPoles();
  std::cout << "Pole:\n";
  for (const auto& pole : comp_poles) {
    std::cout << pole << std::endl;
  }
  std::cout << std::endl;

  std::string filename_1 = "../output/simple_pole_zero_data.csv";
  std::ofstream ofs_1(filename_1);
  if(!ofs_1.is_open()) {
    std::cerr << "Error opening " << filename_1 << std::endl;
    return;
  }

  ofs_1 << "type,real,imaginary\n";

  for (const auto& zero : zeros) {
    ofs_1 << "zero," << zero.real() << "," << zero.imag() << "\n";
  }

  for (const auto& pole : poles) {
    ofs_1 << "pole," << pole.real() << "," << pole.imag() << "\n";
  }

  ofs_1.close();

  std::string filename_2 = "../output/complex_pole_zero_data.csv";
  std::ofstream ofs_2(filename_2);
  if (!ofs_2.is_open()) {
    std::cerr << "Error opening " << filename_2 << std::endl;
    return;
  }

  ofs_2 << "type,real,imaginary\n";

  for (const auto& zero : comp_zeros) {
    ofs_2 << "zero," << zero.real() << "," << zero.imag() << "\n";
  }
  for (const auto& pole : comp_poles) {
    ofs_2 << "pole," << pole.real() << "," << pole.imag() << "\n";
  }
  ofs_2.close();
}

void ExportFrequencyResponseData() {
  // Create the transfer function to analyze
  TransferFunction transfer_function({1}, {1, 1});

  // Generate a frequency sweep
  std::vector<double> frequencies = FrequencyResponse::GenerateFrequencySweep(0.0, 20.0, 500);

  // Build the FrequencyResponse object
  FrequencyResponse frequency_response(transfer_function, frequencies);

  // Get:
  // frequencies
  // complex responses
  // magnitudes
  // phases
  const std::vector<double>& stored_frequencies = frequency_response.GetFrequencies();
  const std::vector<std::complex<double>>& responses = frequency_response.GetResponses();
  const std::vector<double>& magnitudes = frequency_response.GetMagnitudes();
  const std::vector<double>& phases = frequency_response.GetPhases();

  // Open a CSV file
  std::ofstream output_file("../output/frequency_response.csv");

  if (!output_file.is_open())
    throw std::runtime_error("Could not open frequency response output file.");

  // Write the header:
  // frequency,real,imaginary,magnitude,phase
  output_file << "frequency,real,imaginary,magnitude,phase" << std::endl;

  // Loop through every frequency-response sample:
  //   write frequency
  //   write response real part
  //   write response imaginary part
  //   write magnitude
  //   write phase
  for (size_t i = 0; i < stored_frequencies.size(); i++) {
    output_file << stored_frequencies[i] << "," << responses[i].real() << "," << responses[i].imag() << "," << magnitudes[i] << "," << phases[i] << std::endl;
  }

  // Close the file
  output_file.close();

  std::cout << "Frequency response data exported successfully." << std::endl;
}

void ExportNyquistData() {
  // Create G(s) = 1 / (s + 1)
  TransferFunction transfer_function({1}, {1, 1});

  // Create the Nyquist analysis
  NyquistAnalysis nyquist_analysis(transfer_function);

  // Generate and map the Nyquist path
  nyquist_analysis.GenerateNyquistPath(100.0, 500);
  nyquist_analysis.MapNyquistPath();

  // Get the original and mapped paths
  const std::vector<std::complex<double>>& s_path =
      nyquist_analysis.GetSPath();

  const std::vector<std::complex<double>>& mapped_path =
      nyquist_analysis.GetMappedPath();

  // Open the CSV file
  std::ofstream output_file("../output/nyquist_data.csv");

  if (!output_file.is_open())
    throw std::runtime_error("Could not open Nyquist output file.");

  // Write the CSV header
  output_file
      << "s_real,s_imaginary,mapped_real,mapped_imaginary"
      << std::endl;

  // Write each point and its mapped value
  for (size_t i = 0; i < s_path.size(); i++) {
    output_file
        << s_path[i].real() << ","
        << s_path[i].imag() << ","
        << mapped_path[i].real() << ","
        << mapped_path[i].imag()
        << std::endl;
  }

  output_file.close();

  std::cout << "Nyquist data exported successfully."
            << std::endl;
}

void TestPhaseCrossoverFrequency() {
  std::cout << "======================================" << std::endl;
  std::cout << "Testing Phase Crossover Frequency" << std::endl;
  std::cout << "======================================" << std::endl;

  // --------------------------------------------------
  // Test 1:
  //
  // G(s) = 1 / [(s + 1)(s + 2)(s + 3)]
  //
  // Denominator at s = jw:
  //
  // (jw + 1)(jw + 2)(jw + 3)
  //
  // Imaginary part becomes zero when:
  //
  // w(11 - w^2) = 0
  //
  // Ignoring w = 0:
  //
  // w_pc = sqrt(11)
  //      ≈ 3.31662 rad/s
  //
  // At this frequency, the denominator lies on the
  // negative real axis, so G(jw) has phase -180 deg.
  // --------------------------------------------------

  std::cout << "Test 1 - Type 0 system" << std::endl;

  TransferFunction transfer_function_1(
      {1},
      {1, 6, 11, 6});

  NyquistAnalysis nyquist_1(transfer_function_1);

  double expected_omega_1 = std::sqrt(11.0);

  double actual_omega_1 =
      nyquist_1.GetPhaseCrossoverFrequency(
          10.0,
          10001);

  std::cout << "Expected phase crossover frequency: "
            << expected_omega_1
            << std::endl;

  std::cout << "Actual phase crossover frequency:   "
            << actual_omega_1
            << std::endl;

  std::cout << std::endl;


  // --------------------------------------------------
  // Test 2:
  //
  // G(s) = 1 / [s(s + 1)(s + 2)]
  //
  // This is a Type 1 system.
  //
  // The function must NOT evaluate exactly at w = 0.
  //
  // At s = jw, the denominator has imaginary part:
  //
  // w(2 - w^2)
  //
  // Therefore:
  //
  // w_pc = sqrt(2)
  //      ≈ 1.41421 rad/s
  // --------------------------------------------------

  std::cout << "Test 2 - Type 1 system" << std::endl;

  TransferFunction transfer_function_2(
      {1},
      {1, 3, 2, 0});

  NyquistAnalysis nyquist_2(transfer_function_2);

  double expected_omega_2 = std::sqrt(2.0);

  double actual_omega_2 =
      nyquist_2.GetPhaseCrossoverFrequency(
          10.0,
          10001);

  std::cout << "Expected phase crossover frequency: "
            << expected_omega_2
            << std::endl;

  std::cout << "Actual phase crossover frequency:   "
            << actual_omega_2
            << std::endl;

  std::cout << std::endl;


  // --------------------------------------------------
  // Test 3:
  //
  // G(s) = 1 / (s + 1)
  //
  // Its phase approaches -90 degrees, so it never
  // reaches -180 degrees.
  //
  // Therefore no phase crossover frequency exists.
  // --------------------------------------------------

  std::cout << "Test 3 - No phase crossover" << std::endl;

  try {
    TransferFunction transfer_function_3(
        {1},
        {1, 1});

    NyquistAnalysis nyquist_3(transfer_function_3);

    nyquist_3.GetPhaseCrossoverFrequency(
        100.0,
        10001);

    std::cout << "FAILED - exception expected."
              << std::endl;
  }
  catch (const std::runtime_error& error) {
    std::cout << "PASSED - caught expected exception: "
              << error.what()
              << std::endl;
  }

  std::cout << std::endl;


  // --------------------------------------------------
  // Test 4:
  // Invalid maximum frequency
  // --------------------------------------------------

  std::cout << "Test 4 - Invalid maximum frequency" << std::endl;

  try {
    NyquistAnalysis nyquist_4(transfer_function_1);

    nyquist_4.GetPhaseCrossoverFrequency(
        0.0,
        100);

    std::cout << "FAILED - exception expected."
              << std::endl;
  }
  catch (const std::invalid_argument& error) {
    std::cout << "PASSED - caught expected exception: "
              << error.what()
              << std::endl;
  }

  std::cout << std::endl;


  // --------------------------------------------------
  // Test 5:
  // Too few frequency samples
  // --------------------------------------------------

  std::cout << "Test 5 - Too few samples" << std::endl;

  try {
    NyquistAnalysis nyquist_5(transfer_function_1);

    nyquist_5.GetPhaseCrossoverFrequency(
        10.0,
        2);

    std::cout << "FAILED - exception expected."
              << std::endl;
  }
  catch (const std::invalid_argument& error) {
    std::cout << "PASSED - caught expected exception: "
              << error.what()
              << std::endl;
  }

  std::cout << std::endl;
}

void TestGainMargin() {
  std::cout << "======================================" << std::endl;
  std::cout << "Testing Gain Margin" << std::endl;
  std::cout << "======================================" << std::endl;

  // --------------------------------------------------
  // Test 1:
  //
  // G(s) = 1 / [(s + 1)(s + 2)(s + 3)]
  //
  // omega_pc = sqrt(11)
  //
  // |G(j omega_pc)| = 1 / 60
  //
  // Therefore:
  // GM = 60
  // --------------------------------------------------

  std::cout << "Test 1 - Type 0 system" << std::endl;

  TransferFunction transfer_function_1(
      {1},
      {1, 6, 11, 6});

  NyquistAnalysis nyquist_1(transfer_function_1);

  double expected_gain_margin_1 = 60.0;

  double actual_gain_margin_1 =
      nyquist_1.GetGainMargin(
          10.0,
          10001);

  std::cout << "Expected gain margin: "
            << expected_gain_margin_1
            << std::endl;

  std::cout << "Actual gain margin:   "
            << actual_gain_margin_1
            << std::endl;

  std::cout << std::endl;


  // --------------------------------------------------
  // Test 2:
  //
  // G(s) = 1 / [s(s + 1)(s + 2)]
  //
  // omega_pc = sqrt(2)
  //
  // |G(j omega_pc)| = 1 / 6
  //
  // Therefore:
  // GM = 6
  // --------------------------------------------------

  std::cout << "Test 2 - Type 1 system" << std::endl;

  TransferFunction transfer_function_2(
      {1},
      {1, 3, 2, 0});

  NyquistAnalysis nyquist_2(transfer_function_2);

  double expected_gain_margin_2 = 6.0;

  double actual_gain_margin_2 =
      nyquist_2.GetGainMargin(
          10.0,
          10001);

  std::cout << "Expected gain margin: "
            << expected_gain_margin_2
            << std::endl;

  std::cout << "Actual gain margin:   "
            << actual_gain_margin_2
            << std::endl;

  std::cout << std::endl;


  // --------------------------------------------------
  // Test 3:
  //
  // G(s) = 1 / (s + 1)
  //
  // There is no finite phase crossover frequency,
  // so GetGainMargin() should propagate the exception
  // from GetPhaseCrossoverFrequency().
  // --------------------------------------------------

  std::cout << "Test 3 - No phase crossover" << std::endl;

  try {
    TransferFunction transfer_function_3(
        {1},
        {1, 1});

    NyquistAnalysis nyquist_3(transfer_function_3);

    nyquist_3.GetGainMargin(
        100.0,
        10001);

    std::cout << "FAILED - exception expected."
              << std::endl;
  }
  catch (const std::runtime_error& error) {
    std::cout << "PASSED - caught expected exception: "
              << error.what()
              << std::endl;
  }

  std::cout << std::endl;


  // --------------------------------------------------
  // Test 4:
  // Invalid maximum frequency
  // --------------------------------------------------

  std::cout << "Test 4 - Invalid maximum frequency"
            << std::endl;

  try {
    NyquistAnalysis nyquist_4(transfer_function_1);

    nyquist_4.GetGainMargin(
        0.0,
        100);

    std::cout << "FAILED - exception expected."
              << std::endl;
  }
  catch (const std::invalid_argument& error) {
    std::cout << "PASSED - caught expected exception: "
              << error.what()
              << std::endl;
  }

  std::cout << std::endl;


  // --------------------------------------------------
  // Test 5:
  // Too few samples
  // --------------------------------------------------

  std::cout << "Test 5 - Too few samples" << std::endl;

  try {
    NyquistAnalysis nyquist_5(transfer_function_1);

    nyquist_5.GetGainMargin(
        10.0,
        2);

    std::cout << "FAILED - exception expected."
              << std::endl;
  }
  catch (const std::invalid_argument& error) {
    std::cout << "PASSED - caught expected exception: "
              << error.what()
              << std::endl;
  }

  std::cout << std::endl;
}

int main() {
  TestGainMargin();

  return 0;
}