"""
@brief: Leetcode_105_从前序与中序遍历序列构造二叉树
@link: https://leetcode.cn/problems/construct-binary-tree-from-preorder-and-inorder-traversal/description
@author: liangj.zhang
@date: 20/12/2025

@Difficulty: Medium

@Label: Binary Tree

@Again(Worthy 0 - 5): 5

@thoughts:
+ 【思路 1】：利用 preOrder inOrder 特性
     有个当前范围后 preorder [pl, pr], inorder [il, ir]
     preorder 的第一个值，就是当前树的根，
     在 inorder 中知道该根的位置（通过值）in_idx 后，
     我们就能知道左右子树的情况；左子树 [il, in_idx - 1] 右子树 [in_idx + 1, ir]
     也会知道 左子树的个数 left_tree_size，
     根据 preorder 的特性，当前根之后是其整个左子树，再是整个右子树，我们知道子树个数，也就找到子树在 preorder 中的范围；
     新的范围就有了，
         左子树：preorder[pl + 1, pl + left_tree_size] inorder[il, in_idx - 1]
         右子树：preorder[pl + left_tree_size + 1, pr] inorder[in_idx + 1, ir]
     可以开启递归了

     + 分析：
         + 时间复杂度：记录 inorder 中各 val 的位置：O(n), 递归每个节点一遍 O(n)
         + 空间复杂度：O(n)
     + rank:
         + 时间效率：0 ms, 击败 100%
         + 空间效率：26.94 MB, 击败 52.82%
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
    def __init__(self):
        self.rec = {}
        self.pre = []

    def __buildTree(self, pl: int, pr: int, il: int, ir: int) -> Optional[TreeNode]:
        if pl > pr: return None
        root_idx = pl
        root_val = self.pre[root_idx]
        in_idx = self.rec[root_val]

        left_tree_size = in_idx - il

        node = TreeNode(root_val)
        node.left = self.__buildTree(pl + 1, pl + left_tree_size, il, in_idx - 1)
        node.right = self.__buildTree(pl + left_tree_size + 1, pr, in_idx + 1, ir)

        return node

    def buildTree(self, preorder: List[int], inorder: List[int]) -> Optional[TreeNode]:
        for i in range(len(inorder)):
            self.rec[inorder[i]] = i
        self.pre = preorder

        return self.__buildTree(0, preorder.__len__() - 1, 0, inorder.__len__() - 1)