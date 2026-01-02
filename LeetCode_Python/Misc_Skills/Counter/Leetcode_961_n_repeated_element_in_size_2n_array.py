"""
@breif: 在长度 2N 的数组中找出重复 N 次的元素
@link: https://leetcode.cn/problems/n-repeated-element-in-size-2n-array/description/?envType=daily-question&envId=2026-01-02
@author: liangj.zhang
@date: 2/1/2026

@Difficulty: so Easy

@Label: HashMap

@Retrospect(worthy 1 - 5): 1

@thoughts:
 + 【思路 1】：HashMap
     除了一个重复的元素，其他元素都不会重复...
     挣他个 10 积分

     + 分析：
         + 时间复杂度：O(n)
         + 空间复杂度：O(n)
     + rank:
         + 时间效率：0 ms, 击败 100%
         + 空间效率：18.23 MB, 击败 95.91%
"""

class Solution:
    def repeatedNTimes(self, nums: List[int]) -> int:
        s = set()
        for e in nums:
            if e in s:
                return e
            else:
                s.add(e)
        return nums[0]