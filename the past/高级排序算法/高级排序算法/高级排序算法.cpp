// 高级排序算法.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include "SortTestHelper.h"
using namespace std;

// 将arr[l...mid]和arr[mid+1...r]两部分进行归并
template <typename T>
void __merge(T arr[], int l, int mid, int r) {

    //T aux[r - l + 1];
    T* aux = new int[r - l + 1];
    for (int i = l; i <= r; i++)
        aux[i - l] = arr[i];

    int i = l, j = mid + 1;
    for (int k = l; k <= r; k++) {

        if (i > mid) {
            arr[k] = aux[j - l];
            j++;
        }
        else if (j > r) {
            arr[k] = aux[i - l];
            i++;
        }
        else if (aux[i - l] < aux[j - l]) {
            arr[k] = aux[i - l];
            i++;
        }
        else {
            arr[k] = aux[j - l];
            j++;
        }
    }

    delete[] aux;
}

// 递归使用归并排序，对arr[l...r]的范围进行排序
template <typename T>
void __mergeSort(T arr[], int l, int r) {

    if (l >= r)
        return;

    int mid = (l + r) / 2;  // l和r非常大时，可能产生溢出
    __mergeSort(arr, l, mid);
    __mergeSort(arr, mid + 1, r);
    __merge(arr, l, mid, r);
}

// 归并排序算法
template <typename T>
void mergeSort(T arr[], int n) {

    __mergeSort(arr, 0, n - 1);
}

// 插入排序算法
template <typename T>
void insertionSort(T arr[], int n) {

    for (int i = 1; i < n; i++) {

        // 寻找元素arr[i]合适的插入位置
        T e = arr[i];
        int j;
        for (j = i; j > 0 && arr[j - 1] > e; j--)
            arr[j] = arr[j - 1];
        arr[j] = e;
    }

    return;
}

// 插入排序算法（重载）
template <typename T>
void insertionSort(T arr[], int l, int r) {

    for (int i = l + 1; i <= r; i++) {

        T e = arr[i];
        int j;
        for (j = i; j > l && arr[j - 1] > e; j--)
            arr[j] = arr[j - 1];
        arr[j] = e;
    }
}

// 希尔排序，bobo老师
template<typename T>
void shellSort(T arr[], int n) {

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

// 将arr[l...mid]和arr[mid+1...r]两部分进行归并
template <typename T>
void __merge2(T arr[], int l, int mid, int r) {

    //T aux[r - l + 1];
    T* aux = new int[r - l + 1];
    for (int i = l; i <= r; i++)
        aux[i - l] = arr[i];

    int i = l, j = mid + 1;
    for (int k = l; k <= r; k++) {

        if (i > mid) {
            arr[k] = aux[j - l];
            j++;
        }
        else if (j > r) {
            arr[k] = aux[i - l];
            i++;
        }
        else if (aux[i - l] < aux[j - l]) {
            arr[k] = aux[i - l];
            i++;
        }
        else {
            arr[k] = aux[j - l];
            j++;
        }
    }

    delete[] aux;
}

// 递归使用归并排序，对arr[l...r]的范围进行排序
template <typename T>
void __mergeSort2(T arr[], int l, int r) {

    //if (l >= r)
    //    return;
    if (r - l <= 15) {
        insertionSort(arr, l, r);
        return;
    }

    int mid = (l + r) / 2;  // l和r非常大时，可能产生溢出
    __mergeSort2(arr, l, mid);
    __mergeSort2(arr, mid + 1, r);
    if(arr[mid] > arr[mid + 1])
        __merge2(arr, l, mid, r);
}

// 归并排序算法
template <typename T>
void mergeSort2(T arr[], int n) {

    __mergeSort2(arr, 0, n - 1);
}

int main(){
    
    int n = 100000;

    cout << "Test for Random Array, size = " << n << ", random range[0, " << n << "]" << endl;
    int* arr = SortTestHelper::generateRandomArray(n, 0, n);
    int* arr2 = SortTestHelper::copyIntArray(arr, n);
    int* arr3 = SortTestHelper::copyIntArray(arr, n);
    int* arr4 = SortTestHelper::copyIntArray(arr, n);

    SortTestHelper::testSort("Insertion Sort", insertionSort, arr, n);
    SortTestHelper::testSort("Merge Sort", mergeSort, arr2, n);
    SortTestHelper::testSort("Merge Sort2", mergeSort2, arr3, n);
    SortTestHelper::testSort("Shell Sort", shellSort, arr4, n);

    delete[] arr;
    delete[] arr2;
    delete[] arr3;

    cout << endl;

    int swapTimes = 100;
    cout << "Test for Random Nearly Ordered Array, size = " << n << ", swap time = " << swapTimes << endl;
    arr = SortTestHelper::generateNearlyOrderedArray(n, swapTimes);
    arr2 = SortTestHelper::copyIntArray(arr, n);
    arr3 = SortTestHelper::copyIntArray(arr, n);
    arr4 = SortTestHelper::copyIntArray(arr, n);

    SortTestHelper::testSort("Insertion Sort", insertionSort, arr, n);
    SortTestHelper::testSort("Merge Sort", mergeSort, arr2, n);
    SortTestHelper::testSort("Merge Sort2", mergeSort2, arr3, n);
    SortTestHelper::testSort("Shell Sort", shellSort, arr4, n);

    delete[] arr;
    delete[] arr2;
    delete[] arr3;

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
