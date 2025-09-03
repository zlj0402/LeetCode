"""
@brief: Leetcode_209_长度最小的子数组
@link: https://leetcode.cn/problems/minimum-size-subarray-sum/description/
@author: liangj.zhang
@date: 3/9/2025

@Difficulty: Medium

@Label: Sliding Window

@Retrospect(1 - 5): 3

@thoughts:
    + 【思路 1】：滑动窗口
        虽然是在刷题单阶段，但在视频讲解前，我就暂停了，先自己想了下；
        这题的滑动窗口（也是一种双指针），也是很容易想到的；

        + 分析：
            + 时间复杂度：l 和 r 最多都只遍历一遍数组的长度 => O(n)
            + 空间复杂度：不会随着数组长度的变化，自己使用的变量，不会有更多的空间占用 => O(1)
        
        + rank:
            + 时间效率：8 ms, 击败 84.34%
            + 空间效率：27.93 MB, 击败 8.84%
"""

from typing import List


class Solution:
    def minSubArrayLen(self, target: int, nums: List[int]) -> int:
        l = r = 0
        sum_ = 0
        size = len(nums)

        length = 0
        min_len = size + 1
        while r < size:
            sum_ += nums[r]
            r += 1
            length += 1

            while sum_ >= target:
                if length < min_len:
                    min_len = length
                sum_ -= nums[l]
                l += 1
                length -= 1
        
        return 0 if min_len == size + 1 else min_len