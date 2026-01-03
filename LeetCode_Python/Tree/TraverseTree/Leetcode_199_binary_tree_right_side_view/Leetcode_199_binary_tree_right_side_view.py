"""
@brief: Leetcode_199_二叉树右视图
@link: https://leetcode.cn/problems/binary-tree-right-side-view/description
@author: liangj.zhang
@date: 14/11/2025

@updated: 
    + 3/1/2026: add 【思路 2】：BFS

@Difficulty: Medium

@Label: Binary Tree

@brief content: 从右边看，每一行谁在最右边

@thoughts:
    从右边看，右边比左边更有优先级；
    并且，记录的节点值，是从上往下；
    那么，我们采用先序遍历，且右节点遍历顺序，早于左节点；
    （在向下的过程中，就将深度传递开来； 不采用“回”的时候，将高度返回回来）
    
    + 分析：
         + 时间复杂度：O(n)
         + 空间复杂度：O(h)，h 为树的高度

    + rank: 
         + 时间效率：0 ms, 击败 100%
         + 空间效率：17.49 MB, 击败 55.7%

    + 【思路2】：BFS
         BFS 层序遍历，先遍历右边节点，放入子节点时也先放入右节点；
         内循环遍历的第一个就是右边看到的该层的第一个节点；
         也可以正常的先遍历左节点，放入时也先放入左节点；内循环遍历的最后一个节点，就是该层从右边的第一个节点；
        
         + 分析：
            + 时间复杂度：O(n)
            + 空间复杂度：O(n)
         + rank:
            + 时间效率：0 ms, 击败 100%
            + 空间效率：17.06 MB, 击败 94.28%
"""

import os
import sys

print(os.path.join(os.path.dirname(__file__)))
print(os.path.abspath(os.path.join(os.path.dirname(__file__), "../../.."))) #f:\Code\zljgit\LeetCode
sys.path.append(os.path.abspath(os.path.join(os.path.dirname(__file__), "../../..")))

from typing import List, Optional

from Include.PyLeetcode.Tree.Tree import TreeNode

# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right

# 【思路 2】：BFS
class Solution:
    def rightSideView(self, root: Optional[TreeNode]) -> List[int]:
        if not root: return []
        ret = []
        arr = [root]
        tmp = []

        while arr.__len__():
            size = arr.__len__()
            for i in range(size):
                cur = arr[i]
                if i == 0: ret.append(cur.val)
                if cur.right: tmp.append(cur.right)
                if cur.left: tmp.append(cur.left)
            arr = tmp
            tmp = []

        return ret

# 【思路 1】：DFS
class Solution:
    def __init__(self):
        self.__max_depth = 0
        self.__lst = []

    def __rightSideView(self, root: Optional[TreeNode], depth: int) -> None:
        if not root: return
        if self.__max_depth < depth:
            self.__max_depth = depth
            self.__lst.append(root.val)
        self.__rightSideView(root.right, depth + 1)
        self.__rightSideView(root.left, depth + 1)

    def rightSideView(self, root: Optional[TreeNode]) -> List[int]:
        self.__max_depth = 0
        self.__lst = []
        self.__rightSideView(root, 1)
        return self.__lst
