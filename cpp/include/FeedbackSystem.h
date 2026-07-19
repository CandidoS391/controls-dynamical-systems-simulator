#ifndef FEEDBACKSYSTEM_H_
#define FEEDBACKSYSTEM_H_

#include <vector>
#include <stdexcept>
#include <iostream>

#include "TransferFunction.h"
#include "ErrorConstantType.h"

class FeedbackSystem {
  private:
    TransferFunction forward_path;
    TransferFunction feedback_path;
    TransferFunction desired_transfer_function;

    double EvaluateErrorConstant(ErrorConstantType type) const;

  public:
    // Constructor
    FeedbackSystem(const TransferFunction& forward, const TransferFunction& feedback, const TransferFunction& desired);

    // System Transfer Functions
    TransferFunction GetLoopTransferFunction() const;
    TransferFunction GetClosedLoopTransferFunction() const;
    TransferFunction GetTransferError() const;

    // Accessors
    const TransferFunction& GetForwardPath() const;
    const TransferFunction& GetFeedbackPath() const;
    const TransferFunction& GetDesiredTransferFunction() const;

    // Errror Constants
    double GetStepErrorConstant() const;
    double GetRampErrorConstant() const;
    double GetParabolicErrorConstant() const;

};

#endif