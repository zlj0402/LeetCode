"""
@brief: Leetcode_2563_统计公平数对的数目
@link: https://leetcode.cn/problems/count-the-number-of-fair-pairs/description/
@author: liangj.zhang
@date: 16/9/2025

@Difficulty: Medium

@Label: Binary Search、Three Pointers(Facing)、Two Pointer twice

@Retrospect(worthy 1 - 5): 4

@thoughts:
    + 【思路 1】：二分查找
        + lower_bound -> 解决的是 >= target
        + find >= lower - nums[i]
        + find <= upper - nums[i]

        + 分析：
            + 时间复杂度：排序 O(n log n) + 二分查找 O(log n) * n => O(n log n)，常数大
            + 空间复杂度：O(1)

        + rank:
            + 时间效率：259 ms, 击败 80.97%
            + 空间效率：31.40 MB, 击败 88.42%

    + 【思路 2】：相向三指针
        + 想找的，还是 lower - nums[i] 和 upper - nums[i] 的位置
        + >= lower - nums[i] 和 > upper - nums[i]
        + 题目：upper >= lower
        + 排序后的数组，随着 nums[i] 逐渐增大，lower - nums[i] 和 upper - nums[i] 都会减小
        + L 找到 >= lower - nums[i] 的位置；R 找到 > upper - nums[i] 的位置；
        + 下一次遍历，从上一次的指针位置开始往前，因为 [lower/upper] - nums[i] 是在不断减小的；
        + (i, R] 的范围，是能达成公平数对的范围；
            + L > i 时，[L, R]
            + L <= i 时，(i, R]
            + R <= i 时，循环可以结束了；

        + 分析：
            + 时间复杂度：排序 O(n log n) + 相向三指针 2 * O(n) => O(n log n)
            + 空间复杂度：O(1)

        + rank:
            + 时间效率：167 ms, 击败 87.77%
            + 空间效率：31.53 MB, 击败 45.86%
"""

from typing import List

import bisect

class Solution:
    def countFairPairs(self, nums: List[int], lower: int, upper: int) -> int:
        l = r = len(nums) - 1
        nums.sort()
        cnt = 0
        for i, x in enumerate(nums):
            # >= lower - nums[i]
            while l >= 0 and nums[l] >= lower - nums[i]:   # 直到 nums[l] < lower - nums[i]
                l -= 1
            # l += 1    # >= lower - nums[i] 的第一位
            # > upper - nums[i]
            while r >= 0 and nums[r] > upper - nums[i]:    # 直到 nums[r] <= upper - nums[i]
                r -= 1

            if r <= i: break

            cnt += r - max(l, i)
        return cnt

"""
class Solution:

    def countFairPairs(self, nums: List[int], lower: int, upper: int) -> int:
        
        nums.sort()
        size = len(nums)
        cnt = 0

        for i, x in enumerate(nums):
            if i == size - 1: break
            #l = bisect.bisect_left(nums, lower - x, i + 1, size)
            l = i + 1 if lower <= nums[i] + nums[i + 1] else bisect.bisect_left(nums, lower - x, i + 1, size)
            #r = bisect.bisect_right(nums, upper - x, i + 1, size)
            r = size if upper >= nums[i] + nums[-1] else bisect.bisect_right(nums, upper - x, i + 1, size)

            cnt += r - l

        return cnt
"""

def main():
    # nums = [1,7,9,2,5]
    nums = [-5,-7,-5,-7,-5]
    lower = -12
    upper = -12

    print(Solution().countFairPairs(nums, lower, upper))

if __name__ == "__main__":
    main()