#ifndef SIGNALFLOWGRAPH_H_
#define SIGNALFLOWGRAPH_H_

#include <iostream>
#include <vector>

#include "Branch.h"

class SignalFlowGraph {
  private:
    std::vector<std::string> nodes;
    std::vector<Branch> branches;

  public:
    void AddNode(const std::string& node_name);
    void AddBranch(const std::string& from, const std::string& to, const TransferFunction& gain);
    void Print() const;
};

#endif