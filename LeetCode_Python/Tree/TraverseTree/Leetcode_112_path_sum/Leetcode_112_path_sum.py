"""
@brief: Leetcode_112_路径总和  
@link: https://leetcode.cn/problems/path-sum/description/  
@author: liangj.zhang  
@date: 6/11/2025  

@Difficulty: Easy  

@Label: Tree(Traverse)  

@Retrospect(worthy 1 - 5): 3  

@thoughts:
 + 【思路 1】：递归  
     + 【写法 1】：在叶子节点结算  
         + 分析：  
             + 时间复杂度：O(n)  
             + 空间复杂度：O(h)，h 为树的高度  
         + rank:  
             + 时间效率：0 ms, 击败 100%  
             + 空间效率：18.71 MB, 击败 36.78%
"""

import os
import sys

print(os.path.join(os.path.dirname(__file__)))
print(os.path.abspath(os.path.join(os.path.dirname(__file__), "../../../.."))) #f:\Code\zljgit\LeetCode
sys.path.append(os.path.abspath(os.path.join(os.path.dirname(__file__), "../../../..")))

from typing import Optional

from Include.PyLeetcode.Tree.Tree import TreeNode

# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:

    def __init__(self):
        self.find = False

    def __hasPathSum(self, root: Optional[TreeNode], left: int) -> None:
        
        if not root.left and not root.right and left == 0:
            self.find = True
        
        if not self.find:
            if root.left: self.__hasPathSum(root.left, left - root.left.val)
            if root.right: self.__hasPathSum(root.right, left - root.right.val)

    def hasPathSum(self, root: Optional[TreeNode], targetSum: int) -> bool:
        if not root: return False
        self.find = False
        self.__hasPathSum(root, targetSum - root.val)
        return self.find