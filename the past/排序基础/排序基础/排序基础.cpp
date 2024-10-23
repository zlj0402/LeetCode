// 排序基础.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <algorithm>
#include "Student.h"
#include "SortTestHelper.h"
using namespace std;

// 选择排序算法
template <typename T>
void selectionSort(T arr[], int n) {

    int temp = 0;
    for (int i = 0; i < n; i++) {

        // 寻找[i,n)区间中的最小值
        int minIndex = i;
        for (int j = i + 1; j < n; j++)
            if (arr[j] < arr[minIndex])
                minIndex = j;

        swap(arr[minIndex], arr[i]);
    }
}

// 插入排序算法
template <typename T>
void insertionSort(T arr[], int n) {

    for (int i = 1; i < n; i++) {

        // 寻找元素arr[i]合适的插入位置
        T e = arr[i];
        int j = i;
        for (; j > 0 && arr[j - 1] > e; j--)
            arr[j] = arr[j - 1];
        arr[j] = e;
    }
            
    return;
}

// 冒泡排序算法1，自己
template <class T>
void bubbleSort(T arr[], int n) {

    // 相邻两个元素，大的往后排；每遍，当前最大值都在最后
    for (int i = 0; i < n; i++) {

        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1])
                swap(arr[j], arr[j + 1]);
        }
    }
}

// 冒泡排序2，bobo老师第一版
template<typename T>
void bubbleSort2(T arr[], int n) {

    bool swapped;

    do {
        swapped = false;
        for (int i = 1; i < n; i++)
            if (arr[i - 1] > arr[i]) {
                swap(arr[i - 1], arr[i]);
                swapped = true;

            }

        // 优化, 每一趟Bubble Sort都将最大的元素放在了最后的位置
        // 所以下一次排序, 最后的元素可以不再考虑
        n--;

    } while (swapped);
}

// 冒泡排序算法3，bobo老师第二版
template <class T>
void bubbleSort3(T arr[], int n) {

    // bobo老师的第二版排序
    int newn;
    do {
        newn = 0;
        for (int i = 1; i < n; i++) {
            if (arr[i - 1] > arr[i]) {
                swap(arr[i - 1], arr[i]);
                newn = i;
            }
        }
        n = newn;
    } while (newn > 0);
}

//希尔排序算法，自己
template <class T>
void shellSort(T arr[], int n) {

    int gap = n / 2;
    int j;
    int temp;
    while (gap > 0) {
        for (int i = gap; i < n; i++) {
            temp = arr[i];
            j = i - gap;
            while (j >= 0 and arr[j] > temp) {
                arr[j + gap] = arr[j];
                j = j - gap;
            }
            arr[j + gap] = temp;
        }
        gap = gap / 2;
    }
}

// 希尔排序，bobo老师
template<typename T>
void shellSort2(T arr[], int n) {

    // 计算 increment sequence: 1, 4, 13, 40, 121, 364, 1093...
    int h = 1;
    while (h < n / 3)
        h = 3 * h + 1;

    while (h >= 1) {

        // h-sort the array
        for (int i = h; i < n; i++) {

            // 对 arr[i], arr[i-h], arr[i-2*h], arr[i-3*h]... 使用插入排序
            T e = arr[i];
            int j;
            for (j = i; j >= h && e < arr[j - h]; j -= h)
                arr[j] = arr[j - h];
            arr[j] = e;
        }

        h /= 3;
    }
}

int main(){
    int n = 100000;

    int* arr = SortTestHelper::generateRandomArray(n, 0, n);
    int* arr2 = SortTestHelper::copyIntArray(arr, n);
    int* arr3 = SortTestHelper::copyIntArray(arr, n);
    int* arr4 = SortTestHelper::copyIntArray(arr, n);
    int* arr5 = SortTestHelper::copyIntArray(arr, n);
    int* arr6 = SortTestHelper::copyIntArray(arr, n);
    int* arr7 = SortTestHelper::copyIntArray(arr, n);

    SortTestHelper::testSort("Selection Sort", selectionSort, arr, n);
    SortTestHelper::testSort("Insertion Sort", insertionSort, arr2, n);
    SortTestHelper::testSort("Bubble Sort", bubbleSort, arr3, n);
    SortTestHelper::testSort("Bubble Sort2", bubbleSort2, arr4, n);
    SortTestHelper::testSort("Bubble Sort3", bubbleSort3, arr5, n);
    SortTestHelper::testSort("Shell Sort", shellSort, arr6, n);
    SortTestHelper::testSort("Shell Sort2", shellSort2, arr7, n);

    int swapTimes = 100;

    cout << "Test for nNearly ordered array, size = " << n << ", swap time = " << swapTimes << endl;

    arr = SortTestHelper::generateNearlyOrderedArray(n, swapTimes);
    arr2 = SortTestHelper::copyIntArray(arr, n);
    arr3 = SortTestHelper::copyIntArray(arr, n);
    arr4 = SortTestHelper::copyIntArray(arr, n);
    arr5 = SortTestHelper::copyIntArray(arr, n);
    arr6 = SortTestHelper::copyIntArray(arr, n);
    arr7 = SortTestHelper::copyIntArray(arr, n);

    SortTestHelper::testSort("Selection Sort", selectionSort, arr, n);
    SortTestHelper::testSort("Insertion Sort", insertionSort, arr2, n);
    SortTestHelper::testSort("Bubble Sort", bubbleSort, arr3, n);
    SortTestHelper::testSort("Bubble Sort2", bubbleSort2, arr4, n);
    SortTestHelper::testSort("Bubble Sort3", bubbleSort3, arr5, n);
    SortTestHelper::testSort("Shell Sort", shellSort, arr6, n);
    SortTestHelper::testSort("Shell Sort2", shellSort2, arr7, n);

    delete[] arr;
    delete[] arr2;
    delete[] arr3;
    delete[] arr4;
    delete[] arr5;
    delete[] arr6;
    delete[] arr7;
    cout << endl;

    //float b[] = { 4.4, 3.3, 2.2, 1.1};
    //selectionSort(b, 4);
    //for (int i = 0; i < 4; i++)
    //    cout << b[i] << " ";
    //cout << endl;

    //string c[4] = {"D", "C", "B", "A"};
    //selectionSort(c, 4);
    //for (int i = 0; i < 4; i++)
    //    cout << c[i] << " ";
    //cout << endl;

    //Student d[4] = { {"D", 90}, {"C", 100}, {"B", 95}, {"A", 95} };
    //selectionSort(d, 4);
    //for (int i = 0; i < 4; i++)
    //    cout << d[i];
    //cout << endl;

    return 0;
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
