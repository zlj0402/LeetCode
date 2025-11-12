"""
@brief: Leetcode_101_对称二叉树  
@link: https://leetcode.cn/problems/symmetric-tree/description  
@author: liangj.zhang  
@date: 18/6/2025  

@Difficulty: Easy  

@Label: Binary Tree  

@brief content: 判断二叉树是否为对称的二叉树  

@thoughts:
    两个树互为镜像：
        + 他们的根具有相同值  
        + 每个树的右子树都与另一个树左子树镜像对称  

    【1】-- 迭代 + 栈  
        用了当时做「翻转二叉树」没成功使用的方式（那题不适合，Leetcode_226_invert_binary_tree），
        用两个栈，对称操作，左边靠左往下延伸，右边靠右往下延伸。  

    【2】-- 递归, 剪枝版
        递归时，两棵树的根节点先比较值是否相同，
        然后递归判断 check(左树的左子树, 右树的右子树) && check(左树的右子树, 右树的左子树)。
        有了判断，就利用 self.__ret 提前结束后面的递归

        + 分析：
            + 时间复杂度：最坏 O(n)
            + 空间复杂度：最坏 O(h)，h 为树的高度
        + rank:
            + 时间效率：0 ms, 击败 100%
            + 空间效率：17.38 MB, 击败 98.91% 
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
    def __init__(self) -> None:
        self.__ret = True

    def __isSymmetric(self, left: Optional[TreeNode], right: Optional[TreeNode]) -> None:
        if self.__ret and ((not left) ^ (not right)): self.__ret = False
        if not left or not right: return
        if self.__ret and left.val != right.val: self.__ret = False

        if not self.__ret: return 

        self.__isSymmetric(left.left, right.right)
        self.__isSymmetric(left.right, right.left)

    def isSymmetric(self, root: Optional[TreeNode]) -> bool:
        self.__ret = True
        self.__isSymmetric(root.left, root.right)
        return self.__ret