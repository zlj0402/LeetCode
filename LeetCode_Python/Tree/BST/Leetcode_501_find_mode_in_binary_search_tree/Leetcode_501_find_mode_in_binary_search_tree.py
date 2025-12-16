"""
@brief: Leetcode_501_二叉搜索树中的众数
@link: https://leetcode.cn/problems/find-mode-in-binary-search-tree/description/
@author: liangj.zhang
@date: 16/12/2025

@Difficulty: Easy

@Label: BST

@Retrospect(worthy 1 - 5): 3

@thoughts:
  + 【思路 1】：BST
        update 的时机是当前遍历值 root.val 与 last 不一样时；
        + 为此，先让 last 赋值为 BST 中的第一个值：findBSTFirstNode【不同做法，可能不需要这样】
        中规中矩的 inOrder 遍历，做一次 update 或者更新一下 last、cur_cnt；

    分析：
        时间复杂度：O(n)
        空间复杂度：最坏 O(n)

    rank:
        时间效率：3 ms, 击败 77.9%
        空间效率：20.93 MB, 击败 47.96%
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
        self.last = 0
        self.max_cnt = 0
        self.cur_cnt = 0
        self.max_num = []

    def findBSTFirstNode(self, root: Optional[TreeNode]) -> Optional[TreeNode]:
        if not root: return None
        ret = self.findBSTFirstNode(root.left)
        return ret if ret else root
    
    def update(self) -> None:
        if self.max_cnt <= self.cur_cnt:
            if self.max_cnt < self.cur_cnt:
                self.max_num.clear()
                self.max_cnt = self.cur_cnt
            self.max_num.append(self.last)
        self.cur_cnt = 0

    def __findMode(self, root: Optional[TreeNode]) -> None:
        if not root: return
        self.__findMode(root.left)

        if root.val != self.last:
            self.update()
        
        self.cur_cnt += 1
        self.last = root.val

        self.__findMode(root.right)

    def findMode(self, root: Optional[TreeNode]) -> List[int]:
        
        self.last = self.findBSTFirstNode(root).val
        self.max_cnt = -1
        self.cur_cnt = 0

        self.__findMode(root)
        self.update()

        return self.max_num