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

int main() {
  TestSignalFlowGraph();

  return 0;
}