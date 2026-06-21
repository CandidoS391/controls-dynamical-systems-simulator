#include "ConstantSignal.h"

ConstantSignal::ConstantSignal(double amp) : amplitude(amp) {

}

double ConstantSignal::Value(double time) const {
  return amplitude;
}