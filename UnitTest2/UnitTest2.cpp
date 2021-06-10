#include "pch.h"
#include "CppUnitTest.h"
#include "../Lab2/haffman.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest2
{
	TEST_CLASS(UnitTest2)
	{
	public:
		haffman hff;
		TEST_METHOD(TestMethod1)
		{
			std::string input_expr = "zz bbb g yyyy q aaaaa";
			hff.parser(input_expr);
			List list = hff.get_nodes();
			Assert::IsTrue(list[0]->weight == 1);
			Assert::IsTrue(list[1]->weight == 1);
			Assert::IsTrue(list[2]->weight == 2);
			Assert::IsTrue(list[3]->weight == 3);
			Assert::IsTrue(list[4]->weight == 4);
			Assert::IsTrue(list[5]->weight == 4);
			Assert::IsTrue(list[6]->weight == 5);
		}

		TEST_METHOD(TestMethod2)
		{
			std::string input_expr = "privet";
			hff.parser(input_expr);
			List list = hff.get_nodes();
			Assert::IsTrue(list[0]->weight == 1);
			Assert::IsTrue(list[1]->weight == 1);
			Assert::IsTrue(list[2]->weight == 1);
			Assert::IsTrue(list[3]->weight == 1);
			Assert::IsTrue(list[4]->weight == 1);
			Assert::IsTrue(list[5]->weight == 1);
		}
	};
}
