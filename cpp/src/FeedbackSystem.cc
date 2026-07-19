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

