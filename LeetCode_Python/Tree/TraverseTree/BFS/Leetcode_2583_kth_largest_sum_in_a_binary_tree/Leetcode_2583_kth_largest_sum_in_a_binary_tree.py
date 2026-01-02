"""
@brief: Leetcode_2583_二叉树中的第 K 大层和
@link: https://leetcode.cn/problems/kth-largest-sum-in-a-binary-tree/description/
@author: liangj.zhang
@date: 2/1/2026

@Difficulty: Medium

@Label: BFS + priority_queue

@Retrospect(worthy 1 - 5): 4

@thoughts:
 + 【思路 1】：BFS + priority_queue
     第 k 个数值，这类需求，我现在的第一想法就是 大小顶堆 维持 k 个数据；
     不用手写大小顶堆，就用 priority_queue;
     BFS：这几天都在写这类题，我已经很熟悉了，更何况 samsung 的 ADV 主要考的就是这类题；
     ----
     heapq\deque 练手的一题
     
     + 分析：
         + 时间复杂度：O(n) + h * O(logk) [h -> 树的高度，k 是放入的节点数]
         + 空间复杂度：O(h)[priority_queue, 最多 O(n)] + O(n)[queue] => O(n)
     + rank:
         + 时间效率：195 ms, 击败 16.61%
         + 空间效率：54.70 MB, 击败 5.30%
    ----
    我觉得是库带来的开销，deque 不如直接换成数组，
    heapq 不如直接换成一个 list，最后 [].sort() 一下
"""

# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right

from cmath import inf
from collections import deque
import heapq

class FixedSizePriQue:
    def __init__(self, max_size: int):
        self.heap = []
        self.max_size = max_size

    def push(self, val):
        if self.heap.__len__() < self.max_size:
            heapq.heappush(self.heap, val)
        elif val > self.heap[0]:
            heapq.heappushpop(self.heap, val)
    
    def top(self):
        return self.heap[0] if self.heap.__len__() > 0 else inf
    
    def size(self):
        return self.heap.__len__()

class Solution:
    def kthLargestLevelSum(self, root: Optional[TreeNode], k: int) -> int:
        q = deque([root])
        fspq = FixedSizePriQue(k)

        while q:
            _sum = 0
            size = q.__len__()
            for _ in range(size):
                cur = q.popleft()
                _sum += cur.val
                if cur.left: q.append(cur.left)
                if cur.right: q.append(cur.right)
            fspq.push(_sum)

        return fspq.top() if fspq.size() >= k else -1
    
# 第一条柱子的做法：最基础，又简洁，留着记录一下
class Solution:
    def kthLargestLevelSum(self, root: Optional[TreeNode], k: int) -> int:
        a=[]
        q=[root]
        while q:
            s = 0
            tmp = q
            q = []
            for node in tmp:
                s +=node.val
                if node.left:
                    q.append(node.left)
                if node.right:
                    q.append(node.right)
            a.append(s)
        if k>len(a):
            return -1
        a.sort()
        return a[-k]