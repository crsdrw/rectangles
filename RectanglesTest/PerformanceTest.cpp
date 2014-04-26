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
	TEST_CLASS(PerformanceTest)
	{
	public:
		
		TEST_METHOD(CreateRandomRectangles)
		{
      Vec canvas_size{ 1.0f, 1.0f };
      Vec min_size{ 0.1f, 0.1f };
      Vec max_size{ 0.4f, 0.4f };
      std::vector<Node> nodes = createRandomRectangles(canvas_size, 10000, min_size, max_size);
		}

	};
}