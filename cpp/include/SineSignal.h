#ifndef SINESIGNAL_H_
#define SINESIGNAL_H_

#include "InputSignal.h"

class SineSignal : public InputSignal {
  private:
    double amplitude;
    double angular_freq;

  public:
    SineSignal(double amp, double ang);
    double Value(double time) const override;
};

#endif