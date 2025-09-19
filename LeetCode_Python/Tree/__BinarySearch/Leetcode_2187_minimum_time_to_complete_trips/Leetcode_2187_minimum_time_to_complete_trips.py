"""
@brief: Leetcode_2187_完成旅途的最少时间
@link: https://leetcode.cn/problems/minimum-time-to-complete-trips/description/
@author: liangj.zhang
@date: 19/9/2025

@Difficulty: Medium

@Label: Binary Search

@Retrospect(worthy 1 - 5): 3

@thoughts:
    + 【思路 1】：二分查找（判定型）
        + 时间 1 份 1 份的增加，cntTrips 也是单调变大，直到刚好 >= totalTrips；
        + 所以，可以使用二分查找；
        + 确定查找范围：
            + 可以把 time 数组中，除 min_time 的其他元素当成无穷大来看，合理的范围就能确定；
            + 二分查找的范围，我觉得应该是 [min(time), min(time) * totalTrips]

        + 分析：
            + 时间复杂度：O(n * log(min_time * totalTrips))
            + 空间复杂度：O(1)

        + rank:
            + 时间效率：583 ms, 击败 96.63%
            + 空间效率：30.66 MB, 击败 9.75%
"""

from typing import List


class Solution:
    def minimumTime(self, time: List[int], totalTrips: int) -> int:
        l = min(time)
        r = l * totalTrips

        while l <= r:
            mid = (l + r) >> 1
            if sum([mid // e for e in time]) < totalTrips:
                l = mid + 1
            else:
                r = mid - 1
        return l