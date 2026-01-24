"""
@brief: Leetcode_257_二叉树的所有路径
@link: https://leetcode.cn/problems/binary-tree-paths/description/
@author: liangj.zhang
@date: 24/1/2026

@Difficulty: Easy

@Label: BackTracking

@Retrospect(worthy 1 - 5): 4

@thoughts:

 + 【思路 1 -- 写法 2】：回溯，路径外变量 -- 当前节点，加入当前节点，
     不像写法一加入子节点的；
     注意事项，处理结束值时，需要提前一下在根节点位置，连接字符串，
     不能放在递归终止时，
     因为如此，两个空节点都会结算，就会重复；

     + 分析：
        + 时间复杂度：最坏 O(N)[一条链的时候]，一般情况下 O(N log N)
        + 空间复杂度：O(h) -> h 树的高度（没有算结果空间）
    
     + rank:
         + 时间效率：0 ms, 击败 100%
         + 空间效率：16.62 MB, 88.89%
"""

# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
from typing import List, Optional
from Include.PyLeetcode.Tree.Tree import TreeNode


class Solution:
    def binaryTreePaths(self, root: Optional[TreeNode]) -> List[str]:
        ret = []
        path = []

        def dfs(node: Optional[TreeNode]) -> None:
            if not node: return

            path.append(node.val)

            if not node.left and not node.right:
                ret.append('->'.join(map(str, path)))   # 原来错误的写法：ret.append('->'.join(path)) =》 join() 方法只能用于字符串列表，而传入的是整数列表

            dfs(node.left)
            dfs(node.right)

            path.pop()

        dfs(root)

        return ret
