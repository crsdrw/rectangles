#include "stdafx.h"
#include "Node.h"

namespace {
  using rec::Node;
  using rec::Vec;

  inline Node sizeOnlyCopy(const Node& in) { return Node(in.getPos(), in.getSize()); }

  Node
  findBoundingBox(const std::vector<Node>& nodes) {
    if (nodes.size() == 0u)
      throw std::logic_error("Can't find bounding box of zero nodes");
    
    Node box = sizeOnlyCopy(nodes[0]);
    for (auto node = nodes.cbegin() + 1; node != nodes.cend(); ++node) {
      box.growNode(node->getPos());
      box.growNode(getMax(*node));
    }
    return box;
  }

  void
  binaryPartition(Node& node) {
    Vec second_pos;
    Vec half_size;

    if (node.getSize().x > node.getSize().y) {
      half_size = { node.getSize().x / 2, node.getSize().y };
      second_pos = node.getPos() + Vec{ half_size.x, 0.0f };
    } else {
      half_size = { node.getSize().x, node.getSize().y / 2 };
      second_pos = node.getPos() + Vec{ 0.0f, half_size.y };
    }

    node.setFirst(node.getPos(), half_size);
    node.setSecond(second_pos, half_size);
  }

} // anonymous namespace

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

  void
  Node::growNode(Vec p) {
    if (p.x < pos.x)
      pos.x = p.x;
    if (p.y < pos.y)
      pos.y = p.y;

    Vec offset = p - pos;
    if (offset.x > size.x)
      size.x = offset.x;
    if (offset.y > size.y)
      size.y = offset.y;
  }

  // Non-member non-friend functions
  Node 
  merge(const std::vector<Node>& nodes) {
    Node root = findBoundingBox(nodes);
    binaryPartition(root);
    
    //TODO

    return root;
  }
} // namespace rec