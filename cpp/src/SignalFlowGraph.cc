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

TransferFunction SignalFlowGraph::ComputePathGain(const Path& path) const {
  if (path.branches.empty())
    throw std::invalid_argument("There are no branches!");

  TransferFunction result = path.branches[0].gain;

  for (size_t i = 1; i < path.branches.size(); i++)
    result = result.Series(path.branches[i].gain);

  return result;
}

TransferFunction SignalFlowGraph::ComputeLoopGain(const Loop& loop) const {
  Path loop_as_path{loop.branches};
  return ComputePathGain(loop_as_path);
}

std::vector<Branch> SignalFlowGraph::GetOutgoingBranches(const std::string& node_name) const {
  std::vector<Branch> outgoing_branches;

  for (const auto& branch : branches) {
    if (branch.from == node_name)
      outgoing_branches.push_back(branch);
  }

  return outgoing_branches;
}

bool SignalFlowGraph::IsVisited(const std::string& node_name, const std::vector<std::string>& visited_nodes) const {
  for (const auto& node : visited_nodes) {
    if (node == node_name)
      return true;
  }

  return false;
}

void SignalFlowGraph::DFSForwardPath(const std::string& curr_node, std::vector<Branch>& curr_path, std::vector<std::string>& visited, std::vector<Path>& paths) const {
  // Base case
  if (curr_node == output_node) {
    Path new_path{curr_path};
    paths.push_back(new_path);
    return;
  }

  visited.push_back(curr_node);

  std::vector<Branch> outgoing_branches = GetOutgoingBranches(curr_node);
  for (const auto& branch : outgoing_branches) {
    std::string next_node = branch.to;
    if (!IsVisited(next_node, visited)) {
      curr_path.push_back(branch);
      DFSForwardPath(next_node, curr_path, visited, paths);
      curr_path.pop_back();
    }
  }

  visited.pop_back();
}

std::vector<Path> SignalFlowGraph::FindForwardPaths() const {
  std::vector<Path> path;
  std::vector<Branch> curr_path;
  std::vector<std::string> visited;

  DFSForwardPath(input_node, curr_path, visited, path);

  return path;
}

void SignalFlowGraph::DFSLoop(const std::string& start_node, const std::string& curr_node, std::vector<Branch>& curr_loop, std::vector<std::string>& visited, std::vector<Loop>& loops) const {
  visited.push_back(curr_node);
  std::vector<Branch> outgoing_branches = GetOutgoingBranches(curr_node);
  
  for (const auto& branch : outgoing_branches) {
    std::string next_node = branch.to;
    if (next_node == start_node) {
      curr_loop.push_back(branch);
      Loop new_loop{curr_loop};
      loops.push_back(new_loop);
      curr_loop.pop_back();
    } else if (!IsVisited(next_node, visited)) {
      curr_loop.push_back(branch);
      DFSLoop(start_node, next_node, curr_loop, visited, loops);
      curr_loop.pop_back();
    }

  }
  visited.pop_back();
}

std::vector<Loop> SignalFlowGraph::FindLoops() const {
  std::vector<Loop> all_loops;

  for (const auto& node : nodes) {
    std::vector<Branch> curr_loop;
    std::vector<std::string> visited;

    DFSLoop(node, node, curr_loop, visited, all_loops);
  }

  return all_loops;
}