"""
@brief: Leetcode_1080_根到叶路径上的不足节点
@link: https://leetcode.cn/problems/insufficient-nodes-in-root-to-leaf-paths/description/
@author: liangj.zhang
@date: 1/12/2025

@Difficulty: Medium

@Label: Tree(recursion)

@Retrospect(worthy 1 - 5): 4

@thoughts:
  + 【思路 1】：递归
      nnd, 没有自己写出来；看了灵神的代码；
      主要特殊的地方是：如果回退时，回退到的节点两节点都为空，那么这个节点也要删除；
      （到叶子结点，要比较一下，
          + 能满足条件，肯定会把当前节点 return 回去，
          + 只有没有满足条件的，才会 return None，两边都没有，那么肯定是因为路径走到头时，没能满足条件）
      + 分析：
          + 时间复杂度：O(n)
          + 空间复杂度：O(h)，最坏为 O(n)
      + rank:
          + 时间效率：7 ms, 击败 48.21%
          + 空间效率：18.89 MB, 击败 93.33%
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
    def sufficientSubset(self, root: Optional[TreeNode], limit: int) -> Optional[TreeNode]:
        limit -= root.val
        if not root.left and not root.right: return None if limit > 0 else root

        if root.left: root.left = self.sufficientSubset(root.left, limit)
        if root.right: root.right = self.sufficientSubset(root.right, limit)

        return root if root.left or root.right else None