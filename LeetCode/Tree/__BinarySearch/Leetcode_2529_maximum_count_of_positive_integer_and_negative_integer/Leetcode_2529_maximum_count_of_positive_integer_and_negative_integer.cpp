/**
 * @brief: Leetcode_2529_正整数和负整数的最大计数
 * @link: https://leetcode.cn/problems/maximum-count-of-positive-integer-and-negative-integer/description/
 * @author: liangj.zhang
 * @date: 15/9/2025
 * 
 * @Difficulty: Easy
 * 
 * @Label: Binary Search
 * 
 * @Retrospect(worthy 1 - 5): 2
 * 
 * @thoughts:
 *  + 【思路 1】：二分查找 lower_bound
 *      + 求 < 0  和 > 0 的问题, 得到下标，就是能知道正负数长度个数；
 *      + < 0: lower_bound(0) - 1
 *      + > 0: lower_bound(0 + 1)
 *      
 *      + 分析：
 *          + 时间复杂度：O(logn)
 *          + 空间复杂度：O(1)
 * 
 *      + rank:
 *          + 时间效率：0 ms, 击败 100%
 *          + 空间效率：20.93 MB, 击败 95.72%
 */

#include <iostream>
#include <vector>
using std::cout;
using std::endl;
using std::vector;

// 【思路 1】：二分查找 lower_bound
class Solution {

private:
    static int lower_bound(vector<int>& nums, int target);

public:
    // 求 < 0  和 > 0 的问题, 得到下标，就是能知道正负数长度个数；
    // < 0: lower_bound(0) - 1
    // > 0: lower_bound(0 + 1)
    int maximumCount(vector<int>& nums) {
        
        int neg = lower_bound(nums, 0); // - 1 + 1
        int pos = nums.size() - lower_bound(nums, 1);

        return std::max(neg, pos);
    }
};

int Solution::lower_bound(vector<int>& nums, int target) {

    int left(0), right(nums.size() - 1);
    while (left <= right) {

        int mid = left + (right - left) / 2;
        if (nums[mid] < target)
            left = mid + 1;
        else
            right = mid - 1;
    }
    return left;
}