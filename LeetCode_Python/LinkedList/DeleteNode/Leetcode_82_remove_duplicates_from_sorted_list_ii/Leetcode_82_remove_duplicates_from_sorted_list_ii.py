"""
@brief: Leetcode_82_删除排序链表中的重复元素_II  
@link: https://leetcode.cn/problems/remove-duplicates-from-sorted-list-ii/description/  
@author: liangj.zhang  
@date: 29/10/2025  

@Difficulty: Medium  

@Label: Delete Node  

@Retrospect(worthy 1 - 5): 3  

@thoughts:

 + 【思路 1.2】：满足有重复值为前提（cur 的后两个值相同），先保留值，然后不断删除等 val 的节点；  
     + 分析：  
         + 时间复杂度：O(n)  
         + 空间复杂度：O(1)  
     + rank:  
         + 时间效率：0 ms, 击败 100%  
         + 空间效率：17.43 MB, 击败 84.73%  
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

#【思路 1.2】
class Solution:
    def deleteDuplicates(self, head: Optional[ListNode]) -> Optional[ListNode]:
        dummy = ListNode(-101, head)
        cur = dummy
        while cur.next and cur.next.next:
            val = cur.next.val
            if cur.next.next.val == val:
                while cur.next and cur.next.val == val:
                    cur.next = cur.next.next
            else:
                cur = cur.next
        return dummy.next