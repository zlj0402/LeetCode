"""
@brief: Leetcode_117_填充每个节点的下一个右侧节点指针_II
@link: https://leetcode.cn/problems/populating-next-right-pointers-in-each-node-ii/description/
@author: liangj.zhang
@date: 5/1/2026

@Difficulty: Medium

@Label: BFS

@Retrospect(worthy 1 - 5): 4

@thoughts:
 + 【思路 1】：BFS + 链表
     Leetcode_116 的空间复杂度 O(1) 的办法是通用的，不论树是何种状态，只要是树就可以；

     + 分析：
         + 时间复杂度：O(n)
         + 空间复杂度：O(1)
     + rank:
         + 时间效率：7 ms, 击败 93.58%
         + 空间效率：18.64 MB, 击败 66.14%
"""


# Definition for a Node.
class Node:
    def __init__(self, val: int = 0, left: 'Node' = None, right: 'Node' = None, next: 'Node' = None):
        self.val = val
        self.left = left
        self.right = right
        self.next = next

class Solution:
    def connect(self, root: 'Node') -> 'Node':
        cur = root
        while cur:
            node = Node()
            nxt = node

            while cur:
                if cur.left:
                    nxt.next = cur.left
                    nxt = nxt.next
                if cur.right:
                    nxt.next = cur.right
                    nxt = nxt.next
                cur = cur.next
            cur = node.next
        return root