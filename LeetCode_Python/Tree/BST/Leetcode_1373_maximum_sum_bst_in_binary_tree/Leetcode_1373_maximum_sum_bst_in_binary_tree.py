"""
@brief: Leetcode_1373_二叉搜索子树的最大键值和
@link: https://leetcode.cn/problems/maximum-sum-bst-in-binary-tree/description/
@author: liangj.zhang
@date: 20/12/2025

@Difficulty: Hard

@Label: BST(postOrder)

@Retrospect(worthy 1 - 5): 5

@thoughts:
 + 【思路 1】：BST 的后序遍历
     + 之前写 Leetcode_98 题，验证一棵 BST；当时认真做了这题，看了灵神的多种方式，最重要的最难的验证：postOrder
     我们在遍历的时候，把当前 BST 的 sum，向上传递；
     如果在结合左右子树的情况，当前还能构成 BST，此时就要比较，max 与 sum 就可以了；

     坑：
     1. 树节点有负数，下面的 BST 可能比上面的 BST 和要大；=> 所以每次成立，都要与 max 比较；
     2. 一个叶子节点一定有 《最大键值和》，且为 0；如果整棵树都是 BST，但都是负数，叶子节点的“子树”的键值和 0，此时是最大的；

     ps:
     最开始的时候没考虑到越往上可能越小（即以为越来越大），只需要在原来是，当前不是 BST 的时候，与 max 记录值比较一下就可以了；
     因为有负数，每次都需要比较，考虑有回到了最初情况；

     + 分析：
         + 时间复杂度：O(n)
         + 空间复杂度：最坏 O(n)
     + rank:
         + 时间效率：102 ms, 击败 97.17%
         + 空间效率：36.6 MB, 击败 98.43%
"""

from cmath import inf
import os
import sys

print(os.path.join(os.path.dirname(__file__)))
print(os.path.abspath(os.path.join(os.path.dirname(__file__), "../../../.."))) #f:\Code\zljgit\LeetCode
sys.path.append(os.path.abspath(os.path.join(os.path.dirname(__file__), "../../../..")))

from typing import Optional, Tuple

from Include.PyLeetcode.Tree.Tree import TreeNode

# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:
    def __init__(self):
        self._max = 0
    
    def postOrder(self, root: Optional[TreeNode]) -> Tuple[int, int, bool, int]:
        if not root: return (inf, -inf, True, 0)

        lmin, lmax, lflag, lsum = self.postOrder(root.left)
        rmin, rmax, rflag, rsum = self.postOrder(root.right)

        if lflag and rflag and (lmax < root.val < rmin):
            _sum = lsum + rsum + root.val
            if self._max < _sum: self._max = _sum
            return {min(lmin, root.val), max(root.val, rmax), True, _sum}
        
        return {-inf, inf, False, -inf}
    
    def maxSumBST(self, root: Optional[TreeNode]) -> int:
        self._max = 0
        _, _, _flag, _sum = self.maxSumBST(root)
        if _flag and self._max < _sum: self._max = _sum

        return self._max
