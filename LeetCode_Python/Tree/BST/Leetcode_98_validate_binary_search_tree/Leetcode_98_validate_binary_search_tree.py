"""
@brief: Leetcode_98_验证二叉搜索树
@link: https://leetcode.cn/problems/validate-binary-search-tree/description
@author: liangj.zhang
@date: 2/12/2025

@Difficulty: Medium

@Label: BST

@Retrospect(worthy 1 - 5): 5 -- Classic

@brief content: 验证一个树是否是二叉搜索树

@thoughts:
  + 【思路 1】：inOrder
        我们知道一个二叉搜索树，以中序遍历来输出的话，是顺序的结果；
        我们利用一个全局的 max_val 变量，来记录上一个遍历到的值；
        中序遍历的过程中：max_val 是应该每一次都会被更新的，
        如果有一次出现不是的情况，我们就知道结果；

    + rank:
        时间效率：0 ms, 击败 100%
        空间效率：19.21 MB, 击败 96.82%

"""


from cmath import inf
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
    pre = -inf
    def isValidBST(self, root: Optional[TreeNode]) -> bool:
        if not root: return True

        if not self.isValidBST(root.left):
            return False
        if self.pre >= root.val:
            return False
        self.pre = root.val
        if not self.isValidBST(root.right):
            return False
        
        return True