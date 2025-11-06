"""
@brief: Leetcode_404_左叶子之和  
@link: https://leetcode.cn/problems/sum-of-left-leaves/description/  
@author: liangj.zhang  
@date: 5/11/2025  

@Difficulty: Easy  

@Label: Tree(Traverse)  

@Retrospect(worthy 1 - 5): 2  

@thoughts:
 + 【思路 1】：右子树还是要遍历的，不然右子树下的左叶子节点怎么办；  

     + 分析：  
         + 时间复杂度：O(n)  
         + 空间复杂度：O(h)，h 为树的高度  
     + rank:  
         + 时间效率：0 ms, 击败 100%  
         + 空间效率：17.68 MB, 击败 77.89%  
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

# 【思路 1】：右子树还是要遍历的，不然右子树下的左叶子节点怎么办；
class Solution:

    def __init__(self):
        self.sum = 0

    def __sumOfLeftLeaves(self, root: Optional[TreeNode], is_left: bool) -> None:
        if root is None: return
        if is_left and not root.left and not root.right:
            self.sum += root.val
        self.__sumOfLeftLeaves(root.left, True)
        self.__sumOfLeftLeaves(root.right, False)

    def sumOfLeftLeaves(self, root: Optional[TreeNode]) -> int:
        if root is None: return 0
        self.sum = 0
        self.__sumOfLeftLeaves(root, False)
        return self.sum
