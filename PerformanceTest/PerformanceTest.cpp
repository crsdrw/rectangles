#include "stdafx.h"
#include <vector>
#include <iostream>
#include "../Rectangles/Window.h"
#include "../Rectangles/Node.h"
#include "../Rectangles/TestData.h"
#include "../Rectangles/BinaryPartitioner.h"

namespace {
  using rec::Window;
  using rec::Vec;
  using rec::Node;

  std::vector<Window> create1MRandomRectangles() {
    Window canvas{ { 0.0f, 0.0f }, { 1.0f, 1.0f } };
    Window range_of_sizes{ { 0.1f, 0.1f }, { 0.3f, 0.3f } };
    return rec::createRandomRectangles(canvas, 1000000, range_of_sizes);
  }

  std::unique_ptr<Node>
  create1MTree() {
    auto rectangles = create1MRandomRectangles();
    rec::BinaryPartitioner bp(rectangles.begin(), rectangles.end());
    return bp.findTree();
  }

  std::vector<Vec> create10RandomPoints() {
    Window canvas{ { 0.0f, 0.0f }, { 1.0f, 1.0f } };
    return createRandomPoints(canvas, 10);
  }

  void findIntersectionsIn1MTree() {
    auto node = create1MTree();
    auto points = create10RandomPoints();
    for (auto point : points) {
      auto intersecting_leaves = node->findIntersectingLeaves(point);
    }
  }
}

int main()
{
  //create1MRandomRectangles();
  //create1MTree();
  findIntersectionsIn1MTree();
}

