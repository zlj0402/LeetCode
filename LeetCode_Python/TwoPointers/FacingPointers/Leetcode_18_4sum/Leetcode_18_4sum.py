"""
@brief: Leetcode_18_四数之和
@link: https://leetcode.cn/problems/4sum/description/
@author: liangj.zhang
@date: 27/8/2025

@Difficulty: Medium
@Label: Two Pointers(Facing)
@Retrospect(worthy 1 - 5): 2

@thoughts:
    + 【思路 1】排序 + 相向双指针 + 优化剪枝
        思路和三数之和类似，只是外层多套了一层枚举，时间复杂度为 O(n^3)
        + 分析：
            + 时间复杂度：排序 O(nlogn) + 嵌套的相向双指针 O(n^3) ==> O(n^3)
            + 空间复杂度：未申请额外空间 O(1)
        + rank:
            + 时间效率：0 ms, 击败 100%
            + 空间效率：17.09 MB, 击败 60.48%

    + 【思路 1.2】递归实现（也是 k 数之和的模板）
        本质上仍然是上面的思路，但通过递归实现，5、6 数之和也可以沿用该模板。
        优化点：
            + 若前 k 个数之和 > target，直接 break
            + 若最后 k - 1 个数加上当前固定的数仍 < target，说明枚举继续后移可能改变结果
            + 但若前 k 个数 > target，这种情况无法改变
        + 分析：
            + 时间复杂度：排序 O(nlogn) + 嵌套的相向双指针 O(n^3) ==> O(n^3)
            + 空间复杂度：至少递归 n - k - 1 次 ==> O(n)
        + rank:
            + 时间效率：3 ms, 击败 90.18%
            + 空间效率：17.68 MB, 击败 5.28%
"""

from typing import List


class Solution:
    def fourSum(self, nums: List[int], target: int) -> List[List[int]]:

        res = []
        nums.sort()
        size = len(nums)
        for i in range(size - 3):
            if i > 0 and nums[i] == nums[i - 1]: continue
            if nums[i] + nums[i + 1] + nums[i + 2] + nums[i + 3] > target: break
            if nums[i] + nums[-3] + nums[-2] + nums[-1] < target: continue
            for j in range(i + 1, size - 2):
                if j > i + 1 and nums[j] == nums[j - 1]: continue
                if nums[i] + nums[j] + nums[j + 1] + nums[j + 2] > target: break
                if nums[i] + nums[j] + nums[-2] + nums[-1] < target: continue
                m = j + 1
                n = size - 1
                while m < n:
                    sum_ = nums[i] + nums[j] + nums[m] + nums[n]
                    if sum_ < target:
                        m += 1
                    elif sum_ > target:
                        n -= 1
                    else:
                        res.append([nums[i], nums[j], nums[m], nums[n]])
                        while m < n and nums[m + 1] == nums[m]: m += 1
                        while m < n and nums[n - 1] == nums[n]: n -= 1
                        m += 1
                        n -= 1
        return res