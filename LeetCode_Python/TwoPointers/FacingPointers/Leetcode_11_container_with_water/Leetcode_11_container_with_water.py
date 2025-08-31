"""
@brief: Leetcode_11_Container_With_Most_Water
@link: https://leetcode.cn/problems/container-with-most-water/description
@author: liangj.zhang
@date: 30/8/2025

@Difficulty: Medium

@thoughts:
    + 【思路1】：
        + 使用双指针：
            + 体会过程，不然你可能会有疑问：错过的哪些可能？不会有更大值的可能吗？
            + 指针从两端开始：
                + 在一个面积求得之后，将矮的一边往里移动，寻找比当前更高的边
                + 这样才能有可能得到更大的面积（因为宽度在变小，指针向内移动）
            + 不管这次移动后的结果是否大于 `max_area`，你都需要继续查找，直到找到更大的面积。
        + python 这次是回顾灵神的基础教学，再写的一遍；
        + 分析：
            + 时间复杂度：O(n)
            + 空间复杂度：O(1)
        + rank:
            + 时间效率：55 ms, 击败 95.2%
            + 空间效率：27.95 MB, 击败 52.35%
"""

from typing import List


class Solution:
    def maxArea(self, height: List[int]) -> int:
        
        max_area = 0
        i = 0
        j = len(height) - 1
        while i < j:
            area = min(height[i], height[j]) * (j - i)
            if area > max_area:
                max_area = area
            if (height[i] <= height[j]):
                i += 1
                while(i < j and height[i] <= height[i - 1]): i += 1
            else:
                j -= 1
                while(i < j and height[j] <= height[j + 1]): j -= 1
        return max_area
