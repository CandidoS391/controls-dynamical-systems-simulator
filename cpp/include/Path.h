#ifndef PATH_H_
#define PATH_H_

#include <vector>
#include <string>

#include "TransferFunction.h"
#include "Branch.h"

struct Path {
  std::vector<Branch> branches;
};

#endif