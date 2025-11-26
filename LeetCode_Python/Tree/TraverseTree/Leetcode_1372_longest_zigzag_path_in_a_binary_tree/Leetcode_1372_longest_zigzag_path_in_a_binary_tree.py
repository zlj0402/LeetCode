"""
@brief: Leetcode_1372_二叉树中的最长交错路径
@link: https://leetcode.cn/problems/longest-zigzag-path-in-a-binary-tree/description/
@author: liangj.zhang
@date: 25/11/2025

@Difficulty: Medium

@Label: Tree(dfs)

@Retrospect(worthy 1 - 5): 4

@thoughts:

  + 【思路 1】：递归 & 剪枝
      遍历每个节点，把该节点当作新的 root，执行“交错路径”的 dfs；
      使用 set 进行剪枝，因为一个节点的左右子树最多走一遍，后续重复访问即可跳过。

      + 分析：
          + 时间复杂度：遍历 n → O(n)，dfs 总访问 ≤ 2n → O(n)，set 操作均摊 O(1) → 总体 O(n)
          + 空间复杂度：两个 set → O(n)

    + ps: C++ 写的

  + 【思路 2】：递归
      对每个节点 node：
        - 如果它是从父节点 root 的 left 过来的，则它作为“右转折点”；否则从它自身作为“第 1 个左转折点”开始。
        - 如果它是从父节点 root 的 right 过来的，则它作为“左转折点”；否则从它自身作为“第 1 个右转折点”开始。
      本质：每个节点既可以作为左转折点，也可以作为右转折点；
           如果不能继承父节点的 zigzag 长度，那么就重置为新起点。

      + 分析：
          + 时间复杂度：O(n)
            （相比思路 1，不会重复递归同一节点的两棵子树）
          + 空间复杂度：O(h)

      + rank：
          + 时间效率：73 ms, 击败 74.13%
          + 空间效率：32.85 MB, 击败 16.51%
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
    def __longestZigZag(self, root: Optional[TreeNode], l: int, r: int) -> int:
        if not root: return max(l, r)
        return max(self.__longestZigZag(root.left, 0, r + 1), self.__longestZigZag(root.right, l + 1, 0))
    def longestZigZag(self, root: Optional[TreeNode]) -> int:
        return self.__longestZigZag(root, 0, 0) - 1