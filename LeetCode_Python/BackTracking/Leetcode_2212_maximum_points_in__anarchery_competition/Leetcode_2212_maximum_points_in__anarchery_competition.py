"""
@brief: Leetcode_2212_射箭比赛中的最大得分
@link: https://leetcode.cn/problems/maximum-points-in-an-archery-competition/description/
@author: liangj.zhang
@date: 20/2/2026

@updated:
    + 21/2/2026:【思路 1 -- 写法 3】：回溯，得分与不得分

@Difficulty: Medium

@Label: BackTracking

@Retrospect(worthy 1 - 5): 3

@thoughts:
    + 【思路 1 -- 写法 3】：回溯，得分与不得分
        区分得分与不得分，每次枚举得分的情况；
        得分取比 Alice 的得分多 1 的最小值；选取完，剩下的统一加到 ans[0] 当中；
        + 分析：
            + 时间复杂度：O(2^n * n), 最坏就是每一次向下枚举，都会更新 ans，就会 * n；
            + 空间复杂度：O(n)
        + rank:
            + 时间效率：11 ms, 击败 66.07%
            + 空间效率：12.41 MB, 击败 67.26%
"""

from typing import List


class Solution:
    def maximumBobPoints(self, numArrows: int, aliceArrows: List[int]) -> List[int]:
        maxScore = 0
        path = [0] * 12
        ans = []

        def dfs(idx: int, score: int, leftArrows: int) -> None:
            nonlocal maxScore, path, ans    # 这里必须需要，不然就是新建一个对象，没有用到外面的
            if maxScore < score:
                ans = path.copy()
                maxScore = score
                # 都是按最小得分 ans[j] 的值的，如果有多余的，就统一放入 ans[0] 当中（多余的是可以任意放的）
                if leftArrows > 0:
                    ans[0] += leftArrows
            for j in range(idx, len(aliceArrows)):
                # 可以得分
                if leftArrows - (aliceArrows[j] + 1) >= 0:
                    path[j] = aliceArrows[j] + 1
                    # 直接利用递归参数，避免手动回溯 score 和 leftArrows
                    dfs(j + 1, score + j, leftArrows - (aliceArrows[j] + 1))
                    path[j] = 0
        
        dfs(0, 0, numArrows)

        return ans