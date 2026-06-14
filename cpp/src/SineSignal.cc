#include <cmath>
#include "SineSignal.h"

SineSignal::SineSignal(double amp, double ang) : amplitude(amp), angular_freq(ang) {

}

double SineSignal::Value(double time) const {
  return amplitude * std::sin(angular_freq * time);
}