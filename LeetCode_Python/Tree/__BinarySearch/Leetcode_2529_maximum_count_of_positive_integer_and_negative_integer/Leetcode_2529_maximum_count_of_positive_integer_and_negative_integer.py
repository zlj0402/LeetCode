"""
@brief: Leetcode_2529_正整数和负整数的最大计数
@link: https://leetcode.cn/problems/maximum-count-of-positive-integer-and-negative-integer/description/
@author: liangj.zhang
@date: 15/9/2025

@Difficulty: Easy

@Label: Binary Search

@Retrospect(worthy 1 - 5): 2

@thoughts:
    + 【思路 1】：二分查找 lower_bound
        + 求 < 0 和 > 0 的问题，得到下标，就能知道正负数长度个数；
        + < 0: lower_bound(0) - 1
        + > 0: lower_bound(0 + 1)

        + 分析：
            + 时间复杂度：O(logn)
            + 空间复杂度：O(1)

        + rank:
            + 时间效率：0 ms, 击败 100%
            + 空间效率：20.93 MB, 击败 95.72%
"""

from typing import List


class Solution:
    def lower_bound(self, nums: List[int], target: int) -> int:
        left, right = 0, len(nums) - 1
        while left <= right:
            mid = left + (right - left) // 2
            if nums[mid] < target:
                left = mid + 1
            else:
                right = mid - 1
        return left
    
    # < 0 and > 0 问题
    # lower_bound 是解决 >= 问题；
    # 整数数组前提，lower_bound 同样能转化解决 < target and > target and <= target 问题
    # < 0 -> lower_bound(nums, target) - 1
    # > 0 -> lower_bound(nums, target + 1)
    def maximumCount(self, nums: List[int]) -> int:
        neg = self.lower_bound(nums, 0)
        pos = len(nums) - self.lower_bound(nums, 1)
        return max(neg, pos)
