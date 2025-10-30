"""
@brief: Leetcode_203_移除链表元素  
@link: https://leetcode.cn/problems/remove-linked-list-elements/description/  
@author: liangj.zhang  
@date: 30/10/2025  

@Difficulty: Easy  

@Label: Delete Node  

@Retrospect(worthy 1 - 5): 1  

@thoughts:
 + 【思路 1】：考虑到可能会有删除第一个节点的情况，使用 dummy head 的方式更合适  
     + 分析：  
         + 时间复杂度：O(n)  
         + 空间复杂度：O(1)  
     + rank:  
         + 时间效率：0 ms, 击败 100%  
         + 空间效率：19.42 MB, 击败 12.53%  
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
    def removeElements(self, head: Optional[ListNode], val: int) -> Optional[ListNode]:
        dummy = ListNode(-1, head)
        cur = dummy
        while cur.next:
            if cur.next.val == val:
                cur.next = cur.next.next
            else:
                cur = cur.next
        return dummy.next