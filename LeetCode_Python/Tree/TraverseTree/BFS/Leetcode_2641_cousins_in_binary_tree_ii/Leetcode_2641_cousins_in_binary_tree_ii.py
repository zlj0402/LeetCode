"""
@brief: Leetcode_2641_二叉树的堂兄弟节点_II
@link: https://leetcode.cn/problems/cousins-in-binary-tree-ii/description/
@author: liangj.zhang
@date: 11/1/2026

@Difficulty: Medium

@Label: BFS

@Retrospect(worthy 1 - 5): 3

@thoughts:
 + 【思路 1】：BFS + vector
     存入一个节点时，就把该节点的孩子节点和传下去；
     同时在这个过程，也能算出下一层的总和； => 不用在下一层节点遍历时，额外遍历一遍；
     + 分析：
         + 时间复杂度：O(n)
         + 空间复杂度：O(n)
     + rank:
         + 时间效率：95 ms, 击败 65.37%
         + 空间效率：63.39 MB, 击败 12.99%
"""

# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:
    def replaceValueInTree(self, root: Optional[TreeNode]) -> Optional[TreeNode]:
        arr, tmp = [(root, root.val)], []
        last_sum = root.val

        while arr.__len__():
            new_sum = 0
            tmp = []    # 这里不能是 tmp.clear(), arr = tmp，arr 和 tmp 是同一个引用，清空也会将 arr 的指向内容清空
            for cur, sub_sum in arr:
                _sum = (cur.left.val if cur.left else 0) + \
                        (cur.right.val if cur.right else 0)
                if cur.left: tmp.append((cur.left, _sum))
                if cur.right: tmp.append((cur.right, _sum))
                cur.val = last_sum - sub_sum
                new_sum += _sum
            arr = tmp
            last_sum = new_sum

        return root