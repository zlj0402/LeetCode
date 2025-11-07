"""
@brief: Leetcode_129_求根节点到叶节点数字之和
@link: https://leetcode.cn/problems/sum-root-to-leaf-numbers/description/
@author: liangj.zhang
@date: 7/11/2025

@Difficulty: Medium (我认为只有 Easy 级别)

@Label: Tree(Traverse)

@Retrospect(worthy 1 - 5): 3

@thoughts:
    + 【思路 1】：递归
        递归的终止条件应该是“叶子节点”，
        要在叶子节点处进行结算，不能等到进入空节点；
        否则需要多传一个参数记录“上一次访问的节点”。

    + 分析：
        + 时间复杂度：O(n)
        + 空间复杂度：O(h)，其中 h 为树的高度
    + rank:
        + 时间效率：0 ms, 击败 100%
        + 空间效率：17.35 MB, 击败 94.87%
"""

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
    def __init__(self):
        self.sum = 0

    def __sumNumbers(self, root: Optional[TreeNode], val: int) -> None:
        if root and not root.left and not root.right:
            self.sum += val
        
        if root.left: self.__sumNumbers(root.left, val * 10 + root.left.val)
        if root.right: self.__sumNumbers(root.right, val * 10 + root.right.val)

    def sumNumbers(self, root: Optional[TreeNode]) -> int:
        self.sum = 0
        self.__sumNumbers(root, root.val)
        return self.sum