"""
@brief: Leetcode_107_二叉树的层序遍历_II
@link: https://leetcode.cn/problems/binary-tree-level-order-traversal-ii/description/
@author: liangj.zhang
@date: 1/1/2026

@Difficulty: Medium

@Label: BFS

@Retrospect(worthy 1 - 5): 3

@thoughts:
 + 【思路 1】：正常的从上到下的 BFS；最后将答案反转一下；

     + 分析：
         + 时间复杂度：BFS -> O(n), 反转结果 -> O(h), h 是树的高度；
         + 空间复杂度：O(n)
     + rank:
         + 时间效率：0 ms, 击败 100%
         + 空间效率：17.46 MB, 击败 90.93%
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
    MAXSIZE = 2001
    arr = [0] * MAXSIZE
    def levelOrderBottom(self, root: Optional[TreeNode]) -> List[List[int]]:
        if not root: return []

        self.arr = Solution.arr
        front = rear = 0
        ret = []

        self.arr[rear] = root; rear += 1
        while front < rear:
            tmp = []
            last_rear = rear

            while front < last_rear:
                cur = self.arr[front]; front += 1
                tmp.append(cur.val)
                if cur.left: self.arr[rear] = cur.left; rear += 1
                if cur.right: self.arr[rear] = cur.right; rear += 1

            ret.append(tmp)
        return ret[::-1]