#ifndef IMPULSESIGNAL_H_
#define IMPULSESIGNAL_H_

#include "InputSignal.h"

class ImpulseSignal : public InputSignal {
  private:
    double amplitude;
    double start_time;
    double end_time;

  public:
    ImpulseSignal(double amp, double start, double end);
    double Value(double time) const override;
};

#endif