"""
@brief: Leetcode_1123_最深叶节点的最近公共祖先
@link: https://leetcode.cn/problems/lowest-common-ancestor-of-deepest-leaves/description/
@author: liangj.zhang
@date: 28/12/2028

@Difficulty: Meidum

@Label: LCA

@Retrospect(worthy 1 - 5): 5

@thoughts:
 + 【思路 1】：
     每条支路，到叶子节点之后，返回这条路径的深度，>>> 递归回去也是返回该路径的最大值 <<<；
     递归回去时，>>> 如果左右两条分支的最大深度不一样，取最大值 <<<
     + 如果，>>> 左右子树的深度相等，且与被记录的最大值相等，说明左右子树相对对方而言，在别的地方还有与他们相等的深度的分支；
     + 当前节点，就是[当前]发现最大深度的分支的 LCA；<<<(如果还有其他最大分支，会继续更新下去)

     + 分析：
         + 时间复杂度：O(n)
         + 空间复杂度：O(n) 可能是一条链
     + rank:
         + 时间效率：0 ms, 击败 100%
         + 空间效率：17.57 MB, 击败 95.64%
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
        self.max_depth = -1
        self.lca = None
    
    def postOrder(self, root: Optional[TreeNode], depth: int) -> int:

        if depth > self.max_depth: self.max_depth = depth
        if not root: return depth
        left = self.postOrder(root.left, depth + 1)
        right = self.postOrder(root.right, depth + 1)
        if left == right and left == self.max_depth:
            self.lca = root
        return max(left, right)
    
    def lcaDeepestLeaves(self, root: Optional[TreeNode]) -> Optional[TreeNode]:
        self.postOrder(root, 0)
        return self.lca