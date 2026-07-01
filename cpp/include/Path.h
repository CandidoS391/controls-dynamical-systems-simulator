#ifndef PATH_H_
#define PATH_H_

#include <vector>
#include <string>

#include "TransferFunction.h"

struct Path {
  std::vector<std::string> nodes;
  TransferFunction gain;
};

#endif