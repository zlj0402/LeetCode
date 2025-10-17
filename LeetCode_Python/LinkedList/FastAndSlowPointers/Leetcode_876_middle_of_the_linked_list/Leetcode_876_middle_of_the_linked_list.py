"""
@brief: Leetcode_876_链表的中间节点
@link: https://leetcode.cn/problems/middle-of-the-linked-list/description/
@author: liangj.zhang
@date: 17/10/2025

@Difficulty: Easy

@Label: Fast And Slow Pointers

@Retrospect(worthy 1 - 5): 2

@thoughts:
 + 【思路 1】：快慢指针
     题目的条件，指出，最少一个节点
     初始状态，fast / slow 指针都指向头指针；
     slow 一次走一步，fast 一次走两步
     循环终止条件：fast && fast.next 不为 None，在图上画一画，很容易就明白了；
     比计数的方式，优雅一些；且少一遍遍历
     + 分析：
         + 时间复杂度：O(n)
         + 空间复杂度：O(1)
     + rank:
         + 时间效率：0 ms, 击败 100%
         + 空间效率：17.42 MB, 击败 66.47%
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
    def middleNode(self, head: Optional[ListNode]) -> Optional[ListNode]:
        fast = slow = head
        while fast and fast.next:
            fast = fast.next.next
            slow = slow.next
        return slow