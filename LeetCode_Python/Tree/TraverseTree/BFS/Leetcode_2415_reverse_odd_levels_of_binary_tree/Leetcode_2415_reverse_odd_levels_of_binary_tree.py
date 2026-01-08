"""
@brief: Leetcode_2415_反转二叉树的奇数层
@link: https://leetcode.cn/problems/reverse-odd-levels-of-binary-tree/description/
@author: liangj.zhang
@date: 8/1/2026

@Difficulty: Medium

@Label: BFS、DFS

@Retrospect(worthy 1 - 5): 3(BFS) + 3(DFS)

@thoughts:
 + 【思路 1】：BFS + list
     这题是完美二叉树，那 DFS 肯定也是能行的；交换节点应该；
     最近写 BFS 写惯了，这次就先写 BFS;
     ---
     交换节点值，并不影响后续的节点记录；
     当前层遍历的时候，就像交换翻转一个有序数组就可以了； -- 这题以 list 方式会方便些；
     要交换的对立面 opposite_idx = size - i

     + 分析：
         + 时间复杂度：O(n)
         + 空间复杂度：O(n)
     + rank:
         + 时间效率：11 ms, 击败 94.29%
         + 空间效率：23.39 MB, 击败 5.11%

 + 【思路 2】：DFS
     交换节点，下次做；
"""


# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right

import os
import sys

print(os.path.join(os.path.dirname(__file__)))
print(os.path.abspath(os.path.join(os.path.dirname(__file__), "../../../../.."))) #f:\Code\zljgit\LeetCode
sys.path.append(os.path.abspath(os.path.join(os.path.dirname(__file__), "../../../../..")))

from typing import Optional, List

from Include.PyLeetcode.Tree.Tree import TreeNode

class Solution:
    def reverseOddLevels(self, root: Optional[TreeNode]) -> Optional[TreeNode]:
        arr, tmp = [root], []
        even = True
        while arr.__len__():
            size = arr.__len__()
            tmp = []
            for i in range(size):
                cur = arr[i]
                if cur.left: tmp.append(cur.left)
                if cur.right: tmp.append(cur.right)
                if not even and i < size // 2:
                    op = size - 1 - i
                    cur.val, arr[op].val = arr[op].val, cur.val
            arr = tmp
            even = not even
        return root
