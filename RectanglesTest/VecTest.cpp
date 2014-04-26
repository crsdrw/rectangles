#include "stdafx.h"
#include "CppUnitTest.h"
#include <type_traits>

#include "..\Rectangles\Vec.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using rec::Vec;

namespace RectanglesTest
{
  Vec a{ 0.5f, 0.5f };
  Vec b{ 0.6f, 0.7f };
  Vec c{ 0.4f, 0.6f };
  Vec d{ 0.6f, 0.4f };

	TEST_CLASS(VecTest)
	{
	public:		
		TEST_METHOD(TestIsPOD)
		{
      static_assert(std::is_pod<Vec>::value, "Vec is not a POD");
		}

    TEST_METHOD(TestGreaterOperatorSuccess)
    {
      Assert::IsTrue(b > a);
    }

    TEST_METHOD(TestGreaterOperatorFail1)
    {
      Assert::IsFalse(a > b);
    }

    TEST_METHOD(TestGreaterOperatorFail2)
    {
      Assert::IsFalse(a > a);
    }

    TEST_METHOD(TestGreaterOperatorFail3)
    {
      Assert::IsFalse(a > c);
    }

    TEST_METHOD(TestLesserOperatorSuccess)
    {
      Assert::IsTrue(a < b);
    }

    TEST_METHOD(TestLesserOperatorFail1)
    {
      Assert::IsTrue(b < a);
    }
    TEST_METHOD(TestLesserOperatorFail2)
    {
      Assert::IsTrue(b < b);
    }
    TEST_METHOD(TestLesserOperatorFail3)
    {
      Assert::IsTrue(c < a);
    }
	};
}