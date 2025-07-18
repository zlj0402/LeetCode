//
// Created by liangj.zhang on 13/4/2025 -- updated on 18/4/205
// Partially referenced from liuyubobobo's course on GitHub
// URL: https://github.com/liuyubobobo/Play-with-Algorithms/tree/master/02-Sorting-Basic/Course%20Code%20(C%2B%2B)
//

#ifndef SORTTESTHELPER_H
#define SORTTESTHELPER_H

#include <iostream>
#include <algorithm>
#include <string>
#include <ctime>
#include <cassert>
#include <string>
#include <map>

#define GEN_ARRAY_ASC(arr, n) \
    do { for (int i = 0; i < (n); i++) (arr)[i] = i; } while (0)

#define GEN_ARRAY_DESC(arr, n) \
    do { for (int i = 0; i < (n); i++) (arr)[i] = (n) - 1 - i; } while (0)

using namespace std;


namespace RandomNumbers {

    // 生成有n个元素的随机数组,每个元素的随机范围为[rangeL, rangeR]
    int* generateRandomArray(int n, int range_l, int range_r) {

        int* arr = new int[n];

        srand(time(NULL));
        for (int i = 0; i < n; i++)
            arr[i] = rand() % (range_r - range_l + 1) + range_l;
        return arr;
    }

    // 生成一个近乎有序的数组
    // 首先生成一个含有[0...n-1]的完全有序数组, 之后随机交换swapTimes对数据
    // swapTimes定义了数组的无序程度:
    // swapTimes == 0 时, 数组完全有序
    // swapTimes 越大, 数组越趋向于无序
    int* generateNearlyOrderedArray(int n, int swapTimes) {

        int* arr = new int[n];
        //for (int i = 0; i < n; i++)
        //    arr[i] = i;
        GEN_ARRAY_ASC(arr, n);

        srand(time(NULL));
        for (int i = 0; i < swapTimes; i++) {
            int posx = rand() % n;
            int posy = rand() % n;
            swap(arr[posx], arr[posy]);
        }

        return arr;
    }

    // 生成一个有序的数组 [0, n-1]
    int* generateOrderedArray(int n, bool ascending) {

        int* arr = new int[n];

        if (ascending)
            GEN_ARRAY_ASC(arr, n);
        else
            GEN_ARRAY_DESC(arr, n);

        return arr;
    }

    // 拷贝整型数组a中的所有元素到一个新的数组, 并返回新的数组
    template<typename T>
    int* copyIntArray(T a[], int n) {

        T* arr = new T[n];
        //* 在VS中, copy函数被认为是不安全的, 请大家手动写一遍for循环:)
        // 浅拷贝: 对于基本类型和不包含指针成员的类没有影响
        copy(a, a + n, arr);
        return arr;
    }

    // 打印arr数组的所有内容
    template<typename T>
    void printArray(T arr[], int n) {

        for (int i = 0; i < n; i++)
            cout << arr[i] << " ";
        cout << endl;

        return;
    }
}

#endif