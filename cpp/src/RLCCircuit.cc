#include "RLCCircuit.h"

RLCCircuit::RLCCircuit(double r, double l, double c, const InputSignal& in) : resistance_r(r), inductance_l(l), capacity_c(c), input(in) {
  
}

StateVector RLCCircuit::Derivative(const StateVector& state, double time) const {
  double q = state[0], i = state[1];

  double volt_input = input.Value(time);
  
  double dq_dt = i;
  double di_dt = -(resistance_r / inductance_l) * i - (1 / (inductance_l * capacity_c)) * q + (volt_input / inductance_l);

  return StateVector({dq_dt, di_dt});
}