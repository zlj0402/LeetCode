#pragma once
#ifndef SELECTIONSORT_SORTTESTHELPER_H
#define SELECTIONSORT_SORTTESTHELPER_H

#include <iostream>
#include <ctime>
#include <cassert>

using namespace std;

namespace SortTestHelper {

	// 生成有n个元素的随机数组，每个元素的随机范围为[rangeL, rangeR]
	int* generateRandomArray(int n, int rangeL, int rangeR) {

		assert(rangeL <= rangeR);
		int* arr = new int[n];
		srand(time(NULL));
		for (int i = 0; i < n; i++)
			arr[i] = rand() % (rangeR - rangeL + 1) + rangeL;
		return arr;
	}

	int* generateNearlyOrderedArray(int n, int swapTimes) {

		int* arr = new int[n];
		for (int i = 0; i < n; i++)
			arr[i] = i;
		srand(time(NULL));

		for (int i = 0; i < swapTimes; i++) {
			int posx = rand() % n;
			int posy = rand() % n;
			swap(arr[posx], arr[posy]);
		}

		return arr;
	}

	template <typename T>
	void printArray(T arr[], int n) {

		for (int i = 0; i < n; i++)
			cout << arr[i] << " ";
		cout << endl;

		return;
	}

	template <typename T>
	bool isSorted(T arr[], int n) {

		for (int i = 0; i < n - 1; i++)
			if (arr[i] > arr[i + 1])
				return false;

		return true;
	}

	template <typename T>
	void testSort(string sortName, void (*sort)(T[], int), T arr[], int n) {

		clock_t starttime = clock();
		sort(arr, n);
		clock_t endtime = clock();

		assert(isSorted(arr, n));
		// endtime - starttime是运行了多少个机器周期
		cout << sortName << " : " << double(endtime - starttime) / CLOCKS_PER_SEC << " s" << endl;

		return;
	}

	int* copyIntArray(int a[], int n) {

		int* arr = new int[n];
		copy(a, a + n, arr);	// 头指针，尾指针，目标的头指针

		return arr;
	}
}

#endif