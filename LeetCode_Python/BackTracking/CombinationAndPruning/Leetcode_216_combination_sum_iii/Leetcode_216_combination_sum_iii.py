"""
@brief: Leetcode_216_组合总和_III
@link: 组合总和 III
@author: liangj.zhang
@date: 26/2/2026

@Difficulty: Medium

@Label: Backtracking & Pruning

@Retrospect(worthy 1 - 5): 3

@thoughts:
    + 【思路 1】：回溯 + 剪枝
        正常的回溯已经没问题了吧

        剪枝1：
            正常能有结果的条件是，
            前 k 个数之和 <= n，且 后 k 个数之和 >= n

            即：
                1 + ... + k <= n <= (9 - (k - 1)) + ... + (9 - 0)

            高斯公式：
                (k + 1) * k / 2 <= n <= 9 * k - (k - 1) * k / 2

            反过来：
                当
                (k + 1) * k / 2 > n
                或
                9 * k - (k - 1) * k / 2 < n

                时，一定没有结果

        剪枝2：
            当前 path 的和已经 > n
            后续无需继续

        剪枝3：
            当

                path.size() + (9 - j + 1) < k

            即使遍历到最后，
            可选数量也不足 k，
            直接结束

    + 分析：

        时间复杂度：
            O(C(n, k) * k)

        空间复杂度：
            O(k)

    + rank:

        时间效率：
            0 ms, 击败 100%

        空间效率：
            8.49 MB, 击败 95.41%
"""
from typing import List


class Solution:
    def combinationSum3(self, k: int, n: int) -> List[List[int]]:
        path = []
        ans = []

        def dfs(idx: int, k: int, curSum: int) -> None:
            if k == 0:
                if curSum == n: ans.append(path.copy())
                return
            
            for j in range(idx, 10):
                if curSum + j > n: return
                if len(path) + (9 - j + 1) < k: return

                path.append(j)
                dfs(j + 1, k - 1, curSum + j)
                path.pop()

        if (k + 1) * k > 2 * n or (19 * k - k * k) < 2 * n: return []
        dfs(1, k, 0)

        return ans