#include "stdafx.h"
#include "BinaryPartitioner.h"
#include "Node.h"
#include "Window.h"
#include <algorithm>

namespace {

  // local helper functions

  using rec::Window;
  bool horizontalCompare(const Window& lhs, const Window& rhs) { return getMaxX(lhs) < getMaxX(rhs); }
  bool verticalCompare(const Window& lhs, const Window& rhs) { return getMaxY(lhs) < getMaxY(rhs); }
}

namespace rec {

  // member functions

  // Constructor, takes a range into a vector of Window. Finds the bounding
  // box and count of Window in the range.
  BinaryPartitioner::BinaryPartitioner(Itr a, Itr b) : begin(a), end(b), count(0), box() {
    auto distance = std::distance(begin, end);
    if (distance < 0)
      std::logic_error("Invalid range");
    count = static_cast<size_t>(distance);
  }

  // Sort the range of window by their maximum X or Y, depending on
  // on which is larger the width or height of the bounding box
  void
  BinaryPartitioner::sort() {
    auto compare = box.size.x > box.size.y ? horizontalCompare : verticalCompare;
    std::sort(begin, end, compare);
  }

  // Split the range in two
  BinaryPartitioner::Itr
  BinaryPartitioner::findMid() {
    auto length = std::distance(begin, end);
    auto half_length = length / 2;
    Itr mid = begin;
    std::advance(mid, half_length);
    return mid;
  }

  void
  BinaryPartitioner::findBoundingBox() const {
    auto rec = begin;
    box = *rec++;
    for (; rec != end; ++rec)
      growWindow(box, *rec);
  }

  std::unique_ptr<Node>
  BinaryPartitioner::findTree() {

    if (count == 0)
      return nullptr;

    findBoundingBox();

    // Create a  node for the bounding box
    auto node = std::unique_ptr<Node>(new Node(box));

    // If there is more than one rectangle in the range
    // then create two sub-windows and recurse
    if (count > 1) {
      sort();
      auto mid = findMid();
      BinaryPartitioner bp1(begin, mid);
      BinaryPartitioner bp2(mid, end);
      node->attachFirst(bp1.findTree());
      node->attachSecond(bp2.findTree());
    }
    return node;
  }

}  // namespace rec

