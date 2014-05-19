#pragma once
#include <vector>
#include <functional>
#include "Window.h"
#include <memory>

namespace rec {
  class Node;

  /** Class to create a binary tree of a list of rectangles */
  class BinaryPartitioner {
  private:

    typedef std::vector<Window>::iterator Itr;

    // Range in a vector of Window
    Itr    begin;
    Itr    end;

    // Count of the Window in the range
    mutable size_t count;

    // Bounding box of the window in the range
    mutable Window box;

    void findBoundingBox() const;
    void sort();
    Itr findMid();

  public:
    BinaryPartitioner(Itr a, Itr b);

    std::unique_ptr<Node> findTree();
  };
}  // namespace rec

