#include "stdafx.h"
#include "Node.h"


namespace {
  using rec::Node;
  using rec::Window;

  // local helper functions

  Window
  findBoundingBox(const std::list<Window>& rectangles) {
    if (rectangles.empty())
      throw std::logic_error("Can't find bounding box of zero nodes");

    auto rec = rectangles.cbegin();
    Window box = *rec++;
    for (; rec != rectangles.cend(); ++rec)
      growWindow(box, *rec);
    return box;
  }

  //int getIntersectingCount(const Node& root, const std::list<Node>& nodes) {
  //  int count = 0;
  //  for (auto& node : nodes) {
  //    if (isColision(root, getCentre(node)))
  //      count++;
  //  }
  //  return count;
  //}

  //void
  //binaryPartition(Node& node, const std::list<Node>& nodes) {
  //  Vec second_pos;
  //  Vec half_size;

  //  if (node.getSize().x > node.getSize().y) {
  //    half_size = { node.getSize().x / 2, node.getSize().y };
  //    second_pos = node.getPos() + Vec{ half_size.x, 0.0f };
  //  } else {
  //    half_size = { node.getSize().x, node.getSize().y / 2 };
  //    second_pos = node.getPos() + Vec{ 0.0f, half_size.y };
  //  }

  //  node.setFirst(node.getPos(), half_size);
  //  node.setSecond(second_pos, half_size);
  //  int intersecting_count = getIntersectingCount(, nodes);
  //  while (intersecting_count - nodes.size / 2)
  //}

} // anonymous namespace

namespace rec {

  // member functions
  void Node::findLeavesInternal(std::vector<const Node*>& leaves, const Vec* p) const {
    if (p && !isColision(window, *p))
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



  // Non-member non-friend functions
  //Node 
  //merge(const std::list<Window>& rectangles) {
  //  Window root = findBoundingBox(rectangles);
  //  binaryPartition(root, nodes);
  //  
  //  

  //  return root;
  //}
} // namespace rec