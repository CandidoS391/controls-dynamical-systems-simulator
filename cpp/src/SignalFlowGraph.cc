#include "SignalFlowGraph.h"
#include "Branch.h"

void SignalFlowGraph::AddNode(const std::string& node) {
  nodes.push_back(node);
}

void SignalFlowGraph::AddBranch(const std::string& from, const std::string& to, const TransferFunction& gain) {
  Branch new_branch{from, to, gain};
  branches.push_back(new_branch);
}

void SignalFlowGraph::Print() const {
  // Print out nodes
  std::cout << "Nodes: " << std::endl;
  for (auto node : nodes) {
    std::cout << node << std::endl;
  }
  std::cout << std::endl;

  // Print out the Branches
  std::cout << "Branches: " << std::endl;
  for (auto branch : branches) {
    std::cout << branch.from << " -> " << branch.gain << " -> " << branch.to;
    std::cout << std::endl;
  }
}