"""
@brief: Leetcode_1448_统计二叉树中好节点的数目
@link: https://leetcode.cn/problems/count-good-nodes-in-binary-tree/description/
@author: liangj.zhang
@date: 8/11/2025

@Difficulty: Medium

@Label: Tree(Traverse)

@Retrospect(worthy 1 - 5): 3

@thoughts:
    + 【思路 1】：递归（dfs）
        本题使用普通的 BFS 不太合适，因为节点入队后，
        父节点与当前节点的关系无法追溯，无法比较大小。
        而递归（DFS）可以自然地将 pre_max 的关系传递下去。

    + 分析：
        + 时间复杂度：O(n)
        + 空间复杂度：O(h)，其中 h 为树的高度

    + rank:
        + 时间效率：0 ms, 击败 100%
        + 空间效率：86.43 MB, 击败 52.23%
"""

import os
import sys

print(os.path.join(os.path.dirname(__file__)))
print(os.path.abspath(os.path.join(os.path.dirname(__file__), "../../.."))) #f:\Code\zljgit\LeetCode
sys.path.append(os.path.abspath(os.path.join(os.path.dirname(__file__), "../../..")))

from typing import Optional

from Include.PyLeetcode.Tree.Tree import TreeNode

# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:
    def __init__(self):
        self.__cnt = 0

    def __goodNodes(self, root: Optional[TreeNode], pre_max: int) -> None:
        if not root: return
        if root.val >= pre_max:
            self.__cnt += 1
            if root.val > pre_max: pre_max = root.val
        self.__goodNodes(root.left, pre_max)
        self.__goodNodes(root.right, pre_max)
    
    def goodNodes(self, root: Optional[TreeNode]) -> int:
        self.__cnt = 0
        self.__goodNodes(root, root.val)
        return self.__cnt