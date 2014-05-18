#include "stdafx.h"
#include "Node.h"


namespace {
  using rec::Node;
  using rec::Window;
  using rec::Vec;

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

  int getIntersectingCount(const Window& box, const std::list<Window>& rectangles) {
    int count = 0;
    for (auto& rectangle : rectangles) {
      if (isColision(box, getCentre(rectangle)))
        count++;
    }
    return count;
  }

  void
  divideWindow(const Window& in, Window &out1, Window &out2, float factor) {
    Vec second_pos;
    Vec half_size;

    if (in.size.x > in.size.y) {
      half_size = { in.size.x * factor, in.size.y };
      second_pos = in.pos + Vec{ half_size.x, 0.0f };
    } else {
      half_size = { in.size.x, in.size.y * factor };
      second_pos = in.pos + Vec{ 0.0f, half_size.y };
    }

    out1 = { in.pos, half_size };
    out2 = { second_pos, half_size };
  }

  void
  binaryPartition(Node& node, const std::list<Window>& rectangles) {
    Window bounding_box = node.getWindow();
    Window window1{ bounding_box.pos, { 0.0f, 0.0f } };
    Window window2(bounding_box);
    int half_count = static_cast<int>(rectangles.size() / 2);
    int difference = -half_count;
    float delta = 0.5f;
    float factor = 0.0f;
    for (int i = 0; i != 4 && std::abs(difference) > 1; ++i) {
      if (difference < 0)
        factor += delta;
      else
        factor -= delta;
      delta /= 2.0f;
      divideWindow(bounding_box, window1, window2, factor);
      int intersecting_count = getIntersectingCount(window1, rectangles);
      difference = intersecting_count - half_count;
    }
    node.setFirst(window1);
    node.setSecond(window2);
    // TODO
  }

}  // anonymous namespace

namespace rec {

  // member functions

  // Private method to find all leaves that intersect point p, if p is nullptr then just find all leaves.
  void Node::findLeavesInternal(std::vector<const Node*>& leaves, const Vec* p) const {
    
    // Check for intersect with point p if it exists
    if (p && !isColision(window, *p))
      return;

    // If this is a leaf of the tree then add self to the list and stop searching
    if (isLeaf()) {
      leaves.push_back(this);
      return;
    }

    // If there are one or two child nodes, recurse
    if (first)
      first->findLeavesInternal(leaves, p);
    if (second)
      second->findLeavesInternal(leaves, p);
  }


  // Public method to find all leaves
  std::vector<const Node*>
  Node::findLeaves() const {
    std::vector<const Node*> leaves;
    findLeavesInternal(leaves, nullptr);
    return leaves;
  }

  // Public method to find all leaves intersecting a point p
  std::vector<const Node*>
  Node::findIntersectingLeaves(Vec p) const {
    std::vector<const Node*> leaves;
    findLeavesInternal(leaves, &p);
    return leaves;
  }



  // Non-member non-friend functions
  Node
  merge(const std::list<Window>& rectangles) {
    Window bounding_box = findBoundingBox(rectangles);
    Node root(bounding_box);
    binaryPartition(root, rectangles);

    return root;
  }
}  // namespace rec
