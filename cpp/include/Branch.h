#ifndef BRANCH_H_
#define BRANCH_H_

#include <string>

#include "TransferFunction.h"

struct Branch {
  std::string from;
  std::string to;
  TransferFunction gain;
};

#endif