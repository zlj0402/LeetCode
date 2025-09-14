/**
 * @brief: Leetcode_34_在排序数组中查找元素的第一个和最后一个位置
 * @link: https://leetcode.cn/problems/find-first-and-last-position-of-element-in-sorted-array/description/
 * @author: liangj.zhang
 * @date: 14/9/2025
 * 
 * @Difficulty: Medium
 * 
 * @Label: Binary Search
 * 
 * @Retrospect(worthy 1 - 5): 4
 * 
 * @thoughts:
 *      + condition: 有序，非递减整数数组；
 * 
 *      + 【思路 1】：lower_bound & upper_bound
 *          + lower_bound: 返回第一个 >= target 的位置 idx1；
 *          + upper_bound: 返回的是第一个 > target 的位置 idx2；
 *              + 结合 lower_bound 返回值，判断是否有 target 后，upper_bound 的返回值 idx2, - 1 就是最后出现的位置；
 *                  + 是否有 target:
 *                      + 如果数组所有元素都比 target 小，那么 lower_bound 返回的 left 是最后一个元素后面的位置；
 *                      1. 在 left != nums.size() 的情况（也即，在数组中有比 target 大的值），再判断 nums[idx1] 是否 == target，
 *                      2. 不等，则说明数组中，也没有 target；
 *                      + 上述，两点则是判断有无 target 的条件；
 *          + ps:
 *              + 其实，在有整数为条件的题目，我们可以不用实现 upper_bound；
 *              + lower_bound 解决的是 >= 的问题，其它三种问题 >, <, <= 都可以由 lower_bound 求解；当然前提是元素都为整数的前提下，
 *                  + > target: 转换为 lower_bound(nums, target + 1)，求 >= target + 1, 即等价于 > target；
 *                  + < target: 转换为 lower_bound(nums, target) - 1
 *                  + <= target: > target 求取 idx 之后，idx - 1
 *          + 分析：
 *              + 时间复杂度：O(logn)
 *              + 空间复杂度：O(1)
 * 
 *          + rank:
 *              + 时间效率：0 ms, 击败 100%
 *              + 空间效率：17.18 MB, 击败 73.08%
 */

#include <vector>
#include <iostream>
using std::cout;
using std::endl;
using std::vector;

class Solution {

private:
    // >= target, the first position of >= target
    static int lower_bound(vector<int>& nums, int target);

    // > target, the first postion of > target
    static int upper_bound(vector<int>& nums, int target);

public:
    vector<int> searchRange(vector<int>& nums, int target) {
        
        int first_pos = lower_bound(nums, target);
        if (first_pos == nums.size() || (nums[first_pos] != target))
            return {-1, -1};
        int sec_pos = upper_bound(nums, target) - 1;

        return {first_pos, sec_pos};
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
    
    return left;    // if nums[n - 1] < target, left -> n: equal to length of nums[]
}

int Solution::upper_bound(vector<int>& nums, int target) {

    int left(0), right(nums.size() - 1);
    while (left <= right) {

        int mid = left + (right - left) / 2;
        if (nums[mid] > target)
            right = mid - 1;
        else
            left = mid + 1;
    }
    
    return left;    // if nums[n - 1] < target, left -> n: equal to length of nums[]
}