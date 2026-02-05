"""
@brief: Leetcode_3379_转换数组
@link: https://leetcode.cn/problems/transformed-array/description
@author: liangj.zhang
@date: 5/2/2026

@Difficulty: Easy

@Lable: circular queue

@Retrospect(worthy 1 - 5): 2

@thoughts:
 + 【思路 1】：得到 新的坐标 是唯一的关键，然后弄清楚谁赋给谁；
     每日一题，赚 10 积分；
     ---
     新位置的值 nums[new_idx] 赋给 result[i]，i 是原下标；
     这题也是必须要开一个新的空间

     + 分析：
         + 时间复杂度：O(n)
         + 空间复杂度：O(n)
     + rank:
            + 时间效率：62 ms, 击败 61.54%
            + 空间效率：19.12 MB, 击败 7.69%
"""


from typing import List


class Solution:
    def constructTransformedArray(self, nums: List[int]) -> List[int]:
        len_ = nums.__len__()
        result = [0] * len_
        for i in range(len_):
            step = nums[i] if nums[i] > 0 else (nums[i] % len_) + len_
            result[i] = nums[(i + step) % len_]
        return result