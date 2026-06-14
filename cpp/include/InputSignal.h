#ifndef INPUTSIGNAL_H_
#define INPUTSIGNAL_H_

class InputSignal {
  public:
    virtual ~InputSignal() = default;
    virtual double Value(double time = 0) const = 0;
};

#endif