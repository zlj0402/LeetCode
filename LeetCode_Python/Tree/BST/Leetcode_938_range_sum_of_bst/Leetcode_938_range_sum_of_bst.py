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
    def rangeSumBST(self, root: Optional[TreeNode], low: int, high: int) -> int:
        if not root: return 0

        left = right = 0
        if root.val < low:
            right = self.rangeSumBST(root.right, low, high)
        elif root.val > high:
            left = self.rangeSumBST(root.left, low, high)
        else:
            left = self.rangeSumBST(root.left, low, high)
            right = self.rangeSumBST(root.right, low, high)

        return  (root.val if low <= root.val <= high else 0) + left + right