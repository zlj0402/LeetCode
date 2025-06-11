//
// Created by liangj.zhang on 11/6/2025
// 
// URL: https://leetcode.cn/problems/longest-consecutive-sequence/description
// 
// 思路：
//  【1】. 虽然题目要求了，要按 O(n) 的时间复杂度，但第一时间想到的是，排序之后，顺序的遍历一遍，相当于时间复杂度，还是 O(nlogn)
//      + 就当是练习手写快排了；
//      + 实际上，网页上 Cases 的时间效率，要比 O(n) 的要快；
//      + 而且是数据量，达到千万级别的，快排的方式，还是药比 【2】 hash 之后，枚举 + 删除/标记的方式要快；
//      + 特此为试验两种方式的差异，写了个测试用例，（这都成了，这题的最大收获，清晰的拆分了用例，像自己整理侯捷老师的 Test STL 库一样清晰）
// 
//  【2】. 是看了题解之后写的两种方式，其实是同一个意思；
//      + hash 之后，枚举 + 删除/标记的方式
//      + 将 nums 数组中的值，加入到 set 中，是一次 O(n)
//      + 枚举就是，当前值前后的数值遍历，没有就终止，不会多遍历；拿 删除 举证；
//      + 当次值遍历完成后，从 set 中删除这次遍历的值；所有值删除完，是一次 O(n)，所有值遍历到，也是 O(n)
//      + 3 次 O(n)，时间复杂度应当还是 O(n) 呀，为什么呢？
//      + chat 的解释是 hash 的隐藏代价是常数大，一次 find 的汇编指令可能有 20 条；具体见 Notion -- 算法与数据结构 -- Leetcode -- Hash -- Leetcode_128
// 
//  rank: 
//      【1】.
//          + 时间效率：39 ms, 击败 87.46%
//          + 空间效率：58.88 MB, 击败 90.45%
//      【2.2】.
//          + 时间效率：107 ms, 击败 36.49%
//          + 空间效率：90.13 MB, 击败 6.57%
//

#include <vector>
#include <iostream>
using std::cout;
using std::endl;
using std::vector;

#include "TestSortSolution.h"
#include "TestHashSolution.h"

#include "SortTestHelper.h"


int main() {

    // -8, -4, -3, -3, -3, -2, -1, 0, 0, 2, 5, 7
    //vector<int> nums = { -2,-3,-3,7,-3,0,5,0,-8,-4,-1,2 };
    //cout << (new Solution())->longestConsecutive(nums);

    int n = 10000000;
    int* arr = SortTestHelper::generateRandomArray(n, 0, n);
    //SortTestHelper::printArray(arr, n);

    //int n = 6;
    //int arr[] = { 100,4,200,1,3,2 };
    
    int* arr1 = SortTestHelper::copyIntArray(arr, n);
    int* arr2 = SortTestHelper::copyIntArray(arr, n);

    zlj01::test_sort_solution(vector<int>(arr1, arr1 + n));
    zlj02::test_hash_solution(vector<int>(arr2, arr2 + n));


    //delete[] arr;
    delete[] arr1;
    delete[] arr2;
}