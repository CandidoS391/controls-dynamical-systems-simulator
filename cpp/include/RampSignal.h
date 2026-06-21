#ifndef RAMPSIGNAL_H_
#define RAMPSIGNAL_H_

#include "InputSignal.h"

class RampSignal : public InputSignal {
  private:
    double slope;
    double start_time;

  public:
    RampSignal(double user_slope, double user_start_time);
    double Value(double time) const override;
};

#endif