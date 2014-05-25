#pragma once

#include <vector>

namespace rec {
  struct Vec;
  struct Window;
  class Node;

  Node createSimpleTree();
  std::vector<rec::Vec> createRandomPoints(Window canvas, int number_of_points);
  std::vector<rec::Window> createRandomRectangles(Window canvas, int number_of_rectangles, Window range_of_sizes);
  std::vector<rec::Window> createSimpleListRectangles();
}