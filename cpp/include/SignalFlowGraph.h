#ifndef SIGNALFLOWGRAPH_H_
#define SIGNALFLOWGRAPH_H_

#include <iostream>
#include <vector>
#include <stdexcept>

#include "TransferFunction.h"
#include "Branch.h"

class SignalFlowGraph {
  private:
    std::vector<std::string> nodes;
    std::vector<Branch> branches;
    std::string input_node;
    std::string output_node;

  public:
    void AddNode(const std::string& node_name);
    void AddBranch(const std::string& from, const std::string& to, const TransferFunction& gain);
    void Print() const;
    bool HasNode(const std::string& node_name) const;
    void SetInputNode(const std::string& node_name);
    void SetOutputNode(const std::string& node_name);
    TransferFunction ComputePathGain(const std::vector<Branch>& path_branches) const;
};

#endif