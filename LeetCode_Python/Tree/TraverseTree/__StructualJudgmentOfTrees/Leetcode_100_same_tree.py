"""
@brief: Leetcode_100_相同的树  
@link: https://leetcode.cn/problems/same-tree/description/  
@author: liangj.zhang  
@date: 11/11/2025  

@Difficulty: Easy  

@Label: Tree(Structural Judgment Of Trees)  

@Retrospect(worthy 1 - 5): 3  

@thoughts:
    + 【思路 1】：递归  
        对方（p）传哪边，我（q）就传哪边，（步调一致），然后函数体内进行比较；  

        + 分析：  
            + 时间复杂度：最坏 O(n)，遇到不等的，就一直退出递归；  
            + 空间复杂度：O(h)，最坏的情况，h 为树的高度  

        + rank:  
            + 时间效率：0 ms, 击败 100%  
            + 空间效率：17.39 MB, 击败 90.45%  
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
        self.__ret = True
    
    def __isSameTree(self, p: Optional[TreeNode], q: Optional[TreeNode]) -> None:
        if (not p) ^ (not q): self.__ret = False
        if self.__ret and ((not p) or (not q)): return
        if self.__ret and p.val != q.val: self.__ret = False

        if not self.__ret: return

        self.__isSameTree(p.left, q.left)
        self.__isSameTree(p.right, q.right)

    def isSameTree(self, p: Optional[TreeNode], q: Optional[TreeNode]) -> bool:
        self.__ret = True
        self.__isSameTree(p, q)
        return self.__ret