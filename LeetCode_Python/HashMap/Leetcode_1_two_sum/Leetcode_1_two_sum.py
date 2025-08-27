"""
@brief: Leetcode_1_two_sum
@link: https://leetcode.cn/problems/two-sum/description/
@author: liangj.zhang
@date: 27/8/2025

@Difficulty: Easy

@Label: HashMap

@Retrospect(worthy 1 - 5): 1

@thoughts:
    + 【思路 1】哈希思想
        边遍历，边加入 dict 当中，与 target 作差，看着差值是否在 dict 当中
        + 分析：
            + 时间复杂度：只遍历了一遍，可能还不用；O(n)
            + 空间复杂度：O(n)
        + rank:
            + 时间效率：0 ms, 击败 100%
            + 空间效率：18.65 MB, 击败 32.1%
"""

from typing import List


class Solution:
    def twoSum(self, nums: List[int], target: int) -> List[int]:
        s = {}
        res = []
        for i in range(len(nums)):
            if target - nums[i] in s:
                return [i, s[target - nums[i]]]
            s[nums[i]] = i