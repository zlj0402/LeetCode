"""
@brief: Leetcode_104_二叉树的最大深度  
@link: https://leetcode.cn/problems/maximum-depth-of-binary-tree/description/  
@author: liangj.zhang  
@date: 3/11/2025  

@Difficulty: Easy  

@Label: Tree  

@Retrospect(worthy 1 - 5): 3  

@thoughts:
 + 【写法 1】：递归时，传递深度；向下得到最大深度;
    ps: C++ 实现了，python 留给以后写吧；
  
 + 【写法 2】：递归返回时，比较左右子树高度；向上得到最大深度  
     + 分析：  
         + 时间复杂度：O(n)  
         + 空间复杂度：O(h)，h 为树的高度；最坏：O(n)，平均：O(log n)  
     + rank:
         + 时间效率：0 ms, 击败 100%
         + 空间效率：18.77 MB, 击败 44.69%

 +  【写法 3】：BFS
     + 分析：
         + 时间复杂度：O(n)
         + 空间复杂度：O(1)
     + rank:
         + 时间效率：0 ms, 击败 100%
         + 空间效率：18.04 MB, 击败 95.02%
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
    MAXSIZE = 10001
    arr = [None] * MAXSIZE

    def __init__(self):
        self.arr = Solution.arr

    def maxDepth(self, root: Optional[TreeNode]) -> int:
        if not root: return 0
        ret = front = rear = 0
        
        self.arr[rear] = root; rear += 1
        while front < rear:
            ret += 1
            last_rear = rear
            while front < last_rear:
                cur = self.arr[front]; front += 1
                if cur.left: self.arr[rear] = cur.left; rear += 1
                if cur.right: self.arr[rear] = cur.right; rear += 1
        return ret

class Solution:

    # 这个写法真优雅
    def maxDepth(self, root: Optional[TreeNode]) -> int:
        if root is None:
            return 0
        left_height = self.maxDepth(root.left)
        right_height = self.maxDepth(root.right)

        return max(left_height, right_height) + 1