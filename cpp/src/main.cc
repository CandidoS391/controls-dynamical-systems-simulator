#include <iostream>
#include <fstream>
#include <vector>
#include <string>

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

void TestSignalFlowGraph() {
  SignalFlowGraph graph;

  graph.AddNode("R");
  graph.AddNode("x1");
  graph.AddNode("x2");
  graph.AddNode("C");

  graph.SetInputNode("R");
  graph.SetOutputNode("C");

  TransferFunction g1({1}, {1, 1});
  TransferFunction g2({2}, {1, 2});
  TransferFunction g3({3}, {1, 3});
  TransferFunction h1({1}, {1});

  Branch b1{"R", "x1", g1};
  Branch b2{"x1", "x2", g2};
  Branch b3{"x2", "C", g3};
  Branch b4{"C", "x1", h1};

  graph.AddBranch(b1.from, b1.to, b1.gain);
  graph.AddBranch(b2.from, b2.to, b2.gain);
  graph.AddBranch(b3.from, b3.to, b3.gain);
  graph.AddBranch(b4.from, b4.to, b4.gain);

  graph.Print();

  Path forward_path{{b1, b2, b3}};
  TransferFunction path_gain = graph.ComputePathGain(forward_path);

  std::cout << "\nForward Path Gain R -> x1 -> x2 -> C:\n";
  std::cout << path_gain << std::endl;

  Loop loop{{b2, b3, b4}};
  TransferFunction loop_gain = graph.ComputeLoopGain(loop);

  
  std::cout << "\nLoop Gain x1 -> x2 -> C -> x1:\n";
  std::cout << loop_gain << std::endl;

  std::vector<Path> paths = graph.FindForwardPaths();
  std::cout << "\nNumber of forward paths found: " << paths.size() << std::endl;

  for (const auto& path : paths) {
    for (const auto& branch : path.branches) {
      std::cout << branch.from << " -> ";
    }

    std::cout << path.branches.back().to << std::endl;
  }

  // ------ Testing finding loops -------
  // Test 1: One Simple loop

  std::vector<Loop> loops = graph.FindLoops();
  std::cout << "Number of loops found: " << loops.size() << std::endl;

  for (const auto& loop : loops) {
    std::cout << "Loop: ";
    for (const auto& branch: loop.branches) {
      std::cout << branch.from << " -> ";
    }
    std::cout << loop.branches.back().to << std::endl;

    std::cout << "Gain: " << graph.ComputeLoopGain(loop) << std::endl;
  }

  // Test 2: graph with no loop
  SignalFlowGraph graph2;

  graph2.AddNode("R");
  graph2.AddNode("x1");
  graph2.AddNode("C");

  graph2.SetInputNode("R");
  graph2.SetOutputNode("C");

  graph2.AddBranch("R", "x1", g1);
  graph2.AddBranch("x1", "C", g2);

  std::vector<Loop> loops_2 = graph2.FindLoops();

  std::cout << "Number of loops in graph2: " << loops_2.size() << std::endl;

  // Test 3: self loop
  SignalFlowGraph graph3;

  graph3.AddNode("R");
  graph3.AddNode("x1");
  graph3.AddNode("C");

  graph3.SetInputNode("R");
  graph3.SetOutputNode("C");

  TransferFunction g({1}, {1});
  TransferFunction h({5}, {1});

  graph3.AddBranch("R", "x1", g);
  graph3.AddBranch("x1", "x1", h);
  graph3.AddBranch("x1", "C", g);

  std::vector<Loop> loops3 = graph3.FindLoops();

  std::cout << "Number of loops in graph3: " << loops3.size() << std::endl;

  // ------ Testing AreNonTouching -------
  // Test 1: touching loops
  Loop loop1{{b2, b3, b4}};
  Loop loop2{{b3, b4, b2}};

  std::cout << graph.AreNonTouching(loop1, loop2) << std::endl;

  // test 2: Non-touching loops
  graph.AddNode("a");
  graph.AddNode("b");

  TransferFunction k1({4}, {1});
  TransferFunction k2({5}, {1});

  Branch b5{"a", "b", k1};
  Branch b6{"b", "a", k2};

  Loop loop3{{b5, b6}};

  std::cout << graph.AreNonTouching(loop1, loop3) << std::endl;

  // Test 3: One shared node:
  Branch b7{"C", "a", k1};
  Branch b8{"a", "C", k2};

  Loop loop4{{b7, b8}};

  std::cout << graph.AreNonTouching(loop1, loop4) << std::endl;

  // ------ Testing Mason Gain Formula ------
  std::vector<Loop> one_loop{loops[0]};

  TransferFunction delta = graph.ComputeDelta(one_loop);
  std::cout << "\nDelta:\n";
  delta.Print();

  

  TransferFunction mason_gain = graph.ComputeMasonGain();

  std::cout << "\nMason Gain:\n";
  mason_gain.Print();
}

