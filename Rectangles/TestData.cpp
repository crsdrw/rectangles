#include "stdafx.h"
#include "TestData.h"
#include <random>
#include "Node.h"

namespace rec {
  Node createSimpleTree() {
    Node root(Window{ { 0.0f, 0.0f }, { 1.0f, 1.0f } });
    root.attachFirst(std::unique_ptr<Node>(new Node(Window{ { 0.6f, 0.5f }, { 0.4f, 0.5f } })));
    root.attachSecond(std::unique_ptr<Node>(new Node(Window{ { 0.0f, 0.0f }, { 0.2f, 0.3f } })));
    return root;
  }

  std::vector<Window> createSimpleListRectangles() {
    Window window1{ { 0.6f, 0.5f }, { 0.4f, 0.5f } };
    Window window2{ { 0.0f, 0.0f }, { 0.2f, 0.3f } };
    return std::vector < Window > {window1, window2};
  }

  std::vector<Vec> createRandomPoints(Window canvas, int number_of_points) {
    static std::mt19937 rng(0);

    Vec canvas_max = getMax(canvas);
    std::vector<Vec> points;

    std::uniform_real_distribution<float> x_dist(canvas.pos.x, canvas_max.x);
    std::uniform_real_distribution<float> y_dist(canvas.pos.y, canvas_max.y);
    for (int i = 0; i != number_of_points; ++i)
      points.emplace_back(Vec{ x_dist(rng), y_dist(rng) });

    return points;
  }

  std::vector<Window> createRandomRectangles(Window canvas, int number_of_rectangles, Window range_of_sizes) {
    //static std::random_device rd;
    static std::mt19937 rng(0);

    Vec max_size = getMax(range_of_sizes);
    Vec min_size = range_of_sizes.pos;
    Vec canvas_max = getMax(canvas);

    if (!( max_size < canvas.size))
      throw std::logic_error("max_size not smaller than canvas_size");

    std::vector<Window> rectangles;
    std::uniform_real_distribution<float> x_dist(canvas.pos.x, canvas_max.x - max_size.x);
    std::uniform_real_distribution<float> y_dist(canvas.pos.y, canvas_max.y - max_size.y);
    std::uniform_real_distribution<float> width_dist(min_size.x, max_size.x);
    std::uniform_real_distribution<float> height_dist(min_size.y, max_size.y);
    for (int i = 0; i != number_of_rectangles; ++i) {
      Vec pos{ x_dist(rng), y_dist(rng) };
      Vec size{ width_dist(rng), y_dist(rng) };
      rectangles.emplace_back(Window{ pos, size });
    }
    return rectangles;
  }
}  // namespace rec