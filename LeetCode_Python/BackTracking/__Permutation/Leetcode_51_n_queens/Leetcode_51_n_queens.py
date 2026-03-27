"""
@brief: Leetcode_51_N_皇后
@link: https://leetcode.cn/problems/n-queens/description/
@author: liangj.zhang
@date: 14/3/2026

@Difficulty: Hard

@Label: Backtracking & permutation

@Retrospect(worthy 1 - 5): 5

@thoughts:
    + 【思路 1】：回溯
        是在按照灵神的题单在刷，这里是视频讲解题，但有想法的，我习惯在视频之前按照自己的思路来一遍（如果有的话）
        ----
        这题自己的思路，就是题目，这个游戏的规则，结合回溯的枚举特性，
        每个皇后不会在同一横向和纵向，以及斜线；
        我就枚举每一行位置的可能，
            枚举第一行位置的可能，
            下一行从没有选过的列当中再选一个，下下一行亦是如此；
        ----
        最先完成的一版有重复的问题，再结合 chat 的分析之后，改了过来；
        原来的行号也是通过 for 循环一次选出一个（所以第一个行号就有 4 中情况...），没有按固定顺序枚举下来；有这么个问题；

        + 分析：
            + 时间复杂度：O(n! * n)，n! -> 是情况的可能性，n 是每个节点都要遍历 n 次
            + 空间复杂度：不算存储结果：O(n)
        + rank:
            + 时间效率：15 ms, 击败 42.65%
            + 空间效率：19.42 MB, 击败 53.91%
"""
from typing import List


class Solution:
    
    def solveNQueens(self, n: int) -> List[List[str]]:
        col_s = set()

        path = []
        ans = []
        def dfs(idx: int) -> None:
            nonlocal col_s, path, ans
            if idx == n:
                tmp = []
                for i in range(len(path)):
                    row = ['.'] * n
                    row[path[i][1]] = 'Q'
                    tmp.append(''.join(row))
                ans.append(tmp.copy())
                return

            x = idx # 原来错误的写法：给 x 也来了一遍 for 循环
            for y in range(n):
                if y not in col_s:
                    find = True
                    for x_, y_ in path:
                        if abs(y_ - y) == abs(x_ - x):
                            find = False
                            break
                    if find:
                        col_s.add(y)
                        path.append((x,y))

                        dfs(idx + 1)

                        path.pop()
                        col_s.remove(y)
        dfs(0)
        return ans
    
print(Solution().solveNQueens(n=1))
