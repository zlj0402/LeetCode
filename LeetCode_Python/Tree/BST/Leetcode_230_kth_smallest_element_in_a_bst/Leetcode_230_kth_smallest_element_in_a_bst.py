"""
@brief: Leetcode_230_二叉搜索树中第 K 小的元素
@link: https://leetcode.cn/problems/kth-smallest-element-in-a-bst/description
@author: liangj.zhang
@date: 17/12/2025

@Difficulty: Medium

@Label: BST

@thoughts:
    忽略题目后面的进阶要求，对于熟悉 BST 中序遍历过程的人来说，这题只能算得上 Easy；

rank:
    时间效率：0 ms, 击败 100%
    空间效率：20.18 MB, 击败 99.91%
"""

import os
import sys

print(os.path.join(os.path.dirname(__file__)))
print(os.path.abspath(os.path.join(os.path.dirname(__file__), "../../../.."))) #f:\Code\zljgit\LeetCode
sys.path.append(os.path.abspath(os.path.join(os.path.dirname(__file__), "../../../..")))

from typing import Optional, List

from Include.PyLeetcode.Tree.Tree import TreeNode

# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:
    def __init__(self) -> None:
        self.ans = -1
        self.__cnt = 0
        self.__k = 0
        self.__find = False

    def __in_order(self, root: Optional[TreeNode]) -> None:
        if not root or self.__find: return
        self.__in_order(root.left)
        self.__cnt += 1
        if self.__cnt == self.__k:
            self.ans = root.val
            return
        self.__in_order(root.right)

    def kthSmallest(self, root: Optional[TreeNode], k: int) -> int:
        self.__cnt = 0
        self.__k = k
        self.__find = False

        self.__in_order(root)

        return self.ans