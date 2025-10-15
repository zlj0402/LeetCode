"""
@brief: Leetcode_445_两数相加_II
@link: https://leetcode.cn/problems/add-two-numbers-ii/description/
@author: liangj.zhang
@date: 15/10/2025

@Difficulty: Medium

@Label: Reverse LinkedList

@Retrospect(worthy 1 - 5): 3

@thoughts:
 + 【思路 1】：翻转链表
     翻转链表的时候，顺便得到链表的长度；借此找到最长的链表；
     后续的加法结果，复用该最长的链表；注意末端可能有进位产生的新节点；
     最后再反转一次链表，结果正序；

     + 分析：
         + 时间复杂度：O(n)，遍历链表
         + 空间复杂度：O(1)，进位最多新增一个节点；
     + rank:
         + 时间效率：0 ms, 击败 100%
         + 空间效率：17.58 MB, 击败 58.71%
"""

import os
import sys

print(os.path.join(os.path.dirname(__file__)))
print(os.path.abspath(os.path.join(os.path.dirname(__file__), "../../.."))) #f:\Code\zljgit\LeetCode
sys.path.append(os.path.abspath(os.path.join(os.path.dirname(__file__), "../../..")))

from typing import Optional, Tuple

from Include.PyLeetcode.LinkedList.LinkedList import ListNode
from Include.PyLeetcode.sort_test_helper import SortTestHelper

# Definition for singly-linked list.
# class ListNode:
#     def __init__(self, val=0, next=None):
#         self.val = val
#         self.next = next
class Solution:

    @staticmethod
    def reverseLinkedList(head: Optional[ListNode]) -> Tuple[Optional[ListNode], int]:
        len = 0
        cur = head
        p = None

        while cur:
            next = cur.next
            cur.next = p

            p = cur
            cur = next
            len += 1
        
        return p, len

    def addTwoNumbers(self, l1: Optional[ListNode], l2: Optional[ListNode]) -> Optional[ListNode]:
        l1, len1 = Solution.reverseLinkedList(l1)
        l2, len2 = Solution.reverseLinkedList(l2)

        max_lst = l1 if len1 >= len2 else l2
        min_lst = l2 if len1 >= len2 else l1

        res_lst = max_lst
        last_max_node = None
        flag = False    # 是否有进位
        while max_lst and min_lst:
            max_lst.val += min_lst.val
            if flag:
                max_lst.val += 1
                flag = False
            if max_lst.val >= 10:
                flag = True
                max_lst.val %= 10

            last_max_node = max_lst
            max_lst = max_lst.next
            min_lst = min_lst.next
        
        while flag:
            if max_lst:
                max_lst.val += 1
                flag = False

                if max_lst.val >= 10:
                    flag = True
                    max_lst.val %= 10
                    last_max_node = max_lst
                    max_lst = max_lst.next
            else:
                assert last_max_node is not None
                last_max_node.next = ListNode(1)
                flag = False

        return Solution.reverseLinkedList(res_lst)[0]
    
def main():
    lst1 = [5]
    lst2 = [5]
    l1 = ListNode.build_list(lst1)
    l2 = ListNode.build_list(lst2)
    
    res = Solution().addTwoNumbers(l1, l2)

    ListNode.print_list(res)

if __name__ == "__main__":
    main()
