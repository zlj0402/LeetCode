"""
@brief: Leetcode_700_二叉搜索树中的搜索
@link: https://leetcode.cn/problems/search-in-a-binary-search-tree/description/
@author: liangj.zhang
@date: 4/12/2025

@Difficulty: Easy

@Label: BST

@Retrospect(worthy 1 - 5): 3

@thoughts:
  + 【思路 1】：BST 的查找
        就类似 map/set STL 库的简略查找实现，查找是 O(logn)
        Code 十分简略，赞^^

        分析：
            时间复杂度：O(logn)
            空间复杂度：O(1)

        rank:
            时间效率：0 ms, 击败 100%
            空间效率：34.70 MB, 击败 63.91%
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
    def searchBST(self, root: Optional[TreeNode], val: int) -> Optional[TreeNode]:
        if not root or root.val == val: return root
        return self.searchBST(root.right if root.val < val else root.left, val)