#include "FeedbackSystem.h"

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