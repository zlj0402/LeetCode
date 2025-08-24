"""
@brief: Leetcode_167_两数之和II-输入有序数组
@link: https://leetcode.cn/problems/two-sum-ii-input-array-is-sorted/description/
@author: liangj.zhang
@date: 24/8/2025

@Difficulty: Medium
@Label: Two Pointers(Facing)
@Retrospect(Worthy 0 - 5): 2

@thoughts:
    + 用相向的双指针，这题非常 easy；

    + 分析：
        + 时间复杂度：相向遍历，最多遍历一整个数组 => O(n)
        + 空间复杂度：没有额外的使用数组长度的栈空间，也没有申请动态空间 => O(1)
    
    + rank:
        + 时间效率：0 ms, 击败 100%
        + 空间效率：19.03 MB, 击败 83.72%
"""

from typing import List


class Solution:

    def twoSum(self, numbers: List[int], target: int) -> List[int]:
        
        i = 0
        j = len(numbers) - 1

        while i < j:
            sum = numbers[i] + numbers[j]
            if sum < target:
                i = i + 1
            elif sum > target:
                j = j - 1
            else:
                return [i + 1, j + 1]
                
        return []