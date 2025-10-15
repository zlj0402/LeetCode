"""
@brief: Leetcode_92_反转链表_II
@link: https://leetcode.cn/problems/reverse-linked-list-ii/description/
@author: liangj.zhang
@date: 12/10/2025

@Difficulty: Medium

@Label: Reverse LinkedList

@Retrospect(worthy 1 - 5): 4

@thoughts:
 + 【思路 1】：用带 dummy_head 的方式
     + 不带 dummy_head 的话，额外要做：
         + 记住 left 节点前面一个节点；
         + 记住 right 节点后面一个节点；（后面这个节点就需要，先遍历一遍，多一遍O(n)，俺不乐意）
     + >>> 不带 dummy_head 的话，虽都是那些节点，但分离节点的过程是脱离原来的链表的；<<<
     + >>> 带 dummy_head 的方式，分离的节点，一直都是在原来的链子上面，一条链；<<<

     + 分析：
         + 时间复杂度：O(right)
         + 空间复杂度：O(1)

     + rank:
         + 时间效率：0 ms, 击败 100%
         + 空间效率：10.95 MB, 击败 80.36%
"""

import os
import sys

# print(os.path.join(os.path.dirname(__file__)))
# print(os.path.abspath(os.path.join(os.path.dirname(__file__), "../../../Include")))
sys.path.append(os.path.abspath(os.path.join(os.path.dirname(__file__), "../../../Include")))

from typing import Optional
from PyLeetcode.LinkedList.LinkedList import ListNode

# Definition for singly-linked list.
# class ListNode:
#     def __init__(self, val=0, next=None):
#         self.val = val
#         self.next = next
class Solution:
    def reverseBetween(self, head: Optional[ListNode], left: int, right: int) -> Optional[ListNode]:
        if left == right: return head
        dummy_head = ListNode(-1, head)
        i = 1
        cur = dummy_head

        while i < left:
            i += 1
            cur = cur.next
        # 离开 while loop 后，i == left

        dhead = cur
        cur = dhead.next
        while cur.next and i < right:
            nextNode = cur.next
            cur.next = nextNode.next

            nextNode.next = dhead.next
            dhead.next = nextNode

            i+= 1
        
        return dummy_head.next
