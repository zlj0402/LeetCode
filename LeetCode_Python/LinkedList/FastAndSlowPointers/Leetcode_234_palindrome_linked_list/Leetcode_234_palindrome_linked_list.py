"""
@brief: Leetcode_234_回文链表  
@link: https://leetcode.cn/problems/palindrome-linked-list/description/  
@author: liangj.zhang  
@date: 23/10/2025  

@Difficulty: Easy  

@Label: Reverse LinkedList、Fast and Slow Pointers  

@Retrospect(worthy 1 - 5): 3  

@thoughts:
 + 【思路 1】：反转链表 + 快慢指针  
     这题跟 《Leetcode_234_重排链表》一样，先 快慢指针 找到中点，再将后半部分反转；  
     剩下的是属于本题的逻辑处理过程：比较前半部分和反转后的后半部分；  
     + 分析：  
         + 时间复杂度：O(n)  
         + 空间复杂度：O(1)  
     + rank:  
         + 时间效率：38 ms, 击败 53.17%  
         + 空间效率：38.7 MB, 击败 15.25%  
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
        if cur is None: return
        while cur.next:
            next = cur.next
            cur.next = next.next

            next.next = dhead.next
            dhead.next = next

    def isPalindrome(self, head: Optional[ListNode]) -> bool:
        slow = fast = head
        last_slow = None
        while fast and fast.next:
            last_slow = slow
            slow = slow.next
            fast = fast.next.next

        dhead = slow if fast else last_slow
        self.reverseLinkedList(dhead)

        pre, last = head, dhead.next
        while last:
            if pre.val != last.val:
                return False
            pre = pre.next
            last = last.next

        return True
