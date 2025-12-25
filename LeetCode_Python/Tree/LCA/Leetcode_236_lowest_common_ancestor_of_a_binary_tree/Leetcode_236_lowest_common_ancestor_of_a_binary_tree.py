"""
@brief: Leetcode_236_二叉树的最近公共祖先
@link: https://leetcode.cn/problems/lowest-common-ancestor-of-a-binary-tree/description/
@author: liangj.zhang
@date: 25/12/2025

@Difficulty: Medium

@Label: Tree(post order)

@Retrospect(worthy 1 - 5): 5 -- classic

@thoughts:
 + 【思路 1】：dfs(postorder)
     这是算我正式的第一道 LCA, 看的灵神题解，思路很清晰，希望在忘记之后，下次还能写出这题；
     ----
     1. 当前节点是空节点
     2. 当前节点时 p(目标节点之一)
     3. 当前节点是 q(目标节点之一)
         -- 上面 3 种情况，直接返回
     4. 其他：
         4.1 左右子树都找到：return 当前节点
         4.2 只有左子树找到：return 递归左子树的结果
         4.3 只有右子树找到：return 递归右子树的结果
         4.4 左右子树都没有找到：return 空节点 --（当前遍历的方向，刚好不是两个节点所在的子树）

    + 分析：
        + 时间复杂度：最差 O(n)
        + 空间复杂度：最差 O(n)
    + rank:
        + 时间效率：56 ms, 击败 73.49%
        + 空间效率：21.34 MB, 击败 93.14%
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
#     def __init__(self, x):
#         self.val = x
#         self.left = None
#         self.right = None

class Solution:
    def lowestCommonAncestor(self, root: 'TreeNode', p: 'TreeNode', q: 'TreeNode') -> 'TreeNode':
        if not root or root == p or root == q: return root
        left = self.lowestCommonAncestor(root.left, p, q)
        right = self.lowestCommonAncestor(root.right, p, q)
        if left and right:
            return root
        return left if left else right