void TestSignalFlowGraphInvalidNode() {
  SignalFlowGraph graph;

  graph.AddNode("R");
  graph.AddNode("C");

  try {
    graph.SetInputNode("x1");
  } catch (const std::out_of_range& e) {
    std::cout << "Caught expected error: " << e.what() << std::endl;
  }
}

void TestTransferFunctionSubtract() {
  TransferFunction g1({1}, {1, 1});  // 1 / (s + 1)
  TransferFunction g2({2}, {1, 2});  // 2 / (s + 2)

  TransferFunction result = g1 - g2;

  std::cout << "\nSubtract Test: g1 - g2\n";
  result.Print();
  // Expected:
  // Numerator: -1 0
  // Denominator: 1 3 2
}

void TestTransferFunctionDivide() {
  TransferFunction g1({1}, {1, 1});  // 1 / (s + 1)
  TransferFunction g2({2}, {1, 2});  // 2 / (s + 2)

  TransferFunction result = g1 / g2;

  std::cout << "\nDivide Test: g1 / g2\n";
  result.Print();
  // Expected:
  // Numerator: 1 2
  // Denominator: 2 2
}

void TestTransferFunctionMasonPrep() {
  TransferFunction one({1}, {1});
  TransferFunction loop1({-2}, {1, 2});
  TransferFunction loop2({-3}, {1, 3});

  TransferFunction loop_sum = loop1.Parallel(loop2);
  TransferFunction delta = one - loop_sum;

  std::cout << "\nMason Delta Prep Test: 1 - (L1 + L2)\n";
  delta.Print();
  // Expected:
  // loop_sum = (-5s - 12) / ((s+2)(s+3))
  // delta = (s^2 + 10s + 18) / (s^2 + 5s + 6)
}

