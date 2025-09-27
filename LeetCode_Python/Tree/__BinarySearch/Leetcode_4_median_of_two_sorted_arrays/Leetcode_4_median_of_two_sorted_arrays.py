"""
@brief: Leetcode_4_寻找两个正序数组的中位数
@link: https://leetcode.cn/problems/median-of-two-sorted-arrays/description/
@author: liangj.zhang
@date: 27/9/2025

@Difficulty: Hard

@Label: Binary Search, Two Pointers

@Retrospect(worthy 1 - 5): 5

@thoughts:
    这题可以用双指针，且先理解双指针，更容易理解二分的条件；
    不过双指针的做法是 O(n)，不满足题目的 O(log n) 要求；
    两种做法都是看题解的，双指针的做法秒懂，二分其次。

    + 【思路 1】：双指针
        - 这次没写，留以后写。

    + 【思路 2】：二分查找
        - 求最后一个满足 snums[smid] <= lnums[lmid + 1] 的位置。
        - 示例：
            [-1, -2]
            [ 8,  9, 10]
            总共 5 个数，让前半部分长度达到 (m + n + 1) // 2，
            在总长度为奇数时，让左边多一个数。
        - snums 和 lnums 的划分组合示例：
            * s: 前 0 个，l: 前 3 个
            * s: 前 1 个，l: 前 2 个   => nums[0] < nums[1 + 1] => -1 < 9
            * s: 前 2 个，l: 前 1 个   => nums[1] < nums[0 + 1] => -2 < 8
            虽然有多个满足条件的情况，但只有 idx = 1 时是 snums 中最后一个满足的位置。

    + 分析：
        - 时间复杂度：O(log n)
        - 空间复杂度：O(1)

    + rank:
        * 时间效率：0 ms, 击败 100%
        * 空间效率：17.64 MB, 击败 96.24%
"""

from typing import List

import math

class Solution:
    def findMedianSortedArrays(self, nums1: List[int], nums2: List[int]) -> float:
        snums = nums1 if len(nums1) <= len(nums2) else nums2
        lnums = nums2 if len(nums1) <= len(nums2) else nums1
        slen, llen = snums.__len__(), lnums.__len__()

        half = (slen + llen + 1) // 2
        l, r = 0, slen - 1
        smid = lmid = 0
        while l <= r:
            smid = (l + r) // 2
            lmid = half - (smid + 1) - 1
            if snums[smid] <= lnums[lmid + 1]:
                l = smid + 1
            else:
                r = smid - 1
        smid = r
        lmid = half - (smid + 1) - 1

        sleft = -math.inf if smid == -1 else snums[smid]
        sright = math.inf if smid + 1 >= slen else snums[smid + 1]
        lleft = -math.inf if lmid == -1 else lnums[lmid]
        lright = math.inf if lmid + 1 >= llen else lnums[lmid + 1]
        left_max = max(sleft, lleft)
        right_min = min(sright, lright)
        
        return left_max * 1.0 if (slen + llen) % 2 else (left_max + right_min) / 2