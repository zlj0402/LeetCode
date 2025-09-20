"""
@brief: Leetcode_2861_最大合金数
@link: https://leetcode.cn/problems/maximum-number-of-alloys/description/
@author: liangj.zhang
@date: 20/9/2025

@Difficulty: Medium

@Label: Binary Search

@Retrospect(worthy 1 - 5): 4

@thoughts:
    + 【思路 1】：二分查找
        + 假设 k 是生产一份金属的消耗，那么就有公式 (k 就是代码中的 com_cost)：
            + k * 金属个数 - 原有的、用到的储量 <= budget
                + 具有单调性
            + 这个公式就能用来进行二分查找
        + 下一个问题，是怎么确定二分查找的范围，即金属个数范围；
            + 下手前，在纸上画了画；得到的结论是
                + 左值：stock[x, y, z, ...] composition[x0, y0, z0, ...]
                    + 个数是 x/x0 y/y0 z/z0 ... 中的最小值，通过原来的库存就能生产的金属数量，不需要 budget 的部分；
                    + 现在想想它也应该加上 budget / k；
                + 右值：x/x0 y/y0 z/z0 ... 中的最大值，通过原来的库存最多能生产的；然后加上 budget / k；
                    + 调试的时候，发现特殊的情况，composition[] 中合金的构造只需要一种金属；
                    + 这种时候不能忽略掉余数，以及 budget / k 的余数，两个余数之和，可能再多构成一份合金；
        + 分析：
            + 时间复杂度：O(k * n) + O(k * log(len(stock)))
            + 空间复杂度：O(1)

        + rank:
            + 时间效率：80 ms, 击败 97.77%
            + 空间效率：18.03 MB, 击败 69.38%
"""

from typing import List


class Solution:
    def maxNumberOfAlloys(self, n: int, k: int, budget: int, composition: List[List[int]], stock: List[int], cost: List[int]) -> int:
        max_cnt = 0
        min_range = 100000001

        for i in range(k):
            com_cost = 0
            min_range = 100000001
            max_range = -1
            for j in range(n):
                com_cost += composition[i][j] * cost[j]
                times = stock[j] // composition[i][j]
                if times < min_range:
                    min_range = times
                if times > max_range:
                    max_range = times
            min_range += budget // com_cost
            max_range += budget // com_cost + 1

            l, r = min_range, max_range
            total_cost = 0
            while l <= r:
                mid = (l + r) // 2
                total_cost = mid * com_cost
                for j in range(n):
                    if stock[j] < composition[i][j] * mid:
                        total_cost -= cost[j] * stock[j]
                    else:
                        total_cost -= composition[i][j] * mid * cost[j]
                if total_cost > budget:
                    r = mid - 1
                else:
                    l = mid + 1
            if max_cnt < r:
                max_cnt = r
        return max_cnt
