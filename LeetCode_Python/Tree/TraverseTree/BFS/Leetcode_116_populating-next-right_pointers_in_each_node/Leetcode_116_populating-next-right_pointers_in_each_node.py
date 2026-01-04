"""
@brief: Leetcode_116_填充每个节点的下一个右侧节点指针
@link: https://leetcode.cn/problems/populating-next-right-pointers-in-each-node/description/
@author: liangj.zhang
@date: 4/1/2026

@Difficulty: Medium

@Label: BFS

@Retrospect (worthy 1 - 5): 4

@thoughts:
 + 【思路 1】：BFS + 链表
     这个思路是看了灵神的题解，才意识到的：
     上一层既然是链表，想办法记住上一次的头，
     是不是就能不需要额外的 O(n) 空间了；
     这个方式也非常优雅;
     ----
     第一层就一个节点，就当它是已经链起来的链表；
     内部循环 用一个 dummy 节点，并用一个“指针” nxt 指向 dummy
     先将当前节点 cur 的左节点串入链表 => nxt.mext = cur.left，然后 nxt 向右移动到新的节点上，
     再将当前节点 cur 的右节点串入链表 => nxt.next = cur.right，
     遍历到下一个链表节点 cur.next；
        --
        内部循环结束，
        将 cur 赋值为新串起来的链表的头，dummy.next
        --
        就开始有一次循环了
    
     + 分析：
         + 时间复杂度：O(n)
         + 空间复杂度：O(1)
     + rank:
         + 时间效率：51 ms, 击败 83.13%
         + 空间效率：18.36 MB, 击败 96.51%
"""

"""
# Definition for a Node.
class Node:
    def __init__(self, val: int = 0, left: 'Node' = None, right: 'Node' = None, next: 'Node' = None):
        self.val = val
        self.left = left
        self.right = right
        self.next = next
"""

# Definition for a Node.
class Node:
    def __init__(self, val: int = 0, left: 'Node' = None, right: 'Node' = None, next: 'Node' = None):
        self.val = val
        self.left = left
        self.right = right
        self.next = next

class Solution:
    def connect(self, root: 'Optional[Node]') -> 'Optional[Node]':
        cur = root
        while cur:
            nxt = dummy = Node()
            
            while cur:
                if cur.left:
                    nxt.next = cur.left
                    nxt = nxt.next
                if cur.right:
                    nxt.next = cur.right
                    nxt = nxt.next
                cur = cur.next
            cur = dummy.next
        return root