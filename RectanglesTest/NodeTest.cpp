#include "stdafx.h"
#include "CppUnitTest.h"
#include "..\Rectangles\Node.h"
#include "..\Rectangles\NodePrint.h"
#include "..\Rectangles\TestData.h"
#include "..\Rectangles\BinaryPartitioner.h"
#include <iostream>
#include <fstream>


using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using rec::Node;
using rec::Vec;
using rec::Window;

namespace {
  void compareStreams(std::istream& expected, std::istream& actual) {
    std::string expected_line, actual_line;
    while (expected.good() && actual.good()) {
      std::getline(expected, expected_line);
      std::getline(actual, actual_line);
      Assert::AreEqual(expected_line, actual_line);
    }
  }

  std::vector<Window> create100RandomRectangles() {
    Window canvas{ { 0.0f, 0.0f }, { 1.0f, 1.0f } };
    Window range_of_sizes{ { 0.1f, 0.1f }, { 0.3f, 0.3f } };
    return createRandomRectangles(canvas, 100, range_of_sizes);
  }

  std::unique_ptr<Node> createTreeOf100() {
    auto rectangles = create100RandomRectangles();
    rec::BinaryPartitioner bp(rectangles.begin(), rectangles.end());
    return bp.findTree();
  }
}

namespace RectanglesTest
{
  TEST_CLASS(NodeTest)
  {
  public:

    TEST_METHOD(CreateNode)
    {
      Node root(Window{ { 0.0f, 0.0f }, { 1.0f, 1.0f } });
    }

    TEST_METHOD(CreateNodeWithLeaves)
    {
      Node root = rec::createSimpleTree();

      const std::vector<Window> leaves1 = root.findIntersectingLeaves(Vec{ 0.5f, 0.5f });
      Assert::AreEqual(0u, leaves1.size());

      const std::vector<Window> leaves2 = root.findIntersectingLeaves(Vec{ 0.7f, 0.8f });
      Assert::AreEqual(1u, leaves2.size());
      Assert::IsTrue(rec::areAlmostEqual(Window{ { 0.6f, 0.5f }, { 0.4f, 0.5f } }, leaves2[0], 1e-20f));
    }

    TEST_METHOD(FindLeaves)
    {
      auto root = rec::createSimpleTree();

      std::vector<Window> leaves = root.findLeaves();
      Assert::AreEqual(2u, leaves.size());
    }

    TEST_METHOD(TestPrint)
    {
      //std::ofstream stream("../TestPrintGold.svg");
      //Assert::IsTrue(stream.is_open());

      std::stringstream stream;
      auto root = rec::createSimpleTree();

      print(root, stream);

      std::ifstream file("../TestPrintGold.svg");

      compareStreams(file, stream);
    }

    TEST_METHOD(TestPrint100)
    {
      std::ofstream stream("../TestPrint100Gold.svg");
      Assert::IsTrue(stream.is_open());

      //std::stringstream stream;
      auto root = createTreeOf100();

      print(*root, stream);
    }
  };
}
