"""
@brief: Leetcode_1161_最大层内元素和
@link: https://leetcode.cn/problems/maximum-level-sum-of-a-binary-tree/description/
@author: liangj.zhang
@date: 10/1/2026

@Difficulty: Medium

@Label: BFS

@Retrospect(worthy 1 - 5): 3

@thoughts:
 + 【思路 1】：BFS
     计算每层元素和，只有比之前大的时候，记录当前层；这样就满足提议了
     + 分析：
         + 时间复杂度：O(n)
         + 空间复杂度：O(n)
     + rank:
         + 时间效率：0 ms, 击败 100%
         + 空间效率：105.56 MB, 击败 77.36%
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
class Solution:
    def maxLevelSum(self, root: Optional[TreeNode]) -> int:
        arr, tmp = [root], []
        max_sum, max_level = root.val, 1
        sum, level = 0, 1

        while arr.__len__():
            sum = 0
            size = arr.__len__()
            tmp = []
            for i in range(size):
                cur = arr[i]
                sum += cur.val
                if cur.left: tmp.append(cur.left)
                if cur.right: tmp.append(cur.right)

            if sum > max_sum:
                max_sum = sum
                max_level = level
            arr = tmp
            level += 1
        return max_level