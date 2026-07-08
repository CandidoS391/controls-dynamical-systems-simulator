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

std::vector<std::string> SignalFlowGraph::GetLoopNodes(const Loop& loop) const {
  std::vector<std::string> nodes_in_loop;

  for (const auto& branch : loop.branches) {
    if (!IsVisited(branch.from, nodes_in_loop))
      nodes_in_loop.push_back(branch.from);
    
    if (!IsVisited(branch.to, nodes_in_loop))
      nodes_in_loop.push_back(branch.to);
  }

  return nodes_in_loop;
}

bool SignalFlowGraph::AreNonTouching(const Loop& loop_1, const Loop& loop_2) const {
  std::vector<std::string> nodes_1 = GetLoopNodes(loop_1);
  std::vector<std::string> nodes_2 = GetLoopNodes(loop_2);

  for (const auto& node : nodes_1) {
    if (IsVisited(node, nodes_2))
      return false;
  }

  return true;
}

TransferFunction SignalFlowGraph::ComputeDelta(const std::vector<Loop>& loops) const {
  TransferFunction delta({1}, {1});

  for (const auto& loop : loops) {
    TransferFunction loop_gain = ComputeLoopGain(loop);
    delta = delta - loop_gain;
  }

  for (size_t i = 0; i < loops.size(); i++) {
    for (size_t j = i + 1; j < loops.size(); j++) {
      if (AreNonTouching(loops[i], loops[j])) {
        TransferFunction loop_i_gain = ComputeLoopGain(loops[i]);
        TransferFunction loop_j_gain = ComputeLoopGain(loops[j]);

        TransferFunction product = loop_i_gain.Series(loop_j_gain);
        delta = delta.Parallel(product);
      }
    }
  }

  return delta;
}

TransferFunction SignalFlowGraph::ComputeMasonGain() const {
  std::vector<Path> paths = FindForwardPaths();
  std::vector<Loop> loops = RemoveDuplicateLoops(FindLoops());
  
  if (paths.empty())
    throw std::underflow_error("There are no paths!");

  TransferFunction numerator_sum = ComputePathGain(paths[0]).Series(ComputeDeltaK(paths[0], loops));
  TransferFunction delta = ComputeDelta(loops);

  for (size_t i = 1; i < paths.size(); i++) {
    TransferFunction term = ComputePathGain(paths[i]).Series(ComputeDeltaK(paths[i], loops));
    numerator_sum = numerator_sum.Parallel(term);
  }

  return numerator_sum / delta;
}

std::vector<std::string> SignalFlowGraph::GetPathNodes(const Path& path) const {
  std::vector<std::string> nodes_in_path;

  for (const auto& branch : path.branches) {
    if (!IsVisited(branch.from, nodes_in_path))
      nodes_in_path.push_back(branch.from);

    if (!IsVisited(branch.to, nodes_in_path))
      nodes_in_path.push_back(branch.to);
  }

  return nodes_in_path;
}

bool SignalFlowGraph::AreSameLoop(const Loop& loop_1, const Loop& loop_2) const {
  std::vector<std::string> nodes_1 = GetLoopNodes(loop_1);
  std::vector<std::string> nodes_2 = GetLoopNodes(loop_2);

  if (nodes_1.size() != nodes_2.size())
    return false;

  for (const auto& node : nodes_1) {
    if (!IsVisited(node, nodes_2))
      return false;
  }

  return true;
}

std::vector<Loop> SignalFlowGraph::RemoveDuplicateLoops(const std::vector<Loop>& loops) const {
  std::vector<Loop> unique_loops;

  for (const auto& loop : loops) {
    bool duplicate = false;

    for (const auto& unique_loop : unique_loops) {
      if (AreSameLoop(loop, unique_loop)) {
        duplicate = true;
        break;
      }
    }

    if (!duplicate)
      unique_loops.push_back(loop);
  }

  return unique_loops;
}

bool SignalFlowGraph::DoesLoopTouchPath(const Loop& loop, const Path& path) const {
  std::vector<std::string> path_nodes = GetPathNodes(path);
  std::vector<std::string> loop_nodes = GetLoopNodes(loop);

  for (const auto& node : loop_nodes) {
    if (IsVisited(node, path_nodes))
      return true;
  }

  return false;
}

TransferFunction SignalFlowGraph::ComputeDeltaK(const Path& path, const std::vector<Loop>& loops) const {
  std::vector<Loop> usable_loops;

  for (const auto& loop : loops) {
    if (!DoesLoopTouchPath(loop, path))
      usable_loops.push_back(loop);
  }

  return ComputeDelta(usable_loops);
}