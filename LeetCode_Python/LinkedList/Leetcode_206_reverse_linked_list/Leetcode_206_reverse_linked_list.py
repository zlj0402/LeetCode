"""
@brief: Leetcode_206_反转链表
@link: https://leetcode.cn/problems/reverse-linked-list/description/
@author: liangj.zhang
@date: 11/10/2024

@updated: 
    + 11/10/2025 -- add 不带虚拟头结点思路

@Difficulty: Easy

@Label: Reverse LinkedList

@Retrospect(worthy 1 - 5): 4

@thoughts:
+ 【思路 1】：单链表反转 -- 带虚拟头结点的方式
    dummy_head  ->  1  ->  2  ->  3  ->  4  ->  5
                     cur

                     2  ->  3  ->  4  ->  5
    dummy_head  ->  1  ↗

                                    3  ->  4  ->  5
    dummy_head  ->  2  ->  1  ↗

    dummy_head  ->  2  ->  1  ->  3  ->  4  ->  5
                            cur

                             3  ->  4  ->  5
    dummy_head  ->  2  ->  1  ↗

                                           4  ->  5
    dummy_head  ->  3  ->  2  ->  1  ↗
    以此类推...

+ 【思路 2】：单链表反转 -- 不带虚拟头结点的方式 -- 11/10/2025
初始状态：
    1  ->  2  ->  3  ->  4  ->  5  ->  NULL
    ⭡
   cur
   NULL
    ⭡
    p

第一次循环：
    1  ->  2  ->  3  ->  4  ->  5  ->  NULL
    ⭡      ⭡
   cur    next
   NULL
    ⭡
    p

             2  ->  3  ->  4  ->  5  ->  NULL
             ⭡
            next
    1  -> NULL
    ⭡      ⭡
   cur     p

             2  ->  3  ->  4  ->  5  ->  NULL
             ⭡
            cur
    1  -> NULL
    ⭡
    p

第二次循环：
             2  ->  3  ->  4  ->  5  ->  NULL
             ⭡      ⭡
            cur    next
    1  -> NULL
    ⭡
    p

                    3  ->  4  ->  5  ->  NULL
                    ⭡
                   next
    2  ->  1  -> NULL
    ⭡      ⭡
   cur     p

                    3  ->  4  ->  5  ->  NULL
                    ⭡
                   cur
    2  ->  1  -> NULL
    ⭡
    p

以此类推...

    分析：
        - 时间复杂度：O(n)
        - 空间复杂度：O(1)
    rank:
        - 时间效率：0 ms, 击败 100%
        - 空间效率：18.41 MB, 击败 48.85%

@ps:
    + 目前只写了不用 dummy_head 的方式
"""

import os
import sys

# print(os.path.join(os.path.dirname(__file__)))
# print(os.path.abspath(os.path.join(os.path.dirname(__file__), "../../../Include")))
sys.path.append(os.path.abspath(os.path.join(os.path.dirname(__file__), "../../../Include")))

from typing import Optional
from PyLeetcode.LinkedList.LinkedList import ListNode
from PyLeetcode.sort_test_helper import SortTestHelper

# Definition for singly-linked list.
# class ListNode:
#     def __init__(self, val=0, next=None):
#         self.val = val
#         self.next = next

#【思路 2】：单链表反转 -- 不带虚拟头结点的方式 -- 11/10/2025
class Solution:
    def reverseList(self, head: Optional[ListNode]) -> Optional[ListNode]:
        cur = head
        next = None
        p = None

        while cur is not None:
            next = cur.next
            cur.next = p
            p = cur
            cur = next
        return p

def main():
    head = SortTestHelper.generate_random_array(10, 0, 100)
    linkedlst = ListNode.build_list(head)
    ListNode.print_list(linkedlst)    

if __name__ == "__main__":
    main()