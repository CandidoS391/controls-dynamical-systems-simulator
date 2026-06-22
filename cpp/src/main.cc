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

int main() {
  // Evaluate the Series function
  // TransferFunction g1({1, 1}, {1, 2});
  // TransferFunction g2({1, 3}, {1, 4});

  // TransferFunction result = g1.Series(g2);
  // result.Print();

  // Evaluate the Parallel Function
  TransferFunction g1({1}, {1, 1});  // 1/(s+1)
  TransferFunction g2({1}, {1, 2});  // 1/(s+2)

  TransferFunction result = g1.Parallel(g2);
  result.Print();

  // Evaluate the Feedback Function
  TransferFunction g({1}, {1, 2});  // 1/(s+2)

  TransferFunction closed = g.Feedback();
  closed.Print();
  return 0;
}