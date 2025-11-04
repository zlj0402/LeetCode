"""
@brief: Leetcode_111_二叉树的最小深度  
@link: https://leetcode.cn/problems/minimum-depth-of-binary-tree/description/  
@author: liangj.zhang  
@date: 4/11/2025  

@Difficulty: Easy  

@Label: Tree  

@Retrospect(worthy 1 - 5): 3  

@thoughts:
 + 【思路 1】：递归  
     + 节点为 None，return 0  
     + 节点自身存在，其下左右节点至少有一个为 None 时，return 有子树那边的最小深度  
       => 即 return max(left, right) + 1（都为 0，max 也能处理）  
     + 节点自身存在，其下左右节点都存在，return 左右子树最小的那边 + 1  
       => 即 return min(left, right) + 1  

     + 分析：  
         + 时间复杂度：O(n)  
         + 空间复杂度：O(h)，h 为树的高度  
     + rank:  
         + 时间效率：87 ms, 击败 18.36%  
         + 空间效率：48.49 MB, 击败 99.29%  

 + 【思路 2】：BFS  
     看了 0 ms 那条柱子；没能第一时间想起来，留到下次做吧；  
     从上到下，从左到右，遇到第一个左右节点都没有的节点，即可退出；  
     ps: 内层循环的退出条件，是当前层的节点数遍历完；  
         外层循环中，每次层计数 +1。  
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
    def minDepth(self, root: Optional[TreeNode]) -> int:
        if root is None: return 0

        left_min_h = self.minDepth(root.left)
        right_min_h = self.minDepth(root.right)

        return max(left_min_h, right_min_h) + 1 if not (left_min_h and right_min_h) else min(left_min_h, right_min_h) + 1
