#include "stdafx.h"
#include "Node.h"

namespace rec {

  // Private member function to find all leaves that intersect point p, if p is nullptr then just find all leaves.
  void Node::findLeavesInternal(std::vector<Window>& leaves, const Vec* p) const {
    
    // Check for intersect with point p if it exists
    if (p && !isColision(window, *p))
      return;

    // If this is a leaf of the tree then add window to the list and stop searching
    if (isLeaf()) {
      leaves.push_back(getWindow());
      return;
    }

    // if there are any child nodes recurse
    if (first)
      first->findLeavesInternal(leaves, p);
    if (second)
      second->findLeavesInternal(leaves, p);
  }


  // Public mmeber function to find all leaves
  std::vector<Window>
  Node::findLeaves() const {
    std::vector<Window> leaves;
    findLeavesInternal(leaves, nullptr);
    return leaves;
  }

  // Public member function to find all leaves intersecting a point p
  std::vector<Window>
  Node::findIntersectingLeaves(Vec p) const {
    std::vector<Window> leaves;
    findLeavesInternal(leaves, &p);
    return leaves;
  }
}  // namespace rec
