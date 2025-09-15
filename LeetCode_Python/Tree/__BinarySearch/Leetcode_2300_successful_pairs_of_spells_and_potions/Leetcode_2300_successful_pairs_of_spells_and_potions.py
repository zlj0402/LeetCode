"""
@brief: Leetcode_2300_咒语和药水的成功对数
@link: https://leetcode.cn/problems/successful-pairs-of-spells-and-potions/description/
@author: liangj.zhang
@date: 15/9/2025

@Difficulty: Medium

@Label: Sort && Binary Search、Counter && Suffix Sum

@Retrospect(worthy 1 -5): 3

@thoughts:
    + 【思路 1】：排序 + 二分查找
        success / potion 向上取整的结果，就是 lower_bound 参数中的 target；对每个元素都要进行；
        当然 potions，在一开始就要进行升序排序；

        + ps: 学习到了正整数运算，达到 ceil 效果的 skill：
            + >>> (Dividend - 1) / Divisor + 1 <<<
            + (被除数 - 1) / 除数 + 1

        + 分析：
            + 时间复杂度：排序 O(m log m); m -> len(potions); 对每个 spell 进行二分查找 -> O(n log m); n -> len(spells)
                + 总结：O((n + m) log m)
            + 空间复杂度：O(1)，忽略排序的栈开销；

        + rank:
            + 时间效率：455ms, 击败 63.51%
            + 空间效率：40.57 MB, 击败 93.59%

    + 【思路 2】：Counter && 后缀和
        在题解中看了，能够理解，留着以后做吧；-- 15/9/2025
"""

from typing import List


class Solution:
    def lower_bound(self, nums: List[int], target: int) -> int:
        left, right = 0, len(nums) - 1
        while left <= right:
            mid = (left + right) // 2
            if nums[mid] < target:
                left = mid + 1
            else:
                right = mid - 1
        return left
    
    def successfulPairs(self, spells: List[int], potions: List[int], success: int) -> List[int]:

        potions.sort()

        s_size = len(spells)
        p_size = len(potions)
        res = [0] * s_size

        for i in range(s_size):
            quo = (success - 1) // spells[i] + 1
            if quo > potions[-1]:
                continue
            idx = self.lower_bound(potions, quo)
            res[i] = p_size - idx

        return res