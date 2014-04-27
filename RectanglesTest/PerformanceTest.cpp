#include "stdafx.h"
#include "CppUnitTest.h"
#include "..\Rectangles\Node.h"
#include "..\Rectangles\Vec.h"
#include "TestData.h"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using rec::Node;
using rec::Vec;


namespace RectanglesTest
{
  std::vector<Node> create10kRandomRectangles() {
    Vec canvas_size{ 1.0f, 1.0f };
    Vec min_size{ 0.1f, 0.1f };
    Vec max_size{ 0.4f, 0.4f };
    return createRandomRectangles(canvas_size, 10000, min_size, max_size);
  }

	TEST_CLASS(PerformanceTest)
	{

	public:

		TEST_METHOD(CreateRandomRectangles)
		{
      std::vector<Node> nodes = create10kRandomRectangles();
      Assert::AreEqual((size_t)10000u, nodes.size());
		}
	};
}