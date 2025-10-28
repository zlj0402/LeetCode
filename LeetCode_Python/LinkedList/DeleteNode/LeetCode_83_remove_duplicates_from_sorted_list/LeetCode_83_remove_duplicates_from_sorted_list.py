"""
@brief: Leetcode_83_删除排序链表中的重复元素  
@link: https://leetcode.cn/problems/remove-duplicates-from-sorted-list/description/  
@author: liangj.zhang  
@date: 28/10/2025  

@Difficulty: Easy  

@Label: Delete Node  

@Retrospect(worthy 1 - 5): 3  

@thoughts:
 + 【思路 1】：比较当前指针与下一个节点值  
     ps: 原来自己的第一次写法，还是用额外空间来记录值；不知道当时有没有注意是已经排序的链表；  
     今天写之前，可能是收了昨天写 Leetcode_19 的影响，第一想法用两个指针；  
     行，肯定是可以的；但不如一个指针轻便；  

     + 分析：  
         + 时间复杂度：O(n)  
         + 空间复杂度：O(1)  
     + rank:  
         + 时间效率：0 ms, 击败 100%  
         + 空间效率：17.69 MB, 击败 22.04%  
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
    def deleteDuplicates(self, head: Optional[ListNode]) -> Optional[ListNode]:
        if head is None: return head
        cur = head
        while cur.next:
            if cur.val != cur.next.val:
                cur = cur.next
                continue
            cur.next = cur.next.next
        return head