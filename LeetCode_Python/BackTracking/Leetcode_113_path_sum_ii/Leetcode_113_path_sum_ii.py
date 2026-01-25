"""
@brief: Leetcode_113_路径总和_II
@link: https://leetcode.cn/problems/path-sum-ii/description/
@author: liangj.zhang
@date: 25/1/2026

@Difficulty: Medium

@Label: Backtracking & Tree

@Retrospect(worthy 1 - 5): 3

@thoughts:
 + 【思路 1】：回溯，外部变量 -- 闭包递归
     这倒是一次性写对，唯一注意的是：叶子节点时比较值，不能放在递归终止条件进行，会有重复；
     + 分析：
         + 时间复杂度：节点遍历 O(n) + 每一条路径拷贝 O(H)
                      假设最坏情况，每一条路径都需要拷贝，
                      平衡二叉树，H -> O(logN), 路径数 L -> O(N/2)
                      拷贝最坏情况：O(NlogN)
         + 空间复杂度：O(H)
     + rank:
         + 时间效率：0 ms, 击败 100%
         + 空间效率：20.11 MB, 击败 12.74%
"""


# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
from typing import List, Optional

from Include.PyLeetcode.Tree.Tree import TreeNode


class Solution:
    def pathSum(self, root: Optional[TreeNode], targetSum: int) -> List[List[int]]:
        ret = []
        path = []

        def dfs(node: Optional[TreeNode], sum: int) -> None:
            if not node: return

            path.append(node.val)

            sum_ = sum + node.val

            if not node.left and not node.right and sum_ == targetSum:
                ret.append(path.copy())

            dfs(node.left, sum_)
            dfs(node.right, sum_)

            path.pop()

        dfs(root, 0)
        return ret
