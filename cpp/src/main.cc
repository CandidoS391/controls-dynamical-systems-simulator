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

void TestBlockDiagramAlgebra() {
  TransferFunction g1({1}, {1, 1});
  TransferFunction g2({2}, {1, 2});

  TransferFunction series = g1.Series(g2);
  series.Print();

  TransferFunction parallel = g1.Parallel(g2);
  parallel.Print();
  
  TransferFunction feedback = series.Feedback();
  feedback.Print();
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

void TestStability() {
  // Test 1: Stable Real Transfer Function
  TransferFunction stable({1}, {1, 1});

  std::cout << stable << std::endl;
  stable.PrintStability();
  std::cout << std::endl;

    // Test 2: Unstable Real Transfer Function
  TransferFunction unstable({1}, {1, -2});

  std::cout << unstable << std::endl;
  unstable.PrintStability();
  std::cout << std::endl;

  // Test 3: Stable Complex Transfer Function
  TransferFunction stable_complex({1}, {1, 2, 5});

  std::cout << stable_complex << std::endl;
  stable_complex.PrintStability();
  std::cout << std::endl;

  // Test 4: Imaginary Axis Poles
  TransferFunction unstable_complex({1}, {1, 0, 1});

  std::cout << unstable_complex << std::endl;
  unstable_complex.PrintStability();
  std::cout << std::endl;
}

void TestHigherOrderRoots() {
  // Test 1: Three real roots
  // s^3 + 6s^2 + 11s + 6 = (s + 1)(s + 2)(s + 3)
  TransferFunction real_roots({1}, {1, 6, 11, 6});

  std::cout << "Cubic with real roots:\n";
  for (const auto& pole : real_roots.GetPoles())
    std::cout << pole << std::endl;

  std::cout << std::endl;

  // Test 2: One real root and one complex-conjugate pair
  // s^3 + 1
  TransferFunction mixed_roots({1}, {1, 0, 0, 1});

  std::cout << "Cubic with complex roots:\n";
  for (const auto& pole : mixed_roots.GetPoles())
    std::cout << pole << std::endl;

  std::cout << std::endl;

  // Test 3: Fourth-order polynomial
  // (s + 1)(s + 2)(s + 3)(s + 4)
  TransferFunction fourth_order({1}, {1, 10, 35, 50, 24});

  std::cout << "Fourth-order roots:\n";
  for (const auto& pole : fourth_order.GetPoles())
    std::cout << pole << std::endl;

  std::cout << std::endl;
}



void TestFeedbackSystemBasicFunctions() {
  // ============================================================
  // TESTING FEEDBACK SYSTEM
  // ============================================================

  // G(s) = 2 / (s + 2)
  TransferFunction forward_path({2}, {1, 2});

  // H(s) = 1
  TransferFunction feedback_path({1}, {1});

  // Td(s) = 1
  TransferFunction desired_transfer({1}, {1});

  FeedbackSystem feedback_system(forward_path,
                                feedback_path,
                                desired_transfer);

  // ------------------------------------------------------------
  // Test 1: Loop Transfer Function
  // Expected:
  //      G(s)H(s)
  //    = 2 / (s + 2)
  // ------------------------------------------------------------
  std::cout << "TESTING LOOP TRANSFER FUNCTION" << std::endl;
  std::cout << feedback_system.GetLoopTransferFunction() << std::endl;
  std::cout << std::endl;


  // ------------------------------------------------------------
  // Test 2: Closed Loop Transfer Function
  // Expected:
  //
  //          2
  // ----------------
  // (s + 2) + 2
  //
  //      2
  // = --------
  //    s + 4
  // ------------------------------------------------------------
  std::cout << "TESTING CLOSED LOOP TRANSFER FUNCTION" << std::endl;
  std::cout << feedback_system.GetClosedLoopTransferFunction() << std::endl;
  std::cout << std::endl;
  // ------------------------------------------------------------
  // Test 3: Transfer Error
  //
  // Td(s) = 1
  //
  // Expected:
  //
  //      1 - 2/(s+4)
  //
  //      (s+4)-2
  // = -------------
  //       s+4
  //
  //      s+2
  // = --------
  //      s+4
  // ------------------------------------------------------------
  std::cout << "TESTING TRANSFER ERROR" << std::endl;
  std::cout << feedback_system.GetTransferError() << std::endl;
  std::cout << std::endl;
}

void TestErrorConstants() {
  std::cout << "======================================" << std::endl;
  std::cout << "Testing Error Constants" << std::endl;
  std::cout << "======================================" << std::endl;

  // ------------------------------------------------------------
  // Test 1
  // G(s) = s / (s + 1)
  // H(s) = 1
  // Desired = 1
  //
  // Transfer Error = s / (s + 1)
  //
  // Ks  = infinity
  // Kr  = 1
  // Kpa = 0
  // ------------------------------------------------------------

  FeedbackSystem system_1(
      TransferFunction({0}, {1}),
      TransferFunction({1}, {1}),
      TransferFunction({1, 0}, {1, 1}));

  std::cout << "Test 1" << std::endl;
  std::cout << "Expected Ks: inf" << std::endl;
  std::cout << "Actual Ks:   "
            << system_1.GetStepErrorConstant()
            << std::endl;

  std::cout << "Expected Kr: 1" << std::endl;
  std::cout << "Actual Kr:   "
            << system_1.GetRampErrorConstant()
            << std::endl;

  std::cout << "Expected Kpa: 0" << std::endl;
  std::cout << "Actual Kpa:   "
            << system_1.GetParabolicErrorConstant()
            << std::endl;

  std::cout << std::endl;


  // ------------------------------------------------------------
  // Test 2
  // Zero transfer error
  //
  // Desired = Closed-loop
  //
  // Transfer Error = 0
  //
  // Ks  = inf
  // Kr  = inf
  // Kpa = inf
  // ------------------------------------------------------------


  FeedbackSystem system_2(
      TransferFunction({1}, {1}),
      TransferFunction({1}, {1}),
      TransferFunction({1}, {2}));

  std::cout << "Test 2 - Zero Transfer Error" << std::endl;

  std::cout << "Expected Ks: inf" << std::endl;
  std::cout << "Actual Ks:   "
            << system_2.GetStepErrorConstant()
            << std::endl;

  std::cout << "Expected Kr: inf" << std::endl;
  std::cout << "Actual Kr:   "
            << system_2.GetRampErrorConstant()
            << std::endl;

  std::cout << "Expected Kpa: inf" << std::endl;
  std::cout << "Actual Kpa:   "
            << system_2.GetParabolicErrorConstant()
            << std::endl;

  std::cout << std::endl;


  // ------------------------------------------------------------
  // Test 3
  // Transfer Error = 1 / (s + 1)
  //
  // Ks  = 1
  // Kr  = 0
  // Kpa = 0
  // ------------------------------------------------------------

  FeedbackSystem system_3(
      TransferFunction({0}, {1}),
      TransferFunction({1}, {1}),
      TransferFunction({1}, {1}));

  std::cout << "Test 3" << std::endl;

  std::cout << "Expected Ks: 1" << std::endl;
  std::cout << "Actual Ks:   "
            << system_3.GetStepErrorConstant()
            << std::endl;

  std::cout << "Expected Kr: 0" << std::endl;
  std::cout << "Actual Kr:   "
            << system_3.GetRampErrorConstant()
            << std::endl;

  std::cout << "Expected Kpa: 0" << std::endl;
  std::cout << "Actual Kpa:   "
            << system_3.GetParabolicErrorConstant()
            << std::endl;
}

void TestSensitivityAnalysis() {
  std::cout << "======================================" << std::endl;
  std::cout << "Testing Sensitivity Analysis" << std::endl;
  std::cout << "======================================" << std::endl;

  // ----------------------------------------------------------
  // Test 1
  //
  // A1 = 1
  // A2 = 1
  // A3 = s + 1
  // A4 = 0
  // k  = 2
  //
  // Nominal:
  // T(s) = (1 + 2)/(s + 1) = 3/(s + 1)
  //
  // Sensitivity:
  // S(s) = 2(s + 1) / 3(s + 1) = 2/3
  //
  // The TransferFunction may print the unsimplified result:
  // (2s + 2)/(3s + 3)
  // ----------------------------------------------------------
  SensitivityAnalysis analysis_1(
      {1},
      {1},
      {1, 1},
      {0},
      2.0);

  std::cout << "Test 1" << std::endl;
  std::cout << "Expected nominal: 3 / (s + 1)" << std::endl;
  std::cout << "Actual nominal:   "
            << analysis_1.GetNominalTransferFunction()
            << std::endl;

  std::cout << "Expected sensitivity: 2/3" << std::endl;
  std::cout << "Actual sensitivity:   "
            << analysis_1.GetTransferFunctionSensitivity()
            << std::endl;

  std::cout << std::endl;


  // ----------------------------------------------------------
  // Test 2
  //
  // A1 = s + 1
  // A2 = 0
  // A3 = s + 2
  // A4 = 0
  // k  = 5
  //
  // T does not depend on k.
  //
  // Nominal:
  // T(s) = (s + 1)/(s + 2)
  //
  // Sensitivity:
  // S(s) = 0
  // ----------------------------------------------------------
  SensitivityAnalysis analysis_2(
      {1, 1},
      {0},
      {1, 2},
      {0},
      5.0);

  std::cout << "Test 2 - Zero Sensitivity" << std::endl;
  std::cout << "Expected nominal: (s + 1)/(s + 2)" << std::endl;
  std::cout << "Actual nominal:   "
            << analysis_2.GetNominalTransferFunction()
            << std::endl;

  std::cout << "Expected sensitivity: 0" << std::endl;
  std::cout << "Actual sensitivity:   "
            << analysis_2.GetTransferFunctionSensitivity()
            << std::endl;

  std::cout << std::endl;


  // ----------------------------------------------------------
  // Test 3
  //
  // A1 = 1
  // A2 = 0
  // A3 = s
  // A4 = 1
  // k  = 2
  //
  // Nominal:
  // T(s) = 1/(s + 2)
  //
  // Sensitivity:
  // S(s) = -2/(s + 2)
  // ----------------------------------------------------------
  SensitivityAnalysis analysis_3(
      {1},
      {0},
      {1, 0},
      {1},
      2.0);

  std::cout << "Test 3 - Parameter in Denominator" << std::endl;
  std::cout << "Expected nominal: 1/(s + 2)" << std::endl;
  std::cout << "Actual nominal:   "
            << analysis_3.GetNominalTransferFunction()
            << std::endl;

  std::cout << "Expected sensitivity: -2/(s + 2)" << std::endl;
  std::cout << "Actual sensitivity:   "
            << analysis_3.GetTransferFunctionSensitivity()
            << std::endl;

  std::cout << std::endl;


  // ----------------------------------------------------------
  // Test 4: Invalid nominal denominator
  //
  // A3 + kA4 = -2 + 2(1) = 0
  // ----------------------------------------------------------
  try {
    SensitivityAnalysis analysis_4(
        {1},
        {0},
        {-2},
        {1},
        2.0);

    analysis_4.GetNominalTransferFunction();

    std::cout << "Test 4: FAILED - exception expected"
              << std::endl;
  } catch (const std::invalid_argument& exception) {
    std::cout << "Test 4: PASSED - caught expected exception: "
              << exception.what()
              << std::endl;
  }
}

void TestFeedbackSystemSensitivity() {
  std::cout << "======================================" << std::endl;
  std::cout << "Testing Feedback System Sensitivity" << std::endl;
  std::cout << "======================================" << std::endl;

  // Nominal forward path:
  // G(s) = 1 / (s + 1)
  TransferFunction forward_path({1}, {1, 1});

  // Nominal feedback path:
  // H(s) = 1
  TransferFunction feedback_path({1}, {1});

  TransferFunction desired_transfer({1}, {1});

  FeedbackSystem system(
      forward_path,
      feedback_path,
      desired_transfer);

  // G(s, k) = k / (s + 1)
  //
  // A1 = 0
  // A2 = 1
  // A3 = s + 1
  // A4 = 0
  // k  = 1
  //
  // Therefore S_k^G = 1
  SensitivityAnalysis forward_analysis(
      {0},
      {1},
      {1, 1},
      {0},
      1.0);

  // H(s, k) = k
  //
  // A1 = 0
  // A2 = 1
  // A3 = 1
  // A4 = 0
  // k  = 1
  //
  // Therefore S_k^H = 1
  SensitivityAnalysis feedback_analysis(
      {0},
      {1},
      {1},
      {0},
      1.0);

  // ----------------------------------------------------------
  // Loop transfer:
  //
  // GH = 1 / (s + 1)
  //
  // Forward-path sensitivity:
  //
  // S_G^T = 1 / (1 + GH)
  //       = (s + 1) / (s + 2)
  // ----------------------------------------------------------
  std::cout << "Forward-path sensitivity" << std::endl;
  std::cout << "Expected: (s + 1)/(s + 2)" << std::endl;
  std::cout << "Actual:   "
            << system.GetForwardPathSensitivity()
            << std::endl;
  std::cout << std::endl;

  // ----------------------------------------------------------
  // Feedback-path sensitivity:
  //
  // S_H^T = -GH / (1 + GH)
  //       = -1 / (s + 2)
  // ----------------------------------------------------------
  std::cout << "Feedback-path sensitivity" << std::endl;
  std::cout << "Expected: -1/(s + 2)" << std::endl;
  std::cout << "Actual:   "
            << system.GetFeedbackPathSensitivity()
            << std::endl;
  std::cout << std::endl;

  // Since S_k^G = 1:
  //
  // S_k^T through G
  // = S_G^T S_k^G
  // = (s + 1)/(s + 2)
  std::cout << "Forward-parameter sensitivity" << std::endl;
  std::cout << "Expected: (s + 1)/(s + 2)" << std::endl;
  std::cout << "Actual:   "
            << system.GetForwardParameterSensitivity(
                   forward_analysis)
            << std::endl;
  std::cout << std::endl;

  // Since S_k^H = 1:
  //
  // S_k^T through H
  // = S_H^T S_k^H
  // = -1/(s + 2)
  std::cout << "Feedback-parameter sensitivity" << std::endl;
  std::cout << "Expected: -1/(s + 2)" << std::endl;
  std::cout << "Actual:   "
            << system.GetFeedbackParameterSensitivity(
                   feedback_analysis)
            << std::endl;
  std::cout << std::endl;

  // Combined:
  //
  // (s + 1)/(s + 2) - 1/(s + 2)
  // = s/(s + 2)
  std::cout << "Combined parameter sensitivity" << std::endl;
  std::cout << "Expected: s/(s + 2)" << std::endl;
  std::cout << "Actual:   "
            << system.GetCombinedParameterSensitivity(
                   forward_analysis,
                   feedback_analysis)
            << std::endl;
}

void TestPerformanceAnalysis() {
  std::cout << "======================================" << std::endl;
  std::cout << "Testing Performance Analysis" << std::endl;
  std::cout << "======================================" << std::endl;

  // ----------------------------------------------------------
  // Test 1: Positive response with overshoot
  //
  // Steady-state value: 10
  // Maximum response:    12
  // Overshoot:           2
  // Percent overshoot:   20%
  //
  // 50% target: 5
  // First reached at t = 0.3
  //
  // 10% target: 1, first reached at t = 0.1
  // 90% target: 9, first reached at t = 0.4
  // Rise time: 0.4 - 0.1 = 0.3
  //
  // 5% settling band: [9.5, 10.5]
  // Last outside sample: t = 0.6
  // Settling begins at:  t = 0.7
  // ----------------------------------------------------------
  std::vector<double> time_1 = {
      0.0, 0.1, 0.2, 0.3, 0.4,
      0.5, 0.6, 0.7, 0.8, 0.9};

  std::vector<double> response_1 = {
      0.0, 1.2, 3.5, 5.4, 9.1,
      12.0, 10.8, 10.4, 9.8, 10.0};

  PerformanceAnalysis analysis_1(time_1, response_1);

  std::cout << "Test 1 - Positive Response" << std::endl;

  std::cout << "Expected steady-state value: 10" << std::endl;
  std::cout << "Actual steady-state value:   "
            << analysis_1.GetSteadyStateValue()
            << std::endl;

  std::cout << "Expected overshoot: 2" << std::endl;
  std::cout << "Actual overshoot:   "
            << analysis_1.GetOvershoot()
            << std::endl;

  std::cout << "Expected percent overshoot: 20" << std::endl;
  std::cout << "Actual percent overshoot:   "
            << analysis_1.GetPercentOvershoot()
            << std::endl;

  std::cout << "Expected delay time: 0.3" << std::endl;
  std::cout << "Actual delay time:   "
            << analysis_1.GetDelayTime()
            << std::endl;

  std::cout << "Expected rise time: 0.3" << std::endl;
  std::cout << "Actual rise time:   "
            << analysis_1.GetRiseTime()
            << std::endl;

  std::cout << "Expected settling time with 5% tolerance: 0.7"
            << std::endl;
  std::cout << "Actual settling time with 5% tolerance:   "
            << analysis_1.GetSettlingTime(5.0)
            << std::endl;

  std::cout << std::endl;


  // ----------------------------------------------------------
  // Test 2: Negative response with overshoot
  //
  // Steady-state value: -10
  // Minimum response:   -12
  // Overshoot:          2
  // Percent overshoot:  20%
  //
  // 50% target: -5, first reached at t = 0.3
  //
  // 10% target: -1, first reached at t = 0.1
  // 90% target: -9, first reached at t = 0.4
  // Rise time: 0.3
  //
  // 5% band: [-10.5, -9.5]
  // Last outside sample: t = 0.6
  // Settling begins at:  t = 0.7
  // ----------------------------------------------------------
  std::vector<double> time_2 = {
      0.0, 0.1, 0.2, 0.3, 0.4,
      0.5, 0.6, 0.7, 0.8, 0.9};

  std::vector<double> response_2 = {
      0.0, -1.2, -3.5, -5.4, -9.1,
      -12.0, -10.8, -10.4, -9.8, -10.0};

  PerformanceAnalysis analysis_2(time_2, response_2);

  std::cout << "Test 2 - Negative Response" << std::endl;

  std::cout << "Expected steady-state value: -10" << std::endl;
  std::cout << "Actual steady-state value:   "
            << analysis_2.GetSteadyStateValue()
            << std::endl;

  std::cout << "Expected overshoot: 2" << std::endl;
  std::cout << "Actual overshoot:   "
            << analysis_2.GetOvershoot()
            << std::endl;

  std::cout << "Expected percent overshoot: 20" << std::endl;
  std::cout << "Actual percent overshoot:   "
            << analysis_2.GetPercentOvershoot()
            << std::endl;

  std::cout << "Expected delay time: 0.3" << std::endl;
  std::cout << "Actual delay time:   "
            << analysis_2.GetDelayTime()
            << std::endl;

  std::cout << "Expected rise time: 0.3" << std::endl;
  std::cout << "Actual rise time:   "
            << analysis_2.GetRiseTime()
            << std::endl;

  std::cout << "Expected settling time with 5% tolerance: 0.7"
            << std::endl;
  std::cout << "Actual settling time with 5% tolerance:   "
            << analysis_2.GetSettlingTime(5.0)
            << std::endl;

  std::cout << std::endl;


  // ----------------------------------------------------------
  // Test 3: Response settled from the beginning
  // ----------------------------------------------------------
  std::vector<double> time_3 = {
      0.0, 0.1, 0.2, 0.3};

  std::vector<double> response_3 = {
      10.0, 10.2, 9.8, 10.0};

  PerformanceAnalysis analysis_3(time_3, response_3);

  std::cout << "Test 3 - Settled From Beginning" << std::endl;
  std::cout << "Expected settling time with 5% tolerance: 0"
            << std::endl;
  std::cout << "Actual settling time with 5% tolerance:   "
            << analysis_3.GetSettlingTime(5.0)
            << std::endl;

  std::cout << std::endl;

  // ----------------------------------------------------------
  // Test 5: Invalid vector sizes
  // ----------------------------------------------------------
  try {
    PerformanceAnalysis analysis_5(
        {0.0, 0.1, 0.2},
        {0.0, 1.0});

    std::cout << "Test 5: FAILED - exception expected"
              << std::endl;
  }
  catch (const std::invalid_argument& exception) {
    std::cout << "Test 5: PASSED - caught expected exception: "
              << exception.what()
              << std::endl;
  }

  std::cout << std::endl;


  // ----------------------------------------------------------
  // Test 6: Non-increasing time values
  // ----------------------------------------------------------
  try {
    PerformanceAnalysis analysis_6(
        {0.0, 0.2, 0.1},
        {0.0, 0.5, 1.0});

    std::cout << "Test 6: FAILED - exception expected"
              << std::endl;
  }
  catch (const std::invalid_argument& exception) {
    std::cout << "Test 6: PASSED - caught expected exception: "
              << exception.what()
              << std::endl;
  }

  std::cout << std::endl;


  // ----------------------------------------------------------
  // Test 7: Invalid settling tolerance
  // ----------------------------------------------------------
  try {
    analysis_1.GetSettlingTime(0.0);

    std::cout << "Test 7: FAILED - exception expected"
              << std::endl;
  }
  catch (const std::invalid_argument& exception) {
    std::cout << "Test 7: PASSED - caught expected exception: "
              << exception.what()
              << std::endl;
  }
}

void TestComplexEvaluation() {
  std::cout << "======================================" << std::endl;
  std::cout << "Testing Complex Transfer Function Evaluation" << std::endl;
  std::cout << "======================================" << std::endl;

  // Test 1: Evaluate (s + 1)/(s + 2) at s = j
  TransferFunction transfer_function({1, 1}, {1, 2});
  std::complex<double> s(0, 1);

  std::complex<double> result = transfer_function.Evaluate(s);

  std::cout << "Test 1" << std::endl;
  std::cout << "Expected: (0.6, 0.2)" << std::endl;
  std::cout << "Actual:   " << result << std::endl;

  std::cout << std::endl;

  // Test 2: Evaluate at the pole s = -2
  try {
    std::complex<double> pole(-2, 0);

    transfer_function.Evaluate(pole);

    std::cout << "Test 2: FAILED - exception expected" << std::endl;
  }
  catch (const std::domain_error& exception) {
    std::cout << "Test 2: PASSED - caught expected exception: "
              << exception.what() << std::endl;
  }
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

int main() {
  TestFrequencyResponse();


  return 0;
}