// ConsoleApplicationSort.cpp : définit le point d'entrée pour l'application console.
//

#include "stdafx.h"
////////////////////////
#include <cassert>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <future>
#include <memory>
////////////////////////////
typedef int DataType;
typedef int IndexType;
///////////////////////
const size_t n = 10;
DataType data[10] = { 3,0,1,8,7,2,5,4,9,6 };
//////////////////////////////
std::future<int> partition(const DataType *pData, IndexType *pIndex,
	const int left, const int right) {
	return std::async([pData, pIndex, left, right]()->int {
		int i = left, j = right;
		const DataType pivot = pData[pIndex[(left + right) / 2]];
		while (i <= j) {
			while (pData[pIndex[i]] < pivot) {
				i++;
			}// i
			while (pData[pIndex[j]] > pivot) {
				j--;
			}// j
			if (i < j) {
				const IndexType temp = pIndex[i];
				pIndex[i] = pIndex[j];
				pIndex[j] = temp;
			}
			if (i < right) {
				i++;
			}
			else {
				break;
			}
			if (j < left) {
				j--;
			}
			else {
				break;
			}
		}// while i <= j
		const bool b1 = (left < j);
		const bool b2 = (i < right);
		if (b1 && b2) {
			auto r1 = partition(pData, pIndex, left, j);
			auto r2 = partition(pData, pIndex, i, right);
			return (r1.get() + r2.get());
		}
		else if (b1) {
			return partition(pData, pIndex, left, j).get();
		}
		else if (b2) {
			return partition(pData, pIndex, i, right).get();
		}
		else {
			return 0;
		}
	});
}// partition
//////////////////////
int main()
{
	assert(n > 1);
	std::unique_ptr<IndexType> oIndex(new IndexType[n]);
	IndexType *pIndex = oIndex.get();
	assert(pIndex != nullptr);
	for (size_t i = 0; i < n; ++i) {
		pIndex[i] = (IndexType)i;
	}// i
	const DataType *pData = &(data[0]);
	/////////////////////////////////////
	int r = partition(pData, pIndex, (int)0, (int)(n - 1)).get();
	////////////////////////////////////
	for (size_t i = 0; i < n; ++i) {
		IndexType ii = pIndex[i];
		std::wcout << i << L"\t" << pData[i] << L"\t" << ii << L"\t" << pData[ii] << std::endl;
	}
	/////////////////////////////////////
	return 0;
}// main

