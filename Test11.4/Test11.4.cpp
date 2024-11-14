#include "pch.h"
#include "CppUnitTest.h"
#include "../Lab11.4V2/Lab11.4.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Test114
{
	TEST_CLASS(Test114)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			istringstream input("\n"); // Імітація натискання Enter
			cin.rdbuf(input.rdbuf());  // Перенаправляємо стандартний вхід на симульований

			string fileName = getFileName();
			Assert::AreEqual(string("AVTO"), fileName, L"Default file name should be 'AVTO'");

		}
	};
}
