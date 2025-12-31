"""
@brief: Leetcode_513_找树左下角的值
@link: https://leetcode.cn/problems/find-bottom-left-tree-value/description/
@author: liangj.zhang
@date: 31/12/2025

@Difficulty: Medium

@Label: BFS

@Retrospect(worthy 1 - 5): 3

@thoughts:
 + 【思路 1】：BFS，记录每一层第一个值；
     推出循环时的那个记录值就是结果；

     + 分析：
         + 时间复杂度：O(n)
         + 空间复杂度：O(1)，但我申请这么大数组，其实也是 O(n)
     + rank:
         + 时间效率：0 ms, 击败 100%
         + 空间效率：18.95 MB, 击败 97.55%

 + 【思路 2】：DFS，记录最大深度变化时的那个值；
     DFS 理论上可以比 BFS 更先找到结果，但是递归有额外消耗；
     留着以后做吧；
"""

# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right

from collections import deque

class Solution:
    def findBottomLeftValue(self, root: Optional[TreeNode]) -> int:
        q = deque([root])
        ret = root.val
        while q:
            level_size = len(q)
            ret = q[0].val
            for _ in range(level_size):
                node = q.popleft()
                if node.left: q.append(node.left)
                if node.right: q.append(node.right)
        return ret