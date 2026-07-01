#ifndef LOOP_H_
#define LOOP_H_

#include <vector>

#include "TransferFunction.h"
#include "Branch.h"

struct Loop {
  std::vector<Branch> branches;
};

#endif