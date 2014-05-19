#include "stdafx.h"
#include "CppUnitTest.h"
#include "../Rectangles/Vec.h"
#include "../Rectangles/Window.h"
#include "../Rectangles/BinaryPartitioner.h"
#include "../Rectangles/Node.h"
#include "TestData.h"
#include "../Rectangles/StringTools.h"

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
      auto root = bp.findTree();

      Window expected_box{ { 0.0f, 0.0f }, { 1.0f, 1.0f } };
      Window actual_box = root->getWindow();

      Assert::IsTrue(areAlmostEqual(expected_box, actual_box, 1e-20f));
      
      Assert::IsFalse(root->isLeaf());
      auto root_box = root->getWindow();
      Window expected_root_box{ { 0.0f, 0.0f }, { 1.0f, 1.0f } };
      // TODO
      Assert::IsTrue(areAlmostEqual(expected_root_box, root_box, 1e-20f));
      
      auto leaves = root->findLeaves();      
      Assert::AreEqual(2u, leaves.size());
 
      Window expected_sub_window1{ { 0.0f, 0.0f }, { 0.2f, 0.3f } };
      Window actual_sub_window1 = leaves[0];
      Assert::IsTrue(areAlmostEqual(expected_sub_window1, actual_sub_window1, 1e-20f));

      Window expected_sub_window2{ { 0.6f, 0.5f }, { 0.4f, 0.5f } };
      Window actual_sub_window2 = leaves[1];
      Assert::IsTrue(areAlmostEqual(expected_sub_window2, actual_sub_window2, 1e-20f));

    } 
	};
}