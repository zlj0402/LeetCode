"""
@brief: Leetcode_24_两两交换链表中的节点
@link: https://leetcode.cn/problems/swap-nodes-in-pairs/description/
@author: liangj.zhang
@date: 14/10/2025

@ps: 以前的答题思路也留下来不删除了，以后更新也放这条注释里

@Difficulty: Medium

@Label: Reverse LinkedList

@Retrospect(worthy 1 - 5): 3

@thoughts:
 + 【思路 1】：带 dummy_head 的方式
     做过 《Leetcode_25_K个一组翻转链表》之后做这一题的，显然更容易点这道题；
     标准的 K个一组翻转，还得是 Leetcode_25;
     这道题，两个一组翻转，我们很容易下次翻转的前提条件，有足够的个数，这里是 2;
     所以可以简化为单循环就可以了;

     + 分析：
         + 时间复杂度：O(n)
         + 空间复杂度：O(1)
     + rank:
         + 时间效率：0 ms, 击败 100%
         + 空间效率：17.51 MB, 击败 46.95%
"""

import os
import sys

print(os.path.join(os.path.dirname(__file__)))
print(os.path.abspath(os.path.join(os.path.dirname(__file__), "../../.."))) #f:\Code\zljgit\LeetCode
sys.path.append(os.path.abspath(os.path.join(os.path.dirname(__file__), "../../..")))

from typing import Optional

from Include.PyLeetcode.LinkedList.LinkedList import ListNode
from Include.PyLeetcode.sort_test_helper import SortTestHelper

# Definition for singly-linked list.
# class ListNode:
#     def __init__(self, val=0, next=None):
#         self.val = val
#         self.next = next


class Solution:
    def swapPairs(self, head: Optional[ListNode]) -> Optional[ListNode]:
        dummy = ListNode(-1, head)
        dhead = dummy

        cur = dhead
        while cur:
            next_node = cur.next
            if next_node is None: break
            cur.next = next_node.next

            next_node.next = dhead.next
            dhead.next = next_node

            # dhead -> 下一次链表翻转范围的前一个节点
            dhead = cur
            cur = dhead.next

        return dummy.next