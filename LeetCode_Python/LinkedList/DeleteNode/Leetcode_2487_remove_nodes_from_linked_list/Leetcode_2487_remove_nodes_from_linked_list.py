"""
@brief: Leetcode_2487_从链表中移除节点
@link: https://leetcode.cn/problems/remove-nodes-from-linked-list/description/
@author: liangj.zhang
@date: 1/11/2025

@Difficulty: Medium

@Label: Reverse LinkedList, Delete Node

@Retrospect(worthy 1 - 5): 4

@thoughts:
    + 【思路 1】：反转链表 + 过滤节点，再反转链表
        视觉上，可以将数字看成对应高度的柱子；
        题目的要求转化为：留下的柱子，其左边没有比它更高的柱子。

        从右向左投影来看：
            从最右边的柱子开始向 y 轴投影；
            先投影的柱子在 y 轴上留下印记；
            已留下印记的柱子中，比当前柱子高的将其遮挡；
            只有 >= 已留下印记的柱子，才会留下（即能凸显出来）。
        
        因此：
            解题过程是先反转链表，从反转后的第一个节点开始遍历；
            只保留值 >= 当前节点值的节点；
            最后再反转回来，得到结果链表。

    + 分析：
        + 时间复杂度：O(n)
        + 空间复杂度：O(1)
    + rank:
        + 时间效率：83 ms, 击败 97.57%
        + 空间效率：48.23 MB, 击败 54.21%
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
    def reverseLinkedList(self, head: Optional[ListNode]) -> Optional[ListNode]:
        p = None
        cur = head
        while cur:
            next = cur.next
            cur.next = p

            p = cur
            cur = next
        return p
    
    def removeNodes(self, head: Optional[ListNode]) -> Optional[ListNode]:
        head= self.reverseLinkedList(head)
        cur = head
        while cur.next:
            if cur.next.val >= cur.val:
                cur = cur.next
            else:
                cur.next = cur.next.next
        return self.reverseLinkedList(head)