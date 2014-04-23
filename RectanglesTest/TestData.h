#pragma once

#include <vector>

namespace rec {
  struct Vec;
  class Node;
}

namespace RectanglesTest {
  rec::Node createTestTree();
  std::vector<rec::Node> createRandomRectangles(rec::Vec canvas_size, int number_of_rectangles, rec::Vec min_size, rec::Vec max_size);
}