"""
@brief: Leetcode_25_K个一组翻转链表
@link: https://leetcode.cn/problems/reverse-nodes-in-k-group/description/
@author: liangj.zhang
@date: 13/10/2025

@Difficulty: Hard

@Label: Reverse LinkedList

@Retrospect(worthy 1 - 5): 4

@thoughts:
 + 【思路 1】：用带 dummy_head 的方式
     在写过下面两题：
         + 简单题：Leetcode_206_反转链表
         + 中等题：Leetcode_92_反转链表_II
     尤其是 Leetcode_92 这题之后，充分理解了带 dummy_head 和不带 dummy_head 两者之间的差别之后，
     写这题尤为简单，甚至接近一遍通过;（内循环的范围原来多带了个等号，立马就给它去掉通过了）
         + 带 dummy_head 的方式，一直是一条链；
         + 不带 dummy_head 的方式，虽分离的都是原来的节点，但是分离出的是另一条链；
     
     + 分析：
         + 时间复杂度：O(n)，最多遍历两遍链表
         + 空间复杂度：O(1)

     + rank:
         + 时间效率：0 ms, 击败 100%
         + 空间效率：18.14 MB, 击败 92.88%
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
    def reverseKGroup(self, head: Optional[ListNode], k: int) -> Optional[ListNode]:
        dummy = ListNode(val=-1, next=head)
        dhead = dummy

        while dhead:

            # 翻转的前提条件：后续有 k 个节点
            cnt = 0
            p = dhead
            while p is not None and cnt < k:
                p = p.next
                cnt += 1
            if p is None or cnt < k:
                break

            # 翻转
            cnt = 1
            p = dhead.next
            # print(p.val)
            while cnt < k:
                next_node = p.next
                # print(next_node.val)
                p.next = next_node.next

                next_node.next = dhead.next
                dhead.next = next_node
                cnt += 1
            dhead = p

        return dummy.next
    

def main():
    k = 5
    head = SortTestHelper.generate_random_array(k, 0, 100)
    linkedlst = ListNode.build_list(head)
    ListNode.print_list(linkedlst)

    linkedlst = Solution().reverseKGroup(head=linkedlst, k=k)

    print()
    ListNode.print_list(linkedlst)

if __name__ == "__main__":
    main()