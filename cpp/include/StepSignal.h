#ifndef STEPSIGNAL_H_
#define STEPSIGNAL_H_

#include "InputSignal.h"

class StepSignal : public InputSignal {
  private:
    double start_time;
    double amplitude;

  public:
    StepSignal(double amp, double time);
    double Value(double time) const override;
};

#endif