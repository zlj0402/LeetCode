"""
@brief: Leetcode_965_单值二叉树
@link: https://leetcode.cn/problems/univalued-binary-tree/description/
@author: liangj.zhang
@date: 15/11/2025

@Difficulty: Easy

@Label: Tree(dfs)

@Retrospect(worthy 1 - 5): 2

@thoughts:
    + 【思路 1】：dfs（剪枝版）：纯遍历树，深度优先、广度优先都可以；这里采用递归的 dfs 方式；
        + 分析：
            + 时间复杂度：最坏 O(n)
            + 空间复杂度：最坏 O(h), h 为树的高度
        + rank:
            + 时间效率：0 ms, 击败 100%
            + 空间效率：12.52 MB, 击败 91.38%
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
        self.__res = True
        self.base = -1
    
    def __isUnivalTree(self, root: Optional[TreeNode]) -> None:
        if not root or not self.__res: return
        if root.val != self.base:
            self.__res = False
            return
        
        self.__isUnivalTree(root.left)
        self.__isUnivalTree(root.right)

    def isUnivalTree(self, root: Optional[TreeNode]) -> bool:
        self.base = root.val
        self.__res = True
        self.__isUnivalTree(root)
        return self.__res