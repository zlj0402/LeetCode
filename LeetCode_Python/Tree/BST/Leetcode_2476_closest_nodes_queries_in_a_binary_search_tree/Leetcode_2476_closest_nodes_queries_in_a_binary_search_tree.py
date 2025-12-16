"""
@brief: Leetcode_2476_二叉搜索树最近节点查询
@link: https://leetcode.cn/problems/closest-nodes-queries-in-a-binary-search-tree/description/
@author: liangj.zhang
@date: 15/12/2025

@Difficulty: Medium

@Label: binary search & BST

@Retrospect(worthy 1 - 5): 4

@thoughts:
  + 【思路 1】：Binary Search + BST
        先用 inOrder 的方式遍历二叉搜索树（BST），得到一个升序序列；
        题目要求得到：
            - <= target 的最大值
            - >= target 的最小值

        其中：
            + >= target 的最小值：即 lower_bound
            + <= target：已知 lower_bound 返回的位置 pos，pos - 1 即为答案

        分析：
            时间复杂度：inOrder(O(n)) + q * O(logn)
            空间复杂度：inOrder(O(n))（未假设平衡 BST） + O(q)

        rank:
            时间效率：418 ms, 击败 24.00%
            空间效率：73.6 MB, 击败 18.53%
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
    
    def __init__(self) -> None:
        self.arr = []
        self.ret = []

    def dfs(self, root: Optional[TreeNode]) -> None:
        if not root: return
        self.dfs(root.left)
        self.arr.append(root.val)
        self.dfs(root.right)
        
    def lower_bound(self, target: int) -> int:      
        l, r = 0, self.arr.__len__() - 1
        while l <= r:
            mid = (l + r) // 2
            if self.arr[mid] < target:
                l = mid + 1
            else:
                r = mid - 1
        return l

    def closestNodes(self, root: Optional[TreeNode], queries: List[int]) -> List[List[int]]:

        self.dfs(root)

        size = self.arr.__len__()
        for e in queries:
            l = self.lower_bound(e)
            _min = self.arr[l] if l >= 0 and l < size else -1
            r = l - 1
            _max = e if _min == e else self.arr[r] if r >= 0 and r < size else -1
            self.ret.append([_max, _min])

        return self.ret