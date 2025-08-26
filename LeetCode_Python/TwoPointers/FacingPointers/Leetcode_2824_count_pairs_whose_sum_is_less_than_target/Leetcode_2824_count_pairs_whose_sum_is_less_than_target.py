"""
@brief: Leetcode_2824_count_pairs_whose_sum_is_less_than_target
@link: https://leetcode.cn/problems/count-pairs-whose-sum-is-less-than-target/description/
@author: liangj.zhang
@date: 25/8/2025
  
@Difficulty: Easy
  
@Label: Two Pointers(Facing)、Sort
  
@Retrospect(Worthy 0 - 5): 2 

@thoughts:
    + 思路 1：排序 + 双指针
        + 分析：
            + 时间复杂度：O(n^2)
            + 空间复杂度：O(1)
        + rank：
            + 时间效率：0 ms, 击败 100%
            + 空间复杂度：17.7 MB, 击败 17.64%
"""

from typing import List


class Solution:
    def countPairs(self, nums: List[int], target: int) -> int:
        nums.sort()

        count = 0
        i = 0
        j = len(nums) - 1
        while i < j:
            while (i < j and nums[i] + nums[j] >= target): j = j - 1
            count += j - i
            i += 1

        return count
        