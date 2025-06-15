//
// Created by liangj.zhang on 14/6/2025
// 
// Difficulty: Hard
// 
// Label: Sort、SlidngWindow
// 
// 思路：
// 【1】. 
//	每次求窗口大小内的最大值，我还是首先想到 快排的变式 O(n)，但是这里不能打乱原数组的顺序，我们需要额外固定的空间，每次复制一次；
//	窗口大小 k, 数组长度为 n，遍历多少次：O(n - k)
//  每次需要拷贝窗口内数据的 index：O(k)
//  每次再加上一次快排：O(k)
//  时间复杂度：O((n - k) * (k + K))) == O((n - k) * k)
//	通常（自以为），n - k 和 k 中有一个可以认为是常数，但是，这就像小学的思考题，给一个长度 n 的线，怎么围起来，面积最大，当然是正方形，此时这道题是 O(1/4 * n^2)
//	最糟糕的情况，依然是 O(n^2)
// 
//	我的优化是，记录窗口内，最大值的下标，所以要使用 IndexQuickSort，按下标排序，得最大值的下标；
//	最大值，没出局时，进来一个数，只用跟这个数比较一下就行了；
//	最大值，出局时，就重新 IndexQuickSort 一下；
// 
//  -- 2025/6/14 18:21: 可悲的是，好好的写的这个，第 46/51 个 Case 超时；
// 
//  【2】. 让我想想索引大顶堆怎么样
//  窗口大小为 m，每次插入数据 O(logm)，每次移除数据 O(logm)，得到当前 top 数据 O(1)
//  n 个数据，总时间效率为：n * O(logm)
//  真是可行呢；T_T （迟一些再写吧，累了）
//  结束了--------------------也是以单例模式，写的大顶堆，其实也能复用为小顶堆；
//  也正如我分析的，时间复杂度为 O(nlogn)
//  rank:
//      时间效率：72 ms, 23.77%
//      空间效率：134.12MB, 击败 93%
//  ps: 最大的收获是，手写了一个从 0 开始 index 的，可复用的索引堆；
// 
// 看了题解，只看了前两个题解，还有 O(n) 时间复杂度的：
//  + 优先队列 O(nlogn)，也就是堆了，虽然时间略慢一点点，但是代码量少，下次也写一遍；
//  + 单调栈 O(n)，这个也要写一遍；
//

#include "SortTestHelper.h"
#include "IndexHeapSolution.h"
#include "IndexHeapSolution2.h"
#include "IndexQuickSortSolution.h"
#include<vector>
#include<iostream>
using std::cout;
using std::endl;
using std::vector;
using std::swap;



int main() {

    int n = 15;

    int k = 7;

    //vector<int> nums2 = vector<int>(arr1, arr1 + n);
    //vector<int> nums = { 11, 0, 2, 14, 2, 13, 3, 10, 13, 0 ,2, 7, 10, 11, 6 };
     //vector<int> nums = { 1,3,-1,-3,5,3,6,7 };
    vector<int> nums = { -6,-10,-7,-1,-9,9,-8,-4,10,-5,2,9,0,-7,7,4,-2,-10,8,7 };
    for (auto& e : nums)
        cout << e << " ";
    cout << endl;

    vector<int> ret = (new zlj_kth_iqs::Solution())->maxSlidingWindow(nums, k);
    for (auto& e : ret)
        cout << e << " ";
    cout << endl;


    //vector<int> nums2 = { 1,3,-1,-3,5,3,6,7 };
    ret = (new zlj_heap::Solution())->maxSlidingWindow(nums, k);
    for (auto& e : ret)
        cout << e << " ";
    cout << endl;

    ret = (new zlj_heap2::Solution())->maxSlidingWindow(nums, k);
    for (auto& e : ret)
        cout << e << " ";
    cout << endl;
}