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

    // ---- Helper Functions ----

    // Helper Functions for FindForwardPath
    void DFSForwardPath(const std::string& curr_node, std::vector<Branch>& curr_path, std::vector<std::string>& visited, std::vector<Path>& paths) const;
    bool IsVisited(const std::string& node_name, const std::vector<std::string>& visited_nodes) const;

    // Helper Functions for FindLoops
    void DFSLoop(const std::string& start_node, const std::string& curr_node, std::vector<Branch>& curr_loop, std::vector<std::string>& visited, std::vector<Loop>& loops) const;

    // Helper Function for NonTouching function
    std::vector<std::string> GetLoopNodes(const Loop& loop) const;

    // Helper Function for ComputeDeltaK
    bool DoesLoopTouchPath(const Loop& loop, const Path& path) const;
    std::vector<std::string> GetPathNodes(const Path& path) const;
    bool AreSameLoop(const Loop& loop_1, const Loop& loop_2) const;
    std::vector<Loop> RemoveDuplicateLoops(const std::vector<Loop>& loops) const;

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

    std::vector<Loop> FindLoops() const;

    // Check if two loops are non-touching (essentially if two loops share no nodes)
    bool AreNonTouching(const Loop& loop_1, const Loop& loop_2) const;

    // Mason Gain Formuala
    TransferFunction ComputeDelta(const std::vector<Loop>& loops) const;
    TransferFunction ComputeMasonGain() const;
    TransferFunction ComputeDeltaK(const Path& path, const std::vector<Loop>& loops) const;
    
};

#endif