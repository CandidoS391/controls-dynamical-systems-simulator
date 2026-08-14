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


void TestFrequencyResponse() {
  std::cout << "======================================" << std::endl;
  std::cout << "Testing Frequency Response" << std::endl;
  std::cout << "======================================" << std::endl;

  // ----------------------------------------------------------
  // Test 1
  //
  // G(s) = 1 / (s + 1)
  //
  // Frequencies:
  // omega = 0, 1, 2
  //
  // At omega = 0:
  // G(j0) = 1
  // Magnitude = 1
  // Phase = 0
  //
  // At omega = 1:
  // G(j) = 1 / (1 + j)
  //      = 0.5 - 0.5j
  //
  // Magnitude = sqrt(0.5)
  // Phase = -pi / 4
  //
  // At omega = 2:
  // G(2j) = 1 / (1 + 2j)
  //       = 0.2 - 0.4j
  //
  // Magnitude = 1 / sqrt(5)
  // Phase = -atan(2)
  // ----------------------------------------------------------

  TransferFunction transfer_function({1}, {1, 1});

  std::vector<double> frequencies = {
      0.0, 1.0, 2.0};

  FrequencyResponse frequency_response(
      transfer_function,
      frequencies);

  std::vector<std::complex<double>> responses =
      frequency_response.GetResponses();

  std::vector<double> magnitudes =
      frequency_response.GetMagnitudes();

  std::vector<double> phases =
      frequency_response.GetPhases();

  std::cout << "Test 1 - G(s) = 1/(s + 1)" << std::endl;

  std::cout << std::endl;
  std::cout << "omega = 0" << std::endl;
  std::cout << "Expected response:  (1,0)" << std::endl;
  std::cout << "Actual response:    "
            << responses[0] << std::endl;

  std::cout << "Expected magnitude: 1" << std::endl;
  std::cout << "Actual magnitude:   "
            << magnitudes[0] << std::endl;

  std::cout << "Expected phase:     0" << std::endl;
  std::cout << "Actual phase:       "
            << phases[0] << std::endl;


  std::cout << std::endl;
  std::cout << "omega = 1" << std::endl;
  std::cout << "Expected response:  (0.5,-0.5)" << std::endl;
  std::cout << "Actual response:    "
            << responses[1] << std::endl;

  std::cout << "Expected magnitude: "
            << std::sqrt(0.5) << std::endl;
  std::cout << "Actual magnitude:   "
            << magnitudes[1] << std::endl;

  std::cout << "Expected phase:     "
            << -std::atan(1.0) << std::endl;
  std::cout << "Actual phase:       "
            << phases[1] << std::endl;


  std::cout << std::endl;
  std::cout << "omega = 2" << std::endl;
  std::cout << "Expected response:  (0.2,-0.4)" << std::endl;
  std::cout << "Actual response:    "
            << responses[2] << std::endl;

  std::cout << "Expected magnitude: "
            << 1.0 / std::sqrt(5.0) << std::endl;
  std::cout << "Actual magnitude:   "
            << magnitudes[2] << std::endl;

  std::cout << "Expected phase:     "
            << -std::atan(2.0) << std::endl;
  std::cout << "Actual phase:       "
            << phases[2] << std::endl;

  std::cout << std::endl;


  // ----------------------------------------------------------
  // Test 2: Getter for frequencies
  // ----------------------------------------------------------

  std::cout << "Test 2 - Frequency Getter" << std::endl;

  const std::vector<double>& stored_frequencies =
      frequency_response.GetFrequencies();

  std::cout << "Expected frequencies: 0 1 2" << std::endl;
  std::cout << "Actual frequencies:   ";

  for (const auto& omega : stored_frequencies)
    std::cout << omega << " ";

  std::cout << std::endl;
  std::cout << std::endl;


  // ----------------------------------------------------------
  // Test 3: Negative frequency
  // ----------------------------------------------------------

  try {
    FrequencyResponse invalid_response(
        transfer_function,
        {0.0, 1.0, -2.0});

    std::cout << "Test 3: FAILED - exception expected"
              << std::endl;
  }
  catch (const std::invalid_argument& exception) {
    std::cout << "Test 3: PASSED - caught expected exception: "
              << exception.what()
              << std::endl;
  }

  std::cout << std::endl;


  // ----------------------------------------------------------
  // Test 4: Empty frequency vector
  // ----------------------------------------------------------

  try {
    FrequencyResponse empty_response(
        transfer_function,
        {});

    std::cout << "Test 4: FAILED - exception expected"
              << std::endl;
  }
  catch (const std::invalid_argument& exception) {
    std::cout << "Test 4: PASSED - caught expected exception: "
              << exception.what()
              << std::endl;
  }
}

void TestFrequencySweep() {
  std::cout << "======================================" << std::endl;
  std::cout << "Testing Frequency Sweep" << std::endl;
  std::cout << "======================================" << std::endl;

  // Test 1: Basic frequency sweep
  std::vector<double> frequencies =
      FrequencyResponse::GenerateFrequencySweep(0.0, 10.0, 6);

  std::cout << "Test 1" << std::endl;
  std::cout << "Expected: 0 2 4 6 8 10" << std::endl;
  std::cout << "Actual:   ";

  for (const auto& frequency : frequencies)
    std::cout << frequency << " ";

  std::cout << std::endl;
  std::cout << std::endl;

  // Test 2: Negative starting frequency
  try {
    FrequencyResponse::GenerateFrequencySweep(-1.0, 10.0, 6);

    std::cout << "Test 2: FAILED - exception expected"
              << std::endl;
  }
  catch (const std::invalid_argument& exception) {
    std::cout << "Test 2: PASSED - caught expected exception: "
              << exception.what()
              << std::endl;
  }

  std::cout << std::endl;

  // Test 3: End frequency less than start frequency
  try {
    FrequencyResponse::GenerateFrequencySweep(10.0, 5.0, 6);

    std::cout << "Test 3: FAILED - exception expected"
              << std::endl;
  }
  catch (const std::invalid_argument& exception) {
    std::cout << "Test 3: PASSED - caught expected exception: "
              << exception.what()
              << std::endl;
  }

  std::cout << std::endl;

  // Test 4: Too few samples
  try {
    FrequencyResponse::GenerateFrequencySweep(0.0, 10.0, 1);

    std::cout << "Test 4: FAILED - exception expected"
              << std::endl;
  }
  catch (const std::invalid_argument& exception) {
    std::cout << "Test 4: PASSED - caught expected exception: "
              << exception.what()
              << std::endl;
  }
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

int main() {
  ExportFrequencyResponseData();

  return 0;
}