void TestNonTouchingDelta() {
  SignalFlowGraph graph;

  TransferFunction one({1}, {1});
  TransferFunction g1({2}, {1});
  TransferFunction g2({3}, {1});
  TransferFunction h1({4}, {1});
  TransferFunction h2({5}, {1});

  Branch b1{"x1", "x2", g1};
  Branch b2{"x2", "x1", h1};

  Branch b3{"x3", "x4", g2};
  Branch b4{"x4", "x3", h2};

  Loop loop1{{b1, b2}};
  Loop loop2{{b3, b4}};

  std::cout << "\nNon-Touching Test:\n";
  std::cout << "Are non-touching: "
            << graph.AreNonTouching(loop1, loop2)
            << std::endl;

  std::vector<Loop> loops{loop1, loop2};

  TransferFunction delta = graph.ComputeDelta(loops);

  std::cout << "Delta:\n";
  delta.Print();
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

void TestPartialFractionExpansion() {
  // Test 1: Two distinct real poles
  TransferFunction g({5, 7}, {1, 3, 2});

  std::vector<PartialFractionTerm> terms = g.PartialFractionExpansion();

  std::cout << "Partial Fraction Terms (Test 1):\n";
  g.PrintPartialFractionExpression();

  // Test 2: Three distinct real poles
  TransferFunction g_2({1}, {1, 6, 11, 6});

  std::cout << "Partial Fraction Terms (Test 2):\n";
  std::vector<PartialFractionTerm> terms_2 = g_2.PartialFractionExpansion();

  g_2.PrintPartialFractionExpression();

  // Test 3: Repeated pole
  // 1 / (s + 1)^2
  TransferFunction g_3({1}, {1, 2, 1});
  std::cout << "Partial Fraction Terms (Test 3):\n";

  std::vector<PartialFractionTerm> terms_3 = g_3.PartialFractionExpansion();

  g_3.PrintPartialFractionExpression();

  // Test 4: Unsupported triple pole
  // 1 / (s + 1)^3
  TransferFunction g_4({1}, {1, 3, 3, 1});

  std::cout << "Partial Fraction Terms (Test 4):\n";

  try {
    std::vector<PartialFractionTerm> terms_4 = g_4.PartialFractionExpansion();

    std::cout << "ERROR: Triple pole was not rejected.\n";
  } catch (const std::invalid_argument& error) {
    std::cout << "Expected exception: " << error.what() << std::endl;
  }

  std::cout << std::endl;
}

void TestRouthTable() {
  // Test 1: Stable cubic
  // s^3 + 6s^2 + 11s + 6
  RouthTable stable_table({1, 6, 11, 6});

  std::cout << "Routh Table (Test 1 - Stable Cubic):\n";
  stable_table.Build();
  stable_table.Print();

  StabilityStatus stable_status = stable_table.GetStability();

  if (stable_status == StabilityStatus::k_stable)
    std::cout << "System is stable\n";
  else
    std::cout << "ERROR: Expected stable system\n";

  std::cout << std::endl;


  // Test 2: Unstable cubic
  // s^3 - 2s^2 + s + 2
  RouthTable unstable_table({1, -2, 1, 2});

  std::cout << "Routh Table (Test 2 - Unstable Cubic):\n";
  unstable_table.Build();
  unstable_table.Print();

  StabilityStatus unstable_status = unstable_table.GetStability();

  if (unstable_status == StabilityStatus::k_unstable)
    std::cout << "System is unstable\n";
  else
    std::cout << "ERROR: Expected unstable system\n";

  std::cout << std::endl;


  // Test 3: Stable fourth-order polynomial
  // (s + 1)(s + 2)(s + 3)(s + 4)
  // s^4 + 10s^3 + 35s^2 + 50s + 24
  RouthTable fourth_order_table({1, 10, 35, 50, 24});

  std::cout << "Routh Table (Test 3 - Stable Fourth Order):\n";
  fourth_order_table.Build();
  fourth_order_table.Print();

  StabilityStatus fourth_order_status =
      fourth_order_table.GetStability();

  if (fourth_order_status == StabilityStatus::k_stable)
    std::cout << "System is stable\n";
  else
    std::cout << "ERROR: Expected stable system\n";

  std::cout << std::endl;

  // Test 4: Entire row of zeros handled with auxiliary polynomial
  // s^4 + 2s^2 + 1 = (s^2 + 1)^2
  RouthTable zero_row_table({1, 0, 2, 0, 1});

  std::cout << "Routh Table (Test 4 - Zero Row Replacement):\n";

  zero_row_table.Build();
  zero_row_table.Print();

  StabilityStatus zero_row_status =
      zero_row_table.GetStability();

  if (zero_row_status == StabilityStatus::k_marginally_stable)
    std::cout << "System is marginally stable\n";
  else
    std::cout << "ERROR: Expected marginally stable system\n";

  std::cout << std::endl;
}

void TestLimitAtOrigin() {
  std::cout << "==============================" << std::endl;
  std::cout << "Testing Limit At Origin" << std::endl;
  std::cout << "==============================" << std::endl;

  // ------------------------------------------------------------
  // Test 1
  // T(s) = 1 / (s + 1)
  // ------------------------------------------------------------
  TransferFunction t1({1}, {1, 1});

  std::cout << "Test 1 - 1 / (s + 1)" << std::endl;
  std::cout << "Power 0 (Expected: 1): "
            << t1.LimitAtOriginAfterDividingBySPower(0)
            << std::endl;
  std::cout << "Power 1 (Expected: inf): "
            << t1.LimitAtOriginAfterDividingBySPower(1)
            << std::endl;
  std::cout << std::endl;


  // ------------------------------------------------------------
  // Test 2
  // T(s) = s / (s + 1)
  // ------------------------------------------------------------
  TransferFunction t2({1, 0}, {1, 1});

  std::cout << "Test 2 - s / (s + 1)" << std::endl;
  std::cout << "Power 0 (Expected: 0): "
            << t2.LimitAtOriginAfterDividingBySPower(0)
            << std::endl;
  std::cout << "Power 1 (Expected: 1): "
            << t2.LimitAtOriginAfterDividingBySPower(1)
            << std::endl;
  std::cout << "Power 2 (Expected: inf): "
            << t2.LimitAtOriginAfterDividingBySPower(2)
            << std::endl;
  std::cout << std::endl;


  // ------------------------------------------------------------
  // Test 3
  // T(s) = s² / (s + 1)
  // ------------------------------------------------------------
  TransferFunction t3({1, 0, 0}, {1, 1});

  std::cout << "Test 3 - s^2 / (s + 1)" << std::endl;
  std::cout << "Power 0 (Expected: 0): "
            << t3.LimitAtOriginAfterDividingBySPower(0)
            << std::endl;
  std::cout << "Power 1 (Expected: 0): "
            << t3.LimitAtOriginAfterDividingBySPower(1)
            << std::endl;
  std::cout << "Power 2 (Expected: 1): "
            << t3.LimitAtOriginAfterDividingBySPower(2)
            << std::endl;
  std::cout << std::endl;


  // ------------------------------------------------------------
  // Test 4
  // T(s) = 0
  // ------------------------------------------------------------
  TransferFunction t4({0}, {1});

  std::cout << "Test 4 - Zero Transfer Function" << std::endl;
  std::cout << "Power 0 (Expected: 0): "
            << t4.LimitAtOriginAfterDividingBySPower(0)
            << std::endl;
  std::cout << "Power 1 (Expected: 0): "
            << t4.LimitAtOriginAfterDividingBySPower(1)
            << std::endl;
  std::cout << std::endl;
}

void TestTransferFunctionSystemType() {
  std::cout << "==============================\n";
  std::cout << "Testing Transfer Function Type\n";
  std::cout << "==============================\n\n";

  // Test 1: Type 0
  TransferFunction type_zero({5}, {1, 2});
  std::cout << "Test 1 - Type 0\n";
  std::cout << "Expected: 0\n";
  std::cout << "Actual:   " << type_zero.GetSystemType() << "\n\n";

  // Test 2: Type 1
  TransferFunction type_one({5}, {1, 2, 0});
  std::cout << "Test 2 - Type 1\n";
  std::cout << "Expected: 1\n";
  std::cout << "Actual:   " << type_one.GetSystemType() << "\n\n";

  // Test 3: Type 2
  TransferFunction type_two({5}, {1, 2, 0, 0});
  std::cout << "Test 3 - Type 2\n";
  std::cout << "Expected: 2\n";
  std::cout << "Actual:   " << type_two.GetSystemType() << "\n\n";

  // Test 4: Type 3
  TransferFunction type_three({5}, {1, 2, 0, 0, 0});
  std::cout << "Test 4 - Type 3\n";
  std::cout << "Expected: 3\n";
  std::cout << "Actual:   " << type_three.GetSystemType() << "\n\n";

  // Test 5: Type 1 with additional poles
  TransferFunction mixed({10}, {1, 6, 11, 6, 0});
  std::cout << "Test 5 - Type 1 with additional poles\n";
  std::cout << "Expected: 1\n";
  std::cout << "Actual:   " << mixed.GetSystemType() << "\n\n";

  // Test 6: Nonconstant numerator
  TransferFunction numerator({3, 7}, {1, 4, 0});
  std::cout << "Test 6 - Nonconstant numerator\n";
  std::cout << "Expected: 1\n";
  std::cout << "Actual:   " << numerator.GetSystemType() << "\n\n";
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

int main() {
  TestErrorConstants();


  return 0;
}