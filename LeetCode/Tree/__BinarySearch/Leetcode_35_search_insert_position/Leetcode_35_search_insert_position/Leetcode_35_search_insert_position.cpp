//
// Created by liangj.zhang on 14/6/2025
// 
// URL: https://leetcode.cn/problems/search-insert-position/description
// 
// Difficulty: Easy
// 
// Label: Binary Search
// 
// description:
//  【1】.
//      + 虽然简单，但边界不好琢磨啊
//      + >>> 没找到的时候，不管是 l 还是 r，都会往 target 方向靠近一步，就是合适插入的地方；<<<
//      + 这种方式是调试出来的；
// 
//  rank: great
//      + 时间效率：0 ms, 击败 100%
//      + 空间效率：13.46 MB, 击败 36.63%
// 
//  【2】. floor 思想改进：
//      + floor 本身是，找到的话，返回找到的位置；
//                     没有找到的话，返回的是前一个位置（前一个 < target 的元素的位置；升序情况的话）
//      + 我们只要在没找到时，返回 floor 原本结果 +1 就行了；
// 
//  rank: great
//      + 时间效率：0 ms, 击败 100%
//      + 空间效率：13.38 MB, 击败 58.61%
//

#include <vector>
#include <iostream>
using std::cout;
using std::endl;
using std::vector;

// 【2】
class Solution {
public:
    int searchInsert(vector<int>& nums, int target) {

        int l = 0, r = nums.size() - 1;
        int res = -1;
        while (l <= r) {

            int mid = l + (r - l) / 2;
            if (nums[mid] <= target) {

                res = mid;
                l = mid + 1;
            }
            else {
                r = mid - 1;
            }
        }

        return res;
    }
};

// 【1】
/*
class Solution {
public:
    int searchInsert(vector<int>& nums, int target) {

        int l, r, mid, res;
        l = 0;
        r = nums.size() - 1;
        res = -1;

        while (l <= r) {

            mid = (r - l) / 2 + l;
            if (nums[mid] < target) {
                l = mid + 1;
            }
            else if (nums[mid] > target) {
                r = mid - 1;
            }
            else {

                res = mid;
                break;
            }
        }

        // 没找到，那么 l 当前的位置就是适当插入的位置
        return res == -1 ? l : res;
    }
};*/


int main() {

    int target = -1;
    vector<int> nums = { 1,3,5,6 };
    cout << (new Solution())->searchInsert(nums, target);
}