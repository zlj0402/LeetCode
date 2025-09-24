"""
@brief: Leetcode_153_寻找旋转排序数组中的最小值
@link: https://leetcode.cn/problems/find-minimum-in-rotated-sorted-array/description/
@author: liangj.zhang
@date: 24/9/2025

@Difficulty: Medium

@Label: BinarySearch

@Retrospect(worthy 1 - 5): 4

@thoughts:
    + 【思路 1】：二分查找（旋转螺旋数组）
        - 旋转螺旋数组（以升序为例）：
            * 一段递增的数组（初始状态，或再次回到这个状态），从小到大；
            * 两段递增的数组（nums[0] > nums[-1] 必定成立，题目保证元素不重复）；

        - 最小值一定在 nums[-1] 的左侧；
        - 在区间 [0, n - 2] 内进行二分：
            * 若 nums[mid] < nums[-1]：
                - 右边界左移 r = mid - 1
                - 右侧染蓝色 (> target: nums[-1])
                - 单调性与经典二分不同，这里依赖分段单调 + 与末尾比较的条件
            * 若 nums[mid] >= nums[-1]：
                - 左边界右移 l = mid + 1
                - 左侧染红色 (< target: nums[-1])

    + 分析：
        - 时间复杂度：O(logn)
        - 空间复杂度：O(1)

    + rank:
        - 时间效率：0 ms, 击败 100%
        - 空间效率：17.63 MB, 击败 93.78%
"""

from typing import List


class Solution:
    def findMin(self, nums: List[int]) -> int:
        l, r = 0, nums.__len__() - 2
        while l <= r:
            mid = (l + r) // 2
            if nums[mid] < nums[-1]:
                r = mid - 1
            else:
                l = mid + 1

        return nums[l]