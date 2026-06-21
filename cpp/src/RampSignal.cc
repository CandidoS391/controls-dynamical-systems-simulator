#include "RampSignal.h"

RampSignal::RampSignal(double user_slope, double user_start_time) : slope(user_slope), start_time(user_start_time) {

}

double RampSignal::Value(double time) const {
  if (time < start_time)
    return 0;

  return slope * (time - start_time);
}