"""
@brief: Leetcode_243_最小化数组中的最大值
@link: https://leetcode.cn/problems/minimize-maximum-of-array/description/
@author: liangj.zhang
@date: 21/9/2025

@Difficulty: Medium

@Label: Binary Search, Prefix Sum & Greedy

@Retrospect(worthy 1 - 5): 4

@thoughts:
    + 【思路 1】：二分查找（二分猜答案）
        - 自己没写出来，以为从后往前比较平均值，就能得到答案，并不行；
        - 看了题解的前面，我就知道了；自己取平均值，只是一种取值；
        - 把 min(nums) <= limit <= max(nums) 作为二分的范围，每一次的 mid，都从后往前摊，
          nums[i] 高于 limit 的（要加上 extra），就移给下一个；

        - 灵神题解：
            把 nums[i] 想象成一个大小为 nums[i] 的积木堆，
            我们可以把一个积木移动到左边相邻的积木堆中。
            进一步地，多出的积木并不是只能移动一次，而是可以多次向左移动，
            从 i 移动到 i−1，再移动到 i−2，依此类推。

        - 分析：
            时间复杂度：O(n * logU), U = max(nums) - min(nums)
            空间复杂度：O(1)

        - rank:
            时间效率：522 ms, 击败 69.04%
            空间效率：27.17 MB, 击败 79.97%

    + 【思路 2】：前缀和 & 贪心算法；（留以后写，不然都没意识到用的是贪心）
"""

from typing import List


class Solution:
    def minimizeArrayValue(self, nums: List[int]) -> int:
        size = len(nums)
        l, r = min(nums), max(nums)

        while l <= r:
            mid = (l + r) // 2
            extra = 0

            for i in range(size - 1, -1, -1):
                if nums[i] + extra > mid:
                    extra = nums[i] + extra - mid
                else:
                    extra = 0
            
            if extra:
                l = mid + 1
            else:
                r = mid - 1

        return l