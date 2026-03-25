"""
@brief: Leetcode_22_括号生成
@link: https://leetcode.cn/problems/generate-parentheses/description/
@author: liangj.zhang
@date: 24/3/2026

@updated:
    + 25/3/2026: add 【思路 2】：枚举子集型回溯 + 剪枝

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
    + 【思路 2】：枚举子集型回溯 + 剪枝
        注意代码中，迭代外和迭代内再比较，左右括号数量的差别；
        + 分析：同上
        + rank:
            + 时间效率：0 ms, 击败 100%
            + 空间效率：19.08 MB, 击败 82.33%
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

            # 没选左括号，但相当于选择了右括号
            dfs(idx + 1, left, right + 1)

            # 选
            path[idx] = '('
            dfs(idx + 1, left + 1, right)
            path[idx] = ')'

        dfs(0, 0, 0)

        return ans
    

class Solution:
    def generateParenthesis(self, n: int) -> List[str]:
        path = [')'] * 2 * n
        ans = []
        def dfs(idx: int, left: int, right: int) -> None:
            #if right > left: return    # 这是原来错误的写法：当 n == 3, 可能出现 (( )))(, 这是 idx = 2, left = 2, right = 0 是进入循环的起始；当 j 跳过 3 个 ( 去选择最后一个位置时，进入之后，两者数量相同；=》应该在进入之前进行判断
            if left == n:
                ans.append(''.join(path))
                return
            
            for j in range(idx, 2 * n):
                if right + (j - idx) > left: return # > left, 而不是 > left + 1, 表示选中 j 之前的部分，如果 右括号多于左括号，就是不可能的情况
                path[j] = '('
                dfs(j + 1, left + 1, right + (j - idx))
                path[j] = ')'
        dfs(0, 0, 0)
        return ans
    
def main():
    Solution().generateParenthesis(3)
    
if __name__ == "__main__":
    main()