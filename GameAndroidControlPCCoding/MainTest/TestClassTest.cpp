#include "TestClassTest.h"

namespace ShuangLong
{
	TestClassTest* TestClassTest::mpInstance = nullptr;

	TestClassTest::TestClassTest()
	{
		mpTestClass = new TestClass();
	}

	TestClassTest::~TestClassTest()
	{
	}

	void TestClassTest::Entry()
	{
		mpInstance = new TestClassTest();

		mpInstance->TestMethodTest();
	}

	void TestClassTest::TestMethodTest()
	{
		mpTestClass->TestMethod();
	}
}