#include "FeedbackSystem.h"
#include "ErrorConstantType.h"

FeedbackSystem::FeedbackSystem(const TransferFunction& forward, const TransferFunction& feedback, const TransferFunction& desired) : forward_path(forward), feedback_path(feedback), desired_transfer_function(desired) {

}

//Accessors
const TransferFunction& FeedbackSystem::GetForwardPath() const {
  return forward_path;
}

const TransferFunction& FeedbackSystem::GetFeedbackPath() const {
  return feedback_path;
}

const TransferFunction& FeedbackSystem::GetDesiredTransferFunction() const {
  return desired_transfer_function;
}

// Multiply Transfer Functions G(s) and H(s) together
TransferFunction FeedbackSystem::GetLoopTransferFunction() const {
  return forward_path.Series(feedback_path);
}

// Calculate C/R 
TransferFunction FeedbackSystem::GetClosedLoopTransferFunction() const {
  TransferFunction loop_transfer = GetLoopTransferFunction();
  // Constant 1
  TransferFunction constant_transfer({1}, {1});

  TransferFunction denominator = loop_transfer.Parallel(constant_transfer);

  return forward_path / denominator;
}

// Calculate the difference between the desired transfer function and the actual transfer function
TransferFunction FeedbackSystem::GetTransferError() const {
  TransferFunction closed_loop = GetClosedLoopTransferFunction();

  return desired_transfer_function - closed_loop;
}

double FeedbackSystem::EvaluateErrorConstant(ErrorConstantType type) const {
  TransferFunction transfer_error = GetTransferError();
  int power;

  switch (type) {
    case ErrorConstantType::kStep:
      power = 0;
      break;
    case ErrorConstantType::kRamp:
      power = 1;
      break;
    case ErrorConstantType::kParabolic:
      power = 2;
      break;
    default:
      throw std::invalid_argument("Invalid error constant!");
  }


  double limit = transfer_error.LimitAtOriginAfterDividingBySPower(power);
  if (std::abs(limit) < 1e-8)
    return std::numeric_limits<double>::infinity();
  if (std::isinf(limit))
    return 0;

  return 1 / limit;
}

double FeedbackSystem::GetStepErrorConstant() const {
  return EvaluateErrorConstant(ErrorConstantType::kStep);
}

double FeedbackSystem::GetRampErrorConstant() const {
  return EvaluateErrorConstant(ErrorConstantType::kRamp);
}

double FeedbackSystem::GetParabolicErrorConstant() const {
  return EvaluateErrorConstant(ErrorConstantType::kParabolic);
}

TransferFunction FeedbackSystem::GetForwardPathSensitivity() const {
  // Compute the loop transfer function G(s)H(s)
  TransferFunction loop_transfer_function = GetLoopTransferFunction();
  // Constant 
  TransferFunction constant({1}, {1});

  return constant / constant.Parallel(loop_transfer_function);
}

TransferFunction FeedbackSystem::GetFeedbackPathSensitivity() const {
  // Compute the loop transfer function G(s)H(s)
  TransferFunction loop_transfer_function = GetLoopTransferFunction();
  // Constant (both positive and negative)
  TransferFunction constant({1}, {1});
  TransferFunction negative_constant({-1}, {1});

  // Add 1 to the loop transfer, the negate it
  TransferFunction negative_loop_transfer_function = negative_constant.Series(loop_transfer_function);
  return negative_loop_transfer_function / constant.Parallel(loop_transfer_function);
}

TransferFunction FeedbackSystem::GetForwardParameterSensitivity(const SensitivityAnalysis& forward_analysis) const {
  // Calculate the closed-loop sensitivity to the forward path
  TransferFunction forward_path_sensitivity = GetForwardPathSensitivity();
  // Get the sensitivity of G with respect to k using the passed in forward_analysis
  TransferFunction sensitivity_of_g = forward_analysis.GetTransferFunctionSensitivity();

  // Multiply the two sensitivity transfer functions and return
  return forward_path_sensitivity.Series(sensitivity_of_g);
}

TransferFunction FeedbackSystem::GetFeedbackParameterSensitivity(const SensitivityAnalysis& feedback_analysis) const {
  // Calculate the closed-loop sensitivity to the feedback path
  TransferFunction feedback_path_sensitivity = GetFeedbackPathSensitivity();
  // Get the sensitivity of H with respect to k using the passed in feedback_analysis
  TransferFunction sensitivity_of_h = feedback_analysis.GetTransferFunctionSensitivity();
  
  // Multiply the two sensitivity transfer functions and return
  return feedback_path_sensitivity.Series(sensitivity_of_h);
}

TransferFunction FeedbackSystem::GetCombinedParameterSensitivity(const SensitivityAnalysis& forward_analysis, const SensitivityAnalysis& feedback_analysis) const {
  // Get both the forward contribution and feedback contribution then add them up
  TransferFunction forward_contribution = GetForwardParameterSensitivity(forward_analysis);
  TransferFunction feedback_contribution = GetFeedbackParameterSensitivity(feedback_analysis);

  return forward_contribution.Parallel(feedback_contribution);
}