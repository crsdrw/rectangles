#include "stdafx.h"
#include "TestData.h"
#include <random>
#include "..\Rectangles\Node.h"
#include "..\Rectangles\Vec.h"

namespace RectanglesTest {
  using rec::Node;
  using rec::Vec;

  Node createTestTree() {
    Node root(Vec{ 0.0f, 0.0f }, Vec{ 1.0f, 1.0f });
    root.setFirst(Vec{0.6f, 0.5f}, Vec{ 0.4f, 0.5f });
    root.setSecond(Vec{ 0.0f, 0.0f }, Vec{ 0.2f, 0.3f });
    return root;
  }

  std::vector<Node> createRandomRectangles(Vec canvas_size, int number_of_rectangles, Vec min_size, Vec max_size) {
    //static std::random_device rd;
    static std::mt19937 rng(0);

    if (!(min_size < max_size))
      throw std::logic_error("min_size not smaller than max_size");

    if (!(max_size < canvas_size))
      throw std::logic_error("max_size not smaller than canvas_size");

    std::vector<Node> rectangles;
    std::normal_distribution<float> x_dist(0.0f, canvas_size.x - max_size.x);
    std::normal_distribution<float> y_dist(0.0f, canvas_size.y - max_size.y);
    std::normal_distribution<float> width_dist(min_size.x, max_size.x);
    std::normal_distribution<float> height_dist(min_size.y, max_size.y);
    for (int i = 0; i != number_of_rectangles; ++i) {
      Vec pos{ x_dist(rng), y_dist(rng) };
      Vec size{ width_dist(rng), y_dist(rng) };
      rectangles.emplace_back(pos, size);
    }
    return rectangles;
  }
}