"""
@brief: Leetcode_1609_奇偶树
@link: https://leetcode.cn/problems/even-odd-tree/description/
@author: liangj.zhang
@date: 7/1/2026

@Difficulty: Medium

@Label: BFS + vector/queue

@Retrospect(worthy 1 - 5): 4

@thoughts:
 + 【思路 1】：BFS + list
     + 分析：
         + 时间复杂度：O(n)
         + 空间复杂度：O(n)
     + rank:
         + 时间效率：31 ms, 击败 95.96%
         + 空间效率：55.86 MB, 击败 5.05%
"""

# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
from cmath import inf


class Solution:
    def isEvenOddTree(self, root: Optional[TreeNode]) -> bool:
        arr = [root]
        tmp = []
        level = 0
        even = True

        while arr.__len__():
            prev = -inf if even else inf
            for node in arr:
                v = node.val

                if even:
                    if v % 2 == 0 or v <= prev:
                        return False
                else:
                    if v % 2 == 1 or v >= prev:
                        return False
                prev = v
                if node.left: tmp.append(node.left)
                if node.right: tmp.append(node.right)
            arr = tmp
            tmp = []
            level += 1
            even = not even
        return True