"""
@brief: Leetcode_199_二叉树右视图
@link: https://leetcode.cn/problems/binary-tree-right-side-view/description
@author: liangj.zhang
@date: 14/11/2025

@Difficulty: Medium

@Label: Binary Tree

@brief content: 从右边看，每一行谁在最右边

@thoughts:
    从右边看，右边比左边更有优先级；
    并且，记录的节点值，是从上往下；
    那么，我们采用先序遍历，且右节点遍历顺序，早于左节点；
    （在向下的过程中，就将深度传递开来； 不采用“回”的时候，将高度返回回来）
    
    + 分析：
        + 时间复杂度：O(n)
        + 空间复杂度：O(h)，h 为树的高度

+ rank: 
    时间效率：0 ms, 击败 100%
    空间效率：17.49 MB, 击败 55.7%
"""

import os
import sys

print(os.path.join(os.path.dirname(__file__)))
print(os.path.abspath(os.path.join(os.path.dirname(__file__), "../../.."))) #f:\Code\zljgit\LeetCode
sys.path.append(os.path.abspath(os.path.join(os.path.dirname(__file__), "../../..")))

from typing import List, Optional

from Include.PyLeetcode.Tree.Tree import TreeNode

# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:
    def __init__(self):
        self.__max_depth = 0
        self.__lst = []

    def __rightSideView(self, root: Optional[TreeNode], depth: int) -> List[int]:
        if not root: return
        if self.__max_depth < depth:
            self.__max_depth = depth
            self.__lst.append(root.val)
        self.__rightSideView(root.right, depth + 1)
        self.__rightSideView(root.left, depth + 1)

    def rightSideView(self, root: Optional[TreeNode]) -> List[int]:
        self.__max_depth = 0
        self.__lst = []
        self.__rightSideView(root, 1)
        return self.__lst
