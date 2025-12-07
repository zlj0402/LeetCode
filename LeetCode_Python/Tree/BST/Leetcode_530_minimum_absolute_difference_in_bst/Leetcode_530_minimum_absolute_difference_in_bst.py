"""
@brief: Leetcode_530_二叉搜索树的最小绝对差
@link: https://leetcode.cn/problems/minimum-absolute-difference-in-bst/description/
@author: liangj.zhang
@date: 7/12/2025

@Difficulty: Easy

@Label: BST

@Retrospect(worthy 1 - 5): 3

@thoughts:
  + 【思路 1】：BST 中序遍历
        BST 在中序遍历时，节点是按从小到大的顺序访问；
        最小差值一定出现在中序遍历的相邻两个节点之间。

        分析：
            时间复杂度：O(n)
            空间复杂度：O(n)

        rank:
            时间效率：0 ms, 击败 100%
            空间效率：24.89 MB, 击败 81.06%
"""

from cmath import inf
import os
import sys

print(os.path.join(os.path.dirname(__file__)))
print(os.path.abspath(os.path.join(os.path.dirname(__file__), "../../../.."))) #f:\Code\zljgit\LeetCode
sys.path.append(os.path.abspath(os.path.join(os.path.dirname(__file__), "../../../..")))

from typing import Optional

from Include.PyLeetcode.Tree.Tree import TreeNode

# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:
    _min = inf
    pre = -inf
    def __getMinimumDifference(self, root: Optional[TreeNode]) -> None:
        if not root: return
        self.__getMinimumDifference(root.left)
        self._min = min(self._min, root.val - self.pre)
        self.pre = root.val
        self.__getMinimumDifference(root.right)
    def getMinimumDifference(self, root: Optional[TreeNode]) -> int:
        
        self.__getMinimumDifference(root)
        return self._min