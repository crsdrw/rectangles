#pragma once

#include <vector>

namespace rec {
  struct Window;
  class Node;
}

namespace RectanglesTest {
  rec::Node createSimpleTree();
  std::vector<rec::Window> createRandomRectangles(rec::Window canvas, int number_of_rectangles, rec::Window range_of_sizes);
  std::vector<rec::Window> createSimpleListRectangles();
}