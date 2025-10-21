"""
@brief: Leetcode_142_环形链表_II
@link: https://leetcode.cn/problems/linked-list-cycle-ii/description/
@author: liangj.zhang
@date: 21/10/2025

@Difficulty: Medium

@Label: Fast and Slow Pointers

@Retrospect(worthy 1 - 5): 4

@thoughts:
    + 【思路 1】：快慢指针
        上面 // 注释，以前的写法并不标准，但也是一种解法；
        标准写法要求不得修改链表节点。

        标准写法基于数学推导：
            + 假设是循环链表：
                + a 是圈之外的部分；
                + b 是 slow 在圈内走的距离；
                + c 是 圈的长度 - slow 在圈内走的距离；
            当快慢指针第一次相遇时，快指针可能已经绕圈多次：
                2 * (a + b) = a + b + k * (b + c)
                => a + b = k * (b + c)
                => a - c = (k - 1) * (b + c)
            意味着：
                从相遇点开始，head 和 slow 都以每次一步的速度前进，
                当 slow 先走 c 步时，head 距离相遇点还有 a - c，
                而 a - c 是一圈 (b + c) 的倍数，
                所以两者最终会在环的起点相遇。

        + 分析：
            + 时间复杂度：O(n)
            + 空间复杂度：O(1)
        + rank:
            + 时间效率：11 ms, 击败 39.6%
            + 空间效率：10.98 MB, 击败 98.93%
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
#     def __init__(self, x):
#         self.val = x
#         self.next = None

class Solution:
    def detectCycle(self, head: Optional[ListNode]) -> Optional[ListNode]:
        slow = fast = head
        meet = False
        while fast and fast.next:
            slow = slow.next
            fast = fast.next.next
            if slow == fast:
                meet = True
                break
        if not meet: return None

        slow = fast
        while slow != head:
            slow = slow.next
            head = head.next

        return slow