"""
@brief: Leetcode_16_3sum_closest
@link: https://leetcode.cn/problems/3sum-closest/description/
@author: liangj.zhang
@date: 26/8/2025

@Difficulty: Medium
    + 代码中 nums[i] + nums[j] + nums[k] < target, 以下描述中简写为 i + j + k < t
    + 较为难理解的地方在于：在有大于或小于（< t 或 > t）目标的过程中，都进行了比较和记录
    + 疑问：由于排序，是否存在被过滤的组合，比当前结果更接近目标？
        + 假设上一次变化的是 k：
            + 当前若 i + j + k > t：
                + 在此之前，idx k 之后的数，|i + j + >k| 只会更大（>k 表示比 nums[k] 大的值，因 k 指针移动被忽略）
            + 当前若 i + j + k < t：
                + 当前组合未忽略，pass
        + 假设上一次变化的是 j：
            + 当前若 i + j + k < t：
                + 在此之前，idx j 之前的数，|i + <j + k| 只会更大（<j 表示比 nums[j] 小的值，因 j 指针移动被忽略）
            + 当前若 i + j + k > t：
                + 当前组合未忽略，pass

@Label: Two Pointers(Facing)
@Retrospect(worthy 1 - 5): 3

@thoughts:
    + 思路 1：排序 + 双指针
        + 分析：
            + 时间复杂度：排序 O(nlogn) + 双指针 O(n^2) => O(n^2)
            + 空间复杂度：无额外申请与数组长度相关的空间 => O(1)
        + rank:
            + 时间效率：108 ms, 击败 79.26%
            + 空间效率：17.49 MB, 击败 82.6%
"""

from typing import List


class Solution:
    def __init__(self):
        self.abs_min = 0
        self.min_sum = 0

    def threeSumClosest(self, nums: List[int], target: int) -> int:
        nums.sort()
        size = len(nums)
        self.abs_min = 200001
        self.min_sum = 199999

        for i in range(size - 2):
            if i != 0 and nums[i] == nums[i - 1]: continue
            sum = nums[i] + nums[i + 1] + nums[i + 2]
            if sum > target and sum - target < self.abs_min:
                self.abs_min = sum - target
                self.min_sum = sum
                continue
            sum = nums[i] + nums[size - 2] + nums[size - 1]
            if sum < target and target - sum < self.abs_min:
                self.abs_min = target - sum
                self.min_sum = sum
                continue

            j = i + 1
            k = size - 1
            while j < k:
                sum = nums[i] + nums[j] + nums[k]
                if sum > target:
                    k -= 1
                    if sum - target < self.abs_min:
                        self.abs_min = sum - target
                        self.min_sum = sum
                elif sum < target:
                    j += 1
                    if target - sum < self.abs_min:
                        self.abs_min = target - sum
                        self.min_sum = sum
                else:
                    return target
        return self.min_sum


def main():
    target = 1
    nums = [-1,2,1,-4]

    print(Solution().threeSumClosest(nums, target))

if __name__ == "__main__":
    main()
