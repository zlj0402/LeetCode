"""
@brief: Leetcode_34_在排序数组中查找元素的第一个和最后一个位置
@link: https://leetcode.cn/problems/find-first-and-last-position-of-element-in-sorted-array/description/
@author: liangj.zhang
@date: 14/9/2025

@Difficulty: Medium

@Label: Binary Search

@Retrospect(worthy 1 - 5): 4

@thoughts:
    + condition: 有序，非递减整数数组；

    + 【思路 1】：lower_bound & upper_bound
        + lower_bound: 返回第一个 >= target 的位置 idx1；
        + upper_bound: 返回的是第一个 > target 的位置 idx2；
            + 结合 lower_bound 返回值，判断是否有 target 后，upper_bound 的返回值 idx2 - 1 就是最后出现的位置；
                + 是否有 target:
                    + 如果数组所有元素都比 target 小，那么 lower_bound 返回的 left 是最后一个元素后面的位置；
                    1. 在 left != len(nums) 的情况（也即，在数组中有比 target 大的值），再判断 nums[idx1] 是否 == target，
                    2. 不等，则说明数组中，也没有 target；
                + 上述两点则是判断有无 target 的条件；
        + ps:
            + 其实，在有整数为条件的题目，我们可以不用实现 upper_bound；
            + lower_bound 解决的是 >= 的问题，其它三种问题 >, <, <= 都可以由 lower_bound 求解；当然前提是元素都为整数的前提下，
                + > target: 转换为 lower_bound(nums, target + 1)，求 >= target + 1, 即等价于 > target；
                + < target: 转换为 lower_bound(nums, target) - 1
                + <= target: > target 求取 idx 之后，idx - 1

        + python 这里没有使用 upper_bound，用了转换的 lower_bound 求解；

        + 分析：
            + 时间复杂度：O(logn)
            + 空间复杂度：O(1)

        + rank:
            + 时间效率：0 ms, 击败 100%
            + 空间效率：18.68 MB, 击败 68.22%
"""

from typing import List


class Solution:
    # 要求 nums 是非递减的，即 nums[i] <= nums[i + 1]
    # 返回最小的满足 nums[i] >= target 的 i
    # 如果不存在，返回 len(nums)
    # [L, R]
    def lower_bound(self, nums: List[int], target: int) -> int:
        left = 0
        right = len(nums) - 1   # 闭区间 [left, right]
        while left <= right:    # 区间不为空
            mid = left + (right - left) // 2
            if nums[mid] < target:
                left = mid + 1  # [mid + 1, right]
            else:
                right = mid - 1 # [left, mid - 1]
        return left
    
    def searchRange(self, nums: List[int], target: int) -> List[int]:
        first_pos = self.lower_bound(nums, target)
        if first_pos == len(nums) or nums[first_pos] != target:
            return (-1, -1)
        sec_pos = self.lower_bound(nums, target + 1) - 1
        return (first_pos, sec_pos)