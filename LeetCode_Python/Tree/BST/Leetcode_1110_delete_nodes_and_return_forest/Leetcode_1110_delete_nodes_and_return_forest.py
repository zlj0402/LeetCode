"""
@brief: Leetcode_1110_删点成林
@link: https://leetcode.cn/problems/delete-nodes-and-return-forest/description/
@author: liangj.zhang
@date: 24/12/2025

@Difficulty: Medium

@Label: BST(post order)

@Retrospect(worthy 1 - 5):

@thoughts:
 + 【思路 1】：post order，从下到上剥离要分离的子树，唯独 post order 能做到题目的要求；
     如果以 pre order 进行删除，或者 inorder，会有子树无法进入；
     ---
     这个方法，是 chat 给的，我让其简化思路 1，它给我的这个，确实很巧妙；

     + 分析：
         + 时间复杂度：O(n) + O(m)
         + 空间复杂度：最坏 O(n)，常数小
     + rank:
         + 时间效率：58 ms, 击败 80.65%
         + 空间效率：17.47 MB, 击败 97.70%
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
    def __init__(self):
        self.s = set()
        self.ans = []

    def post_order(self, root: Optional[TreeNode]) -> Optional[TreeNode]:
        if not root: return None
        root.left = self.post_order(root.left)
        root.right = self.post_order(root.right)
        if root.val in self.s:
            if root.left: self.ans.append(root.left)
            if root.right: self.ans.append(root.right)
            return None
        return root

    def delNodes(self, root: Optional[TreeNode], to_delete: List[int]) -> List[TreeNode]:
        for e in to_delete:
            self.s.add(e)
        
        if self.post_order(root):
            self.ans.append(root)

        return self.ans