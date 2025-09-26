"""
@brief: Leetcode_162_寻找峰值
@link: https://leetcode.cn/problems/find-peak-element/description/
@author: liangj.zhang
@date: 23/9/2025

@Difficulty: Medium

@Label: Binary Search

@Retrospect(worthy 1 - 5): 3

@thoughts:
 + 【思路 1】：二分查找 -- 峰值 -- 红蓝染色
     看了灵神的视频：https://www.bilibili.com/video/BV1QK411d76w
     峰值这题，竟然也能用二分；
     还好这题，只用求任意一个峰顶的下标；

     只求得一个峰顶，左侧染红色，右侧染蓝色，染色，即是告诉自己不用再去考虑的部分；
     nums[mid] < nums[mid + 1] => 处于峰顶左侧（，mid 及 mid 左侧染红色，l = mid + 1
     else 即
     nums[mid] >= nums[mid + 1] => 处于峰顶，或者峰顶的右侧（，mid 及 mid 右侧染蓝色，r = mid -1

     + 分析：
         + 时间复杂度：O(logn)
         + 空间复杂度：O(1)
     + rank:
         + 时间效率：0 ms, 击败 100%
         + 空间效率：17.60 MB, 击败 51.84%
"""

from typing import List


class Solution:
    def findPeakElement(self, nums: List[int]) -> int:
        l, r = 0, len(nums) - 2
        while l <= r:
            mid = (l + r) // 2
            if nums[mid] < nums[mid + 1]:
                l = mid + 1
            else:
                r = mid - 1
        return l