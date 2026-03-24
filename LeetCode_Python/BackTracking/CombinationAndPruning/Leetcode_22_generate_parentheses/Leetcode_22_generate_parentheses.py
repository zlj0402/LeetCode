"""
@brief: Leetcode_22_括号生成
@link: https://leetcode.cn/problems/generate-parentheses/description/
@author: liangj.zhang
@date: 24/3/2026

@Difficulty: Medium

@Label: Backtracking + Pruning

@Retrospect (worthy 1 - 5): 4

@thoughts:
    + 【思路 1】：选与不选子集型回溯 + 剪枝
        初始化，path 全为右括号，但是从头开始算，右括号数还是 0，方便生成字符串；
        当遍历到某个 idx 时，右括号比左括号多时，一定是错误的情况；

        + 分析：
            + 时间复杂度：O(C(n, 2n) * n)
            + 空间复杂度：不算结果，O(n)
        + rank:
            + 时间效率：0 ms, 击败 100%
            + 空间效率：19.10 MB, 击败 78.59%
"""

from typing import List


class Solution:
    def generateParenthesis(self, n: int) -> List[str]:
        path = [')'] * 2 * n
        ans = []
        def dfs(idx: int, left: int, right: int) -> None:
            if right > left: return

            if idx == 2 * n:
                if left == right:
                    ans.append(''.join(path))
                return

            dfs(idx + 1, left, right + 1)

            # 选
            path[idx] = '('
            dfs(idx + 1, left + 1, right)
            path[idx] = ')'

        dfs(0, 0, 0)

        return ans