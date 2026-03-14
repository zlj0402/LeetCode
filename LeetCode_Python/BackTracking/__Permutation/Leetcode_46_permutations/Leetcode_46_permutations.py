"""
@brief: Leetcode_46_全排列
@link: https://leetcode.cn/problems/permutations/description/
@author: liangj.zhang
@date: 11/3/2026

@updated:
    + 13/2/2026: add 【思路 2】：枚举回溯 -- 排列 -- 标志位

@Difficulty: Medium

@Label: Backtracking & Permutation

@Retrospect(worthy 1 - 5): 4, classic

@thoughts:
    + 【思路 1】：枚举回溯 -- 排列
        >>> path[idx] 从剩余可选数中，选择一个数填入 <<<
        一个是 path，另一个是要维护一个我们知道，还没有选择数的集合
        （至于这个集合的实现，是一个真的集合结构，还是采用 array 和 标志位 array，异或其他方式）
        （还可以，根据题目条件知道 nums[i] 不超过 10， 那么我们加上一个 > 10 的固定数，我们就也可以知道这个位置选择过，还不用额外开空间）
        ----
        这是写的第一个排列型回溯，有一个感受记录一下（也在下面的当中）：
        组合型回溯，我们是在 dfs 外的固定数组中，选择某个数 nums[idx]，idx 是 dfs 的参数；
        排列型回溯，我们是在 剩余集合中选择一个数，dfs 时的 idx 是 path 当中要填入的下标；
        -- 就是有这么个不同；

        + 分析：
            + 时间复杂度：排列的可能是 n!，所以：O(n * n!)
            + 空间复杂度：不算上结果，path->O(n), dfs -> O(n), summary: O(n)
        + rank:
            + 空间效率：3 ms, 击败 42.20%
            + 时间效率：19.33 MB, 击败 37.45%

    + 【思路 2】：枚举回溯 -- 排列 -- 标志位
        不采用集合的方式，使用标志位的方式
        + 分析：同上
        + rank:
            + 时间效率：0 ms, 击败 100%
            + 空间效率：19.37 MB, 击败 32.06%
"""

from typing import List


class Solution:
    def permute(self, nums: List[int]) -> List[List[int]]:
        path = [0] * len(nums)
        ans = []
        s = set(nums)
        
        # 这里的 idx 是决定放入 path[idx]，而不是 nums 中 idx 位置的数
        def dfs(idx: int, s: set) -> None:
            nonlocal path, ans
            if idx == len(nums):
                ans.append(path.copy())
                return
            for num in s:
                path[idx] = num
                dfs(idx + 1, s - {num})
                path[idx] = 0
        dfs(0, s)
        return ans


class Solution:
    def permute(self, nums: List[int]) -> List[List[int]]:
        path = [0] * len(nums)
        flags = [False] * len(nums)
        ans = []

        def dfs(idx: int) -> None:
            nonlocal path, ans, flags
            if idx == len(nums):
                ans.append(path.copy())
                return
            for i in range(len(nums)):
                if not flags[i]:
                    path[idx] = nums[i]
                    flags[i] = True
                    dfs(idx + 1)
                    flags[i] = False
                    path[idx] = 0
        dfs(0)
        return ans
