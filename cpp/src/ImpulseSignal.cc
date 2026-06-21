#include "ImpulseSignal.h"

ImpulseSignal::ImpulseSignal(double amp, double start, double end) : amplitude(amp), start_time(start), end_time(end) {

}

double ImpulseSignal::Value(double time) const {
  if (time < start_time)
    return 0;
  if (time > end_time)
    return 0;

  return amplitude;
}