"""
@brief: Leetcode_1026_节点与其祖先之间的最大差值
@link: https://leetcode.cn/problems/maximum-difference-between-node-and-ancestor/description/
@author: liangj.zhang
@date: 24/11/2025

@Difficulty: Medium

@Label: Tree(dfs)

@Retrospect(worthy 1 - 5): 3

@thoughts:
  + 【思路 1】：dfs
      一条路径上的最大差值，只需记录该路径上的最小值与最大值；
      遍历到每个节点时更新 max - min 即可。

      + 分析：
          + 时间复杂度：O(n)
          + 空间复杂度：O(h)

      + rank:
          + 时间效率：0 ms, 击败 100%
          + 空间效率：13.41 MB, 击败 61.7%
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
    def __init__(self) -> None:
        self._max = 0
    
    def __maxAncestorDiff(self, root: Optional[TreeNode], min_: int, max_: int) -> None:
        if root.val < min_: min_ = root.val
        if root.val > max_: max_ = root.val
        if self._max < max_ - min_: self._max = max_ - min_

        if root.left: self.__maxAncestorDiff(root.left, min_, max_)
        if root.right: self.__maxAncestorDiff(root.right, min_, max_)

    def maxAncestorDiff(self, root: Optional[TreeNode]) -> int:
        self.__maxAncestorDiff(root, root.val, root.val)
        return self._max
        