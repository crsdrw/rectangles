#include "stdafx.h"
#include "CppUnitTest.h"
#include "..\Rectangles\Node.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using rec::Node;
using rec::Vec;

namespace {
  Node createTestTree() {
    Node root(Vec(0.0f, 0.0f), Vec(1.0f, 1.0f));
    root.setFirst(Vec(0.6f, 0.5f), Vec(0.4f, 0.5f));
    root.setSecond(Vec(0.0f, 0.0f), Vec(0.2f, 0.3f));
    return root;
  }
}

namespace Microsoft{
  namespace VisualStudio {
    namespace CppUnitTestFramework {
      template<> static std::wstring ToString<Vec>(const Vec& t) { std::wstringstream s;	s << t.
        x << "," << t.y; return s.str(); }
    }
  }
}

namespace QuadtreeTest
{
  TEST_CLASS(NodeTest)
  {
  public:

    TEST_METHOD(CreateNode)
    {
      Node root(Vec(0.0f, 0.0f), Vec(1.0f, 1.0f));
    }

    TEST_METHOD(CreateNodeWithLeaves)
    {
      Node root = createTestTree();

      const std::vector<const Node*> leaves1 = root.findIntersectingLeaves(Vec(0.5f, 0.5f));
      Assert::AreEqual(0u, leaves1.size());

      const std::vector<const Node*> leaves2 = root.findIntersectingLeaves(Vec(0.7f, 0.8f));
      Assert::AreEqual(1u, leaves2.size());
      Assert::IsNotNull(leaves2[0]);
      Assert::AreEqual(Vec(0.6f, 0.5f), leaves2[0]->getPos());
    }

    TEST_METHOD(FindLeaves)
    {
      auto root = createTestTree();

      std::vector<const Node*> leaves = root.findLeaves();
      Assert::AreEqual(2u, leaves.size());
    }
  };
}