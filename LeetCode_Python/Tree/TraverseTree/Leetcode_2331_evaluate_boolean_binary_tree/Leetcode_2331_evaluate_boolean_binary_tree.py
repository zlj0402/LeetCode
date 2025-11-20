"""
@brief: Leetcode_2331_计算布尔二叉树的值
@link: https://leetcode.cn/problems/evaluate-boolean-binary-tree/description/
@author: liangj.zhang
@date: 20/11/2025

@Difficulty: Easy

@Label: Tree(post-order traversal)

@Retrospect(worthy 1 - 5): 2

@thoughts:
  + 【思路 1】：递归，后序遍历
      树的简单难度，没有挑战性，全当签到了；
      + 分析：
          + 时间复杂度：O(n)
          + 空间复杂度：O(h)
      + rank:
          + 时间效率：0 ms, 击败 100%
          + 空间效率：17.75 MB, 击败 79.78%
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
    def evaluateTree(self, root: Optional[TreeNode]) -> bool:
        if not root.left: return bool(root.val)

        left = self.evaluateTree(root.left)
        right = self.evaluateTree(root.right)

        return left or right if root.val == 2 else left and right
