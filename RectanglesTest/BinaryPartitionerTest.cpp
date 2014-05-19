#include "stdafx.h"
#include "CppUnitTest.h"
#include "../Rectangles/Vec.h"
#include "../Rectangles/Window.h"
#include "../Rectangles/BinaryPartitioner.h"
#include "../Rectangles/Node.h"
#include "TestData.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using rec::Window;
using rec::BinaryPartitioner;
using rec::Vec;

namespace RectanglesTest
{

	TEST_CLASS(BinaryPartitionerTest)
	{
	public:
		
		TEST_METHOD(TestPartitionEmptyVector)
		{
      auto empty_vector = std::vector < Window > {};
      BinaryPartitioner bp(empty_vector.begin(), empty_vector.end());
      auto node = bp.findTree();
      Assert::IsTrue(node == nullptr);
		}

    TEST_METHOD(TestPartitionVectorOfOne)
    {
      auto vector_of_one = std::vector < Window > {{{0.0f, 0.0f}, {1.0f, 1.0f}}};
      BinaryPartitioner bp(vector_of_one.begin(), vector_of_one.end());
      auto node = bp.findTree();
      Assert::IsTrue(node->isLeaf());
      auto window = node->getWindow();
      Window expected{ { 0.0f, 0.0f }, { 1.0f, 1.0f } };
      Assert::IsTrue(areAlmostEqual(expected, window, 1e-20f));
    }

    TEST_METHOD(TestPartitionVectorSimpleTree)
    {
      auto simple_list_rectangles = createSimpleListRectangles();
      BinaryPartitioner bp(simple_list_rectangles.begin(), simple_list_rectangles.end());
      auto node = bp.findTree();
      Assert::IsFalse(node->isLeaf());
    }
	};
}