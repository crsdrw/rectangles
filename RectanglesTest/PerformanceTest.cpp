#include "stdafx.h"
#include "CppUnitTest.h"
#include <vector>
#include "..\Rectangles\Node.h"
#include "..\Rectangles\Vec.h"
#include "..\Rectangles\TestData.h"
#include "..\Rectangles\BinaryPartitioner.h"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using rec::Node;
using rec::Vec;
using rec::Window;


namespace RectanglesTest
{
  std::vector<Window> create10kRandomRectangles() {
    Window canvas{ { 0.0f, 0.0f }, { 1.0f, 1.0f } };
    Window range_of_sizes{ { 0.1f, 0.1f }, { 0.3f, 0.3f } };
    return createRandomRectangles(canvas, 10000, range_of_sizes);
  }

	TEST_CLASS(PerformanceTest)
	{

	public:

		TEST_METHOD(CreateRandomRectangles)
		{
      auto rectangles = create10kRandomRectangles();
      Assert::AreEqual((size_t)10000u, rectangles.size());
		}

    TEST_METHOD(CreateTreeFromRandomRectangles)
    {
      auto rectangles = create10kRandomRectangles();
      rec::BinaryPartitioner bp(rectangles.begin(),rectangles.end());
      auto node = bp.findTree();
      Assert::IsTrue(node != nullptr);
    }
	};
}