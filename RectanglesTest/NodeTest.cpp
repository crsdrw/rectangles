#include "stdafx.h"
#include "CppUnitTest.h"
#include "..\Rectangles\Node.h"
#include "..\Rectangles\NodePrint.h"
#include "TestData.h"
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
      Node root = createSimpleTree();

      const std::vector<Window> leaves1 = root.findIntersectingLeaves(Vec{ 0.5f, 0.5f });
      Assert::AreEqual(0u, leaves1.size());

      const std::vector<Window> leaves2 = root.findIntersectingLeaves(Vec{ 0.7f, 0.8f });
      Assert::AreEqual(1u, leaves2.size());
      Assert::IsTrue(rec::areAlmostEqual(Window{ { 0.6f, 0.5f }, { 0.4f, 0.5f } }, leaves2[0], 1e-20f));
    }

    TEST_METHOD(FindLeaves)
    {
      auto root = createSimpleTree();

      std::vector<Window> leaves = root.findLeaves();
      Assert::AreEqual(2u, leaves.size());
    }

    TEST_METHOD(TestPrint)
    {
      //std::ofstream stream("../TestPrintGold.svg");
      //Assert::IsTrue(stream.is_open());

      std::stringstream stream;
      auto root = createSimpleTree();

      print(root, stream);

      std::ifstream file("../TestPrintGold.svg");

      compareStreams(file, stream);
    }
  };
}
