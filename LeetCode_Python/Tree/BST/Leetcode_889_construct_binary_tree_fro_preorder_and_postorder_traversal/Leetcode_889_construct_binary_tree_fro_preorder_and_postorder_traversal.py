"""
@brief: Leetcode_889_根据前序和后序遍历构造二叉树
@link: https://leetcode.cn/problems/construct-binary-tree-from-preorder-and-postorder-traversal/description/
@author: liangj.zhang
@date: 23/12/2025

@Difficulty: Medium

@Label: BST

@Retrospect(worthy 1 - 5): 5

@thoughts:
  + 【思路 1】：利用先序遍历和后序遍历的性质
        这道题和 Leetcode_105 / 106 属于同一类构造二叉树的问题；

        不同之处在于：
            在已知当前根节点的情况下，无法像 105 / 106 那样，
            直接通过 inorder 序列确定左右子树的节点数量；
            因此需要借助「子树根节点」，
            在另一种遍历序列中的位置来推导左右子树的规模
            （手动走一遍示例会更清晰）。

        但从整体原理上看：
            依然是通过确定左右子树的区间范围，
            然后递归地构造整棵树；

        相比 105 / 106：
            边界条件会稍微多一些。

        ---
        个人复盘：
            觉得自己最初的代码写得有些乱，
            后来让 ChatGPT 帮忙做了一次简化。

        分析：
            时间复杂度：O(n)
            空间复杂度：O(n)

        rank:
            时间效率：0 ms, 击败 100%
            空间效率：17.11 MB, 击败 98.11%
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
        self.rec = {}
        self.pre = []
    
    def build(self, lpre: int, rpre:int, lpost: int, rpost: int) -> Optional[TreeNode]:
        if lpre > rpre: return None

        node = TreeNode(self.pre[lpre])
        if lpre == rpre: return node    # 说明当前只有一个节点

        left_root_val = self.pre[lpre + 1]
        left_size = self.rec[left_root_val] - lpost + 1

        node.left = self.build(lpre + 1,
                               lpre + left_size,
                               lpost,
                               lpost + left_size - 1)
        node.right = self.build(lpre + left_size + 1,
                                rpre,
                                lpost + left_size,
                                rpost - 1)
        return node
    
    def constructFromPrePost(self, preorder: List[int], postorder: List[int]) -> Optional[TreeNode]:
        size = preorder.__len__()
        self.pre = preorder

        for i in range(size):
            self.rec[postorder[i]] = i

        return self.build(0, size - 1, 0, size - 1)
