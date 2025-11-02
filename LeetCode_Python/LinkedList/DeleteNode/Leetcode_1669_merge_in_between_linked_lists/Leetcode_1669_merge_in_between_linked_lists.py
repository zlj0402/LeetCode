"""
@brief: Leetcode_1669_合并两个链表
@link: https://leetcode.cn/problems/merge-in-between-linked-lists/description/
@author: liangj.zhang
@date: 2/11/2025

@Difficulty: Medium

@Label: Delete Node

@Retrospect(worthy 1 - 5): 2

@thoughts:
    + 【思路 1】：在 list1 当中找到下标 a 的前一个节点，找到下标 b 的后一个节点；
        + 条件: 1 <= a <= b < list1.length - 1
            ==> 不需要考虑边界，[a, b] 范围严格在 (0, list1.length) 之间；
    
    + 解题过程：
        1. 遍历 list1，找到位置 a - 1 的节点 pre；
        2. 再遍历到位置 b + 1 的节点 next；
        3. 将 pre->next 指向 list2；
        4. 找到 list2 的末尾节点，将其 next 指向 next；
        5. 返回 list1。

    + 分析：
        + 时间复杂度：O(b + n)，其中 b 为索引值，n 为 list2 的长度
        + 空间复杂度：O(1)
    + rank:
        + 时间效率：206 ms, 击败 84.94%
        + 空间效率：22.29 MB, 击败 44.32%
"""

import os
import sys

print(os.path.join(os.path.dirname(__file__)))
print(os.path.abspath(os.path.join(os.path.dirname(__file__), "../../../.."))) #f:\Code\zljgit\LeetCode
sys.path.append(os.path.abspath(os.path.join(os.path.dirname(__file__), "../../../..")))

from Include.PyLeetcode.LinkedList.LinkedList import ListNode

# Definition for singly-linked list.
# class ListNode:
#     def __init__(self, val=0, next=None):
#         self.val = val
#         self.next = next
class Solution:
    def mergeInBetween(self, list1: ListNode, a: int, b: int, list2: ListNode) -> ListNode:
        cur = list1
        pre = next = None
        i = 0

        while i + 1 < a:
            i += 1
            cur = cur.next
        pre = cur
        while i + 1 <= b + 1:
            i = i + 1
            cur = cur.next
        next = cur

        pre.next = list2
        while pre.next: 
            pre = pre.next
        pre.next = next

        return list1