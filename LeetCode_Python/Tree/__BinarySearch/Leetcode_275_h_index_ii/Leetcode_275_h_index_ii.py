"""
@brief: Leetcode_275_H指数_II
@link: https://leetcode.cn/problems/h-index-ii/description/
@author: liangj.zhang
@date: 17/9/2025

@Difficulty: Medium

@Label: Binary Search on Predicate

@Retrospect(worthy 1 - 5): 4

@thoughts:
    + 【思路 1】：二分查找（判定型）
        + 满足 nums[idx] >= size - idx => >= idx 的位置都可以不考虑了，红蓝染色法可以给右边图上蓝色了，
          因为 nums[>idx] 更大，size - >idx 更小，肯定满足这个关系
        + 就好像一个 k = -1 的直线 y1（size - idx），与一个不下降的曲线 y2 (nums[idx])，作差 y2 - y1
        + x = 0 处是差值最小的，idx 最大的时候，差值最大 => y2 - y1 具有单调性

        + 分析：
            + 时间复杂度：O(log n)
            + 空间复杂度：O(1)

        + rank:
            + 时间效率：0 ms, 击败 100%
            + 空间效率：22.45 MB, 击败 85.72%
"""

from typing import List


class Solution:
    def hIndex(self, citations: List[int]) -> int:
        size = len(citations)
        l, r = 0, size - 1
        while l <= r:
            mid = (l + r) // 2
            if citations[r] >= size - mid:
                r = mid - 1
            else:
                l = mid + 1
        return size - l