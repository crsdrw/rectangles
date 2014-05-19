#include "stdafx.h"
#include <vector>
#include <iostream>
#include "../Rectangles/Window.h"
#include "../Rectangles/Node.h"
#include "../Rectangles/TestData.h"
#include "../Rectangles/BinaryPartitioner.h"

namespace {
  using rec::Window;

  std::vector<Window> create1MRandomRectangles() {
    Window canvas{ { 0.0f, 0.0f }, { 1.0f, 1.0f } };
    Window range_of_sizes{ { 0.1f, 0.1f }, { 0.3f, 0.3f } };
    return rec::createRandomRectangles(canvas, 1000000, range_of_sizes);
  }

  void create10kTree() {
    auto rectangles = create1MRandomRectangles();
    rec::BinaryPartitioner bp(rectangles.begin(), rectangles.end());
    auto node = bp.findTree();
    std::cout << "Found tree" << std::endl;
  }
}

int main()
{
  create10kTree();
}

