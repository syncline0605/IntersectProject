#include "pch.h"
#include "CppUnitTest.h"
#include "../src/Intersect.h"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(TestProjection1)
		{
			Line line1 = Line{ 1, 0, 1, 1 };
			Point point = Point{ 0, 0 };
			Point testpoint = getProjection(point, line1);
			Point realpoint = { 1, 0 };
			Assert::IsTrue(testpoint == realpoint);
		}

		TEST_METHOD(TestProjection2)
		{
			Line line1 = Line{ 0, 0, 0, 1 };
			Point point = Point{ 0, 0 };
			Point testpoint = getProjection(point, line1);
			Point realpoint = { 0, 0 };
			Assert::IsTrue(testpoint == realpoint);
		}
	};
}
