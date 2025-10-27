"""
@brief: Leetcode_19_删除链表的倒数第 N 个结点
@link: https://leetcode.cn/problems/remove-nth-node-from-end-of-list/description/
@author: liangj.zhang
@date: 27/10/2025

@Difficulty: Medium

@Label: Two Pointers, Delete Node

@Retrospect(worthy 1 - 5): 3

@thoughts:
 + 【思路 1】：双指针
     ps: 以前的方式是申请同等长的指针数组，空间复杂度较高，在实际应用中不太好，
         但如果用静态的 MAX_NODE 数组实现，作为算法题解法还是不错的；
     回到本题：
     目标是删除倒数第 n 个节点，也就是需要找到它的前一个节点；
     让第一个指针 rear 先走 n 步，然后让另一个指针 front 从头开始，
     两个指针再同时一步步往后移动；
     当 rear 走到链表末尾时，front 就恰好位于待删除节点的前一个节点；
     这样就能完成删除操作。
     需要注意边界情况，比如：
     如果删除的是第一个节点 => 可以借助 dummy head（虚拟头节点），当然不用 dummy 也能写。

     + 分析：
         + 时间复杂度：O(n)
         + 空间复杂度：O(1)
     + rank:
         + 时间效率：0 ms, 击败 100%
         + 空间效率：17.67 MB, 击败 19.18%
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
    def removeNthFromEnd(self, head: Optional[ListNode], n: int) -> Optional[ListNode]:
        dummy = ListNode(-1, head)
        cur = dummy
        p = None
        i = 0

        while cur.next is not None:
            i += 1
            if i <= n:
                cur = cur.next
                if i == n:
                    p = dummy
                continue
            p = p.next
            cur = cur.next
        
        tmp = p.next
        if tmp:
            p.next = tmp.next
        return dummy.next