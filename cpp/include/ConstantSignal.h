#ifndef CONSTANTSIGNAL_H_
#define CONSTANTSIGNAL_H_

#include "InputSignal.h"

class ConstantSignal : public InputSignal {
  private:
    double amplitude;

  public:
    ConstantSignal(double amp);
    double Value(double time) const override;
};

#endif