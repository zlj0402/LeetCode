"""
@brief: Leetcode_226_翻转二叉树
@link: https://leetcode.cn/problems/invert-binary-tree/description
@author: liangj.zhang
@date: 18/11/2025

@thoughts:

【1】-- 递归也可以（18/11/2025）
    看题解得知递归也能解决，思路更简洁：
        - 先翻转左子树
        - 再翻转右子树
        - 然后交换左右即可

    + 分析：
        + 时间复杂度：O(n)
        + 空间复杂度：O(h)

    + rank:
        + 时间效率：0 ms, 击败 100%
        + 空间效率：17.34 MB, 击败 90.12%
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
    def invertTree(self, root: Optional[TreeNode]) -> Optional[TreeNode]:
        if not root: return None
        root.left, root.right = root.right, root.left

        self.invertTree(root.left)
        self.invertTree(root.right)

        return root