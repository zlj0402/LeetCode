"""
@brief: Leetcode_39_组合总和
@link: https://leetcode.cn/problems/combination-sum/description/
@author: liangj.zhang
@date: 23/3/2026

@Difficulty: Medium

@Label: Backtracking & 剪枝 & dfs

@Retrospect (worthy 1 - 5): 3 + 5 (classic)

@thoughts:
+ 【思路 1】：枚举回溯 -- 剪枝

    一开始就不自觉地认为先排序一遍，方便后面剪枝；
    我按升序排列；O(nlogn)

    这时候再按顺序回溯，当出现第一个大于 target 的位置，
    此处的 for (size_t j = idx; j < candidates.size(); ++j)
    后面都不用遍历了，以及每个位置后面的回溯，直接 return；

    + 分析：
        + 时间复杂度：
            n -> candidates.size()
            T -> target
            min -> candidates[0] (排序后)

            + 排序:
                O(nlogn)

            + 递归的最大深度:
                O(T/min)
                假设为 O(d)
                最坏情况 (min = 1)，d = T

            + 每层的分支数:
                每层最多有 n 种选择（理论上），
                但实际上随着 sum 增加，可选数量会减少；

            + 回溯的最坏情况:
                O(n^d) = O(n^(T/min))
                没有重复值，越到后面可选择越少；

            + 总计:
                O(nlogn) + O(n^(T/min))

        + 空间复杂度：
            + 递归栈深度: O(T/min)
            + path 空间: O(T/min)
            + 结果: O(解的总数 * 平均长度)

    + rank:
        + 时间效率: 11 ms, 击败 45.13%
        + 空间效率: 19.64MB, 击败 5.16%
"""

from typing import List


class Solution:
    def combinationSum(self, candidates: List[int], target: int) -> List[List[int]]:
        path, ans = [], []
        size = len(candidates)

        candidates.sort()
        def dfs(idx: int, _sum: int) -> None:
            nonlocal path, ans
            if _sum >= target or idx >= size:
                if _sum == target: ans.append(path.copy())
                return
            
            for i in range(idx, size):
                path.append(candidates[i])
                dfs(i, _sum + candidates[i])
                path.pop()

        dfs(0, 0)

        return ans