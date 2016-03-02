#include "stdafx.h"
#include "CppUnitTest.h"
///////////////////////////////////////
#include <iostream>
#include <sstream>
//////////////////////////////
#include "sortdata.h"
////////////////////////////////////////
using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace infodata;
////////////////////////////////////////////////////////////////
namespace UnitTestSort
{		
	TEST_CLASS(UnitTestSort)
	{
	public:
		
		TEST_METHOD(TestQuickSort0)
		{
			// TODO: Your test code here
			size_t n = 10;
			int data[10] = { 3,0,1,8,7,2,5,4,9,6 };
			SortData<int> oSort(n, &(data[0]));
			int nRet = oSort.quicksort().get();
			std::wstringstream os;
			os << oSort;
			std::wstring s = os.str();
			Logger::WriteMessage(s.c_str());
		} // TestQuickSort0
	};
}