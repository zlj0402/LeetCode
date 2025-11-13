"""
@brief: Leetcode_110_平衡二叉树
@link: https://leetcode.cn/problems/balanced-binary-tree/description/
@author: liangj.zhang
@date: 13/11/2025

@Difficulty: Easy

@Label: Tree (Structural Judgment Of Trees)

@Retrospect(worthy 1 - 5): 3

@brief_content: 判断一个树是否是平衡二叉树
 + 平衡二叉树：指该树所有节点的左右子树高度差不超过 1。

@thoughts:
 + 【思路 1】：递归（剪枝版）
     求树的高度的题，都不用改动思路，只需比较左右子树的高度即可；
     在递归求高度的过程中，如果发现左右子树高度差超过 1，就可以立即返回 False（剪枝）。

     + 分析：
         + 时间复杂度：O(n)，平衡二叉树或接近平衡的情况下，节点需全部遍历；
         + 空间复杂度：O(h)，其中 h 为树的高度。
     + rank:
         + 时间效率：0 ms, 击败 100%
         + 空间效率：18.38 MB, 击败 92.94%
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
        self.__ans = True

    def __isBlanced(self, root: Optional[TreeNode]) -> int:
        if not self.__ans or not root: return 0
        left_h = self.__isBlanced(root.left)
        right_h = self.__isBlanced(root.right)
        if abs(left_h - right_h) > 1:
            self.__ans = False
        return max(left_h, right_h) + 1
    
    def isBalanced(self, root: Optional[TreeNode]) -> bool:
        self.__ans = True
        self.__isBlanced(root)
        return self.__ans