#ifndef SIGNALFLOWGRAPH_H_
#define SIGNALFLOWGRAPH_H_

#include <iostream>
#include <vector>
#include <stdexcept>

#include "TransferFunction.h"
#include "Branch.h"
#include "Path.h"
#include "Loop.h"

class SignalFlowGraph {
  private:
    std::vector<std::string> nodes;
    std::vector<Branch> branches;
    std::string input_node;
    std::string output_node;

    // Helper Functions for FindForwardPath
    void DFSForwardPath(const std::string& curr_node, std::vector<Branch>& curr_path, std::vector<std::string>& visited, std::vector<Path>& paths) const;
    bool IsVisited(const std::string& node_name, const std::vector<std::string>& visited_nodes) const;

  public:
    void AddNode(const std::string& node_name);
    void AddBranch(const std::string& from, const std::string& to, const TransferFunction& gain);
    void Print() const;
    bool HasNode(const std::string& node_name) const;
    void SetInputNode(const std::string& node_name);
    void SetOutputNode(const std::string& node_name);
    TransferFunction ComputePathGain(const Path& path) const;
    TransferFunction ComputeLoopGain(const Loop& loop) const;

    std::vector<Branch> GetOutgoingBranches( const std::string& node_name) const;

    // Use DFS helper function to find Forward paths
    std::vector<Path> FindForwardPaths() const;
};

#endif