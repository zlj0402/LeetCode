"""
@brief: Leetcode_2130_链表最大孪生和  
@link: https://leetcode.cn/problems/maximum-twin-sum-of-a-linked-list/description/  
@author: liangj.zhang  
@date: 24/10/2025  

@Difficulty: Medium  

@Label: Fast and Slow Pointers、Reverse LinkedList  

@Retrospect(worthy 1 - 5): 3  

@thoughts:
 + 【思路 1】：快慢指针 + 反转链表  
     思路和 《Leetcode_234》是一样的，  
     这次先尝试了不带 “虚拟头结点” dhead（后半部分的前一个节点）的方式，不太行，dhead 会一直指向原来的下一个节点，比如：  
     1 -> 2 -> 3 -> 4 -> 5 -> 6  

     1 -> 2 -> 3 ↘  
          6 -> 5 -> 4  
     最后还是换了带 “虚拟头节点” dhead 的方式；就是本题的 reverseLinkedList(dhead)；  

     + 分析：  
         + 时间复杂度：O(n)  
         + 空间复杂度：O(1)  
     + rank:  
         + 时间效率：48 ms, 击败 98.58%  
         + 空间效率：46.89 MB, 击败 8.64%  
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
        while cur.next:
            next = cur.next
            cur.next = next.next

            next.next = dhead.next
            dhead.next = next
        
    def pairSum(self, head: Optional[ListNode]) -> int:
        slow = fast = head
        last_slow = None
        while fast and fast.next:
            last_slow = slow
            slow = slow.next
            fast = fast.next.next

        self.reverseLinkedList(last_slow)

        fast = last_slow.next
        slow = head
        max_sum = 0

        while slow != last_slow.next:
            if max_sum < slow.val + fast.val:
                max_sum = slow.val + fast.val
            slow = slow.next
            fast = fast.next
        
        return max_sum