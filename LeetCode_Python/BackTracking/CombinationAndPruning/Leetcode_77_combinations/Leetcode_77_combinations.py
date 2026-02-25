"""
@brief: Leetcode_77_组合
@link: https://leetcode.cn/problems/combinations/description/
@author: liangj.zhang
@date: 25/2/2026

@Difficulty: Medium

@Label: Backtracking & Pruning

@Retrospect(worthy 1 - 5): 4, classic

@thoughts:
    + 【思路 1】：枚举回溯 -- 组合 -- 剪枝
        枚举回溯：每次选中一个数，后续从剩下的数中，继续选取一个（即递归）；
            所有组合的过程，参考：Leetcode_78_子集
        剪枝：当 path.size() == k 时，直接 return，这样后面继续选中的话，长度肯定会超过 k，一定都不符合情况
        
        + 分析：
            + 时间复杂度：O(C(n, k) * k)
            + 空间复杂度：O(k)
        + rank:
            + 时间效率：119 ms, 击败 58.70%
            + 空间效率：60.03 MB, 击败 43.57%
"""

from typing import List


class Solution:
    def combine(self, n: int, k: int) -> List[List[int]]:
        path = []
        ans = []
        def dfs(idx: int) -> None:
            nonlocal path, ans
            if len(path) == k:
                ans.append(path.copy())
                return
            for j in range(idx, n + 1):
                path.append(j)
                dfs(j + 1)
                path.pop()
        dfs(1)
        return ans