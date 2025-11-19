"""
@brief: Leetcode_617_合并二叉树
@link: https://leetcode.cn/problems/merge-two-binary-trees/description/
@author: liangj.zhang
@date: 19/11/2025

@Difficulty: Easy

@Label: Tree(dfs)

@Retrospect(worthy 1 - 5): 3

@thoughts:
  + thoughts:
    + 【思路 1】：递归 -- C++ -- 2025.11.19
        因为可能需要将当前层节点，赋给上一层；所以我们最好是在 参数 root1 root2 的角度，
        考虑其子节点；保证每次传入的参数，都是不为 nullptr 的情况；
            + 两个左子节点都不为 nullptr，则继续递归；其他情况略过；
            + 两个右子节点都不为 nullptr，则继续递归；其他情况略过；

    + 写法2：看到也能在当前层，处理当前层的事情；-- Python 实现了 -- 2025.11.19
        回退回去时，回退的方向要接住；即，
            root1.left = self.mergeTrees(root1.left, root2.left)
            root1.right = self.mergeTrees(root1.right, root2.right)
        + 分析：
            + 时间复杂度：最多 O(max(m, n))，m, n 分别为 root1, root2 的节点数
            + 空间复杂度：最多 O(max(hm, hn))，hm, hn 分别为 root1, root2 树的高度
        + rank:
            + 时间效率：0 ms, 击败 100%
            + 空间效率：17.61 MB, 击败 98.67%
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
    def mergeTrees(self, root1: Optional[TreeNode], root2: Optional[TreeNode]) -> Optional[TreeNode]:
        if not root1 and not root2: return None
        elif not root1: return root2
        elif not root2: return root1

        root1.val += root2.val
        root1.left = self.mergeTrees(root1.left, root2.left)    # 原来忘记写 root1.left/right =
        root1.right = self.mergeTrees(root1.right, root2.right)

        return root1
