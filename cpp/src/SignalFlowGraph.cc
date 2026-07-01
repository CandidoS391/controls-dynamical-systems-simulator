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

bool SignalFlowGraph::HasNode(const std::string& node_name) const {
  for (const auto& node : nodes) {
    if (node == node_name)
      return true;
  }

  return false;
}

void SignalFlowGraph::SetInputNode(const std::string& node_name) {
  if (!HasNode(node_name))
    throw std::out_of_range("Node doesn't exist!");

  input_node = node_name;
}

void SignalFlowGraph::SetOutputNode(const std::string& node_name) {
  if (!HasNode(node_name))
    throw std::out_of_range("Node doesn't exist!");

  output_node = node_name;
}

TransferFunction SignalFlowGraph::ComputePathGain(const std::vector<Branch>& path_branches) const {
  if (path_branches.empty())
    throw std::invalid_argument("There are no branches!");

  TransferFunction result = path_branches[0].gain;

  for (size_t i = 1; i < path_branches.size(); i++)
    result = result.Series(path_branches[i].gain);

  return result;
}