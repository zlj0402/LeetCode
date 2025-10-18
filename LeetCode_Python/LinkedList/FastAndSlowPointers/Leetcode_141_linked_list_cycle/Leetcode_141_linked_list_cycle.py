"""
@brief: Leetcode_141_环形链表
@link: https://leetcode.cn/problems/linked-list-cycle/description/
@author: liangj.zhang
@date: 18/10/2025

@Difficulty: Easy

@Label(worthy 1 - 5): 2

@thoughts:
    + 【思路 1】：快慢指针
        去年就用 C++ 写过，还是很简单的；

        + 分析：
            + 时间复杂度：O(n)
            + 空间复杂度：O(1)
        + rank:
            + 时间效率：49 ms, 击败 82.46%
            + 空间效率：19.46 MB, 击败 71.91%

    + 【思路 1.2】：快慢指针 + 剪枝
        写完之后，我觉得可以剪枝；slow / fast 都不变，加上：slow 行走时，如果值 <= 10000，那么将其往左偏移 16 位；遇到一个值大于 10000 的数，就可以确定有环了；
        + 分析：
            + 时间复杂度：O(n)
            + 空间复杂度：O(1)
        + rank:
            + 时间效率：53 ms, 击败 64.85%
            + 空间效率：19.43 MB, 击败 80.81%
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

#【思路 1.2】：快慢指针 + 剪枝
class Solution:
    def hasCycle(self, head: Optional[ListNode]) -> bool:
        slow = fast = head
        while fast and fast.next:
            if slow.val > 100000 or fast.val > 100000:
                return True
            elif slow.val <= 100000:
                slow.val += 200000
            
            slow = slow.next
            fast = fast.next.next
            if slow == fast:
                return True
        return False

# 【思路 1】：快慢指针
"""
class Solution:
    def hasCycle(self, head: Optional[ListNode]) -> bool:
        slow = fast = head
        while fast and fast.next:
            slow = slow.next
            fast = fast.next.next
            if slow == fast:
                return True
        return False
"""