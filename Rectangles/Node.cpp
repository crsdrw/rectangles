#include "stdafx.h"
#include "Node.h"

namespace rec {

  void Node::findLeavesInternal(std::vector<const Node*>& leaves, const Vec* p) const {
    if (p && !isColision(*this, *p))
      return;

    if (isLeaf()) {
      leaves.push_back(this);
      return;
    }

    if (first)
      first->findLeavesInternal(leaves, p);
    if (second)
      second->findLeavesInternal(leaves, p);
  }

  std::vector<const Node*>
  Node::findLeaves() const {
    std::vector<const Node*> leaves;
    findLeavesInternal(leaves, nullptr);
    return leaves;
  }

  std::vector<const Node*>
  Node::findIntersectingLeaves(Vec p) const {
    std::vector<const Node*> leaves;
    findLeavesInternal(leaves, &p);
    return leaves;
  }
}