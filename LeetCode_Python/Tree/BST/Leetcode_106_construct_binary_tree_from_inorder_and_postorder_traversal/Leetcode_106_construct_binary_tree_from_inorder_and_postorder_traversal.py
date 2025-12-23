"""
@brief: Leetcode_106_从中序与后序遍历序列构造二叉树
@link: https://leetcode.cn/problems/construct-binary-tree-from-inorder-and-postorder-traversal/description/
@author: liangj.zhang
@date: 23/12/2025

@Difficulty: Medium

@Label: BST

@Retrospect(worthy 1 - 5): 5

@thoughts:
  + 【思路 1】：利用 BST 的中序遍历和后序遍历性质
        好在前面先写过 Leetcode_105，通过「先序 + 中序」恢复一棵二叉树；
        明白 Leetcode_105 的原理后，这里其实是同样的做法。

        相同点：
            - 都需要从根节点开始构造；
            - 从下往上时，无法直接判断左右子树的节点数量，
              也无法判断当前子树是作为上一层的左子树还是右子树。

        不同点：
            - 正是由于上述相同点，这里需要从后往前遍历 postorder；
            - 从构造顺序上看，相当于「根 → 右子树 → 左子树」，
              立刻就有了 Leetcode_105 的感觉。

        写 Leetcode_105 时对原理还不够熟，但至少已经理解；
        这道题是对照 Leetcode_105 写出来的，
        下一步是脱离参考，用 Python 再独立实现一遍。

        分析：
            时间复杂度：
                - 遍历并记录 inorder：O(n)
                - 递归构造，每个节点作为一次根节点：O(n)
            空间复杂度：
                - 记录 inorder 的数值与下标：O(n)

        rank:
            时间效率：3 ms, 击败 94.53%
            空间效率：18.57 MB, 击败 97.93%
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
        self.post = []

    def __buildTree(self, pl: int, pr: int, il:int, ir: int) -> Optional[TreeNode]:
        if il > ir: return None

        root_idx = pr
        root_val = self.post[root_idx]
        in_idx = self.rec[root_val]

        right_tree_size = ir - in_idx

        node = TreeNode(root_val)
        node.right = self.__buildTree(pr - right_tree_size, pr - 1, in_idx + 1, ir)
        node.left = self.__buildTree(pl, pr - right_tree_size - 1, il, in_idx - 1)

        return node

    def buildTree(self, inorder: List[int], postorder: List[int]) -> Optional[TreeNode]:
        size = inorder.__len__()
        for i in range(size):
            self.rec[inorder[i]] = i
        self.post = postorder
        return self.__buildTree(0, size - 1, 0, size - 1)