"""
@brief: Leetcode_1302_层数最深叶子节点的和
@link: https://leetcode.cn/problems/deepest-leaves-sum/description/
@author: liangj.zhang
@date: 6/1/2026

@Difficulty: Medium

@Label: BFS

@Retrospect(worthy 1 - 5): 3

@thoughts:
 + 【思路 1】：BFS
     每一层都计算和，循环结束之后的最后一次 sum，返回就是结果；
     ps:
     又熟悉一些层序遍历之后，已经写得像 Easy 题的感觉了；

     + 分析：
         + 时间复杂度：O(n)
         + 空间复杂度：O(n)
     + rank:
         + 时间效率：7 ms, 击败 93.35%
         + 空间效率：21.94 MB, 击败 5.23%

 + 【思路 2】：DFS
     dfs 的时候，记录最大深度，
     最大深度每次切换的时候，重新开始计算和 sum；
     小于当前最大深度就不会进行加法 -> 虽然和 BFS 一样时间复杂度都是 O(n)，但是常数小
     而且 dfs 递归时的空间复杂度是 O(h)，多数情况，使用的空间是比 BFS 要小的；
     ---
     下次遇到这题，用 dfs 再写；
"""

import os
import sys

print(os.path.join(os.path.dirname(__file__)))
print(os.path.abspath(os.path.join(os.path.dirname(__file__), "../../../../.."))) #f:\Code\zljgit\LeetCode
sys.path.append(os.path.abspath(os.path.join(os.path.dirname(__file__), "../../../../..")))

from typing import Optional, List

from Include.PyLeetcode.Tree.Tree import TreeNode

# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right

from collections import deque

class Solution:
    def deepestLeavesSum(self, root: Optional[TreeNode]) -> int:
        q = deque([root])
        _sum = 0
        while q:
            _sum = 0
            size = q.__len__()
            for i in range(size):
                cur = q.popleft()
                _sum += cur.val
                if cur.left: q.append(cur.left)
                if cur.right: q.append(cur.right)
        return _sum