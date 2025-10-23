"""
@brief: Leetcode_143_重排链表
@link: https://leetcode.cn/problems/reorder-list/description/
@author: liangj.zhang
@date: 23/10/2025

@Difficulty: Medium

@Label: Fast and Slow Pointers, Reverse LinkedList

@Retrospect(worthy 1 - 5): 4

@thoughts:
    + 【思路 1】：快慢指针 + 反转链表
        思路是先找到链表的中点，然后将后半部分链表反转，
        最后将后半部分的节点依次插入到前半部分节点之间。

        当链表长度为偶数时，后半部分节点比前半部分少一个，
        所以最后一个节点没有插入位置；
        当链表长度为奇数时，后半部分正好可以全部插入。

        + 分析：
            + 时间复杂度：O(n)
            + 空间复杂度：O(1)
        + rank:
            + 时间效率：0 ms, 击败 100%
            + 空间效率：22.79 MB, 击败 89.71%
"""

import os
import sys

print(os.path.join(os.path.dirname(__file__)))
print(os.path.abspath(os.path.join(os.path.dirname(__file__), "../../../.."))) #f:\Code\zljgit\LeetCode
sys.path.append(os.path.abspath(os.path.join(os.path.dirname(__file__), "../../../..")))

from typing import Optional

from Include.PyLeetcode.LinkedList.LinkedList import ListNode

# Definition for singly-linked list.
# class ListNode:
#     def __init__(self, val=0, next=None):
#         self.val = val
#         self.next = next
class Solution:
    def reverseLinkedList(self, dhead: Optional[ListNode]) -> None:
        cur = dhead.next
        while cur and cur.next:
            next = cur.next
            cur.next = next.next

            next.next = dhead.next
            dhead.next = next

    def reorderList(self, head: Optional[ListNode]) -> None:
        """
        Do not return anything, modify head in-place instead.
        """
        slow = fast = head
        last_slow = None
        while fast and fast.next:
            last_slow = slow
            slow = slow.next
            fast = fast.next.next

        dhead = slow if fast else last_slow
        self.reverseLinkedList(dhead)

        # cur 从后半段第一个节点开始, pre 从头结点开始
        cur = dhead.next
        pre = head
        while pre is not dhead:
            # 先脱离后面的节点
            cur_next = cur.next
            dhead.next = cur_next
            # 连接
            cur.next = pre.next
            pre.next = cur
            # 指向变动
            pre = cur.next
            cur = cur_next