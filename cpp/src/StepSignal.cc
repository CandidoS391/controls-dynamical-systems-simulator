#include "StepSignal.h"

StepSignal::StepSignal(double amp, double time) : start_time(time), amplitude(amp) {

}

double StepSignal::Value(double time) const {
  if (time < start_time)
    return 0;
  else
    return amplitude;
}

