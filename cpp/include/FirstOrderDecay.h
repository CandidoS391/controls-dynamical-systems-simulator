#ifndef FIRSTORDERDECAY_H_
#define FIRSTORDERDECAY_H_

#include "DynamicalSystem.h"

class FirstOrderDecay : public DynamicalSystem {
  private:
    double decay_k;

  public:
    FirstOrderDecay(double input_k) : decay_k(input_k) {

    }
    StateVector Derivative(const StateVector& , double ) const override;
};


#endif