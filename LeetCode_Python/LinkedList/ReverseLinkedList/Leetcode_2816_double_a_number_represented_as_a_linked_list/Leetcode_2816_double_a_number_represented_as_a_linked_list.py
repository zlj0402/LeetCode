"""
@brief: Leetcode_2816_翻倍以链表形式表示的数字
@link: https://leetcode.cn/problems/double-a-number-represented-as-a-linked-list/description/
@author: liangj.zhang
@date: 16/10/2025

@Difficulty: Medium

@Label: Reverse LinkedList

@Retrospect(worthy 1 - 5): 3

@thoughts:
 + 【思路 1】：反转链表
     就像 《Leetcode_445_两数相加_II》一样，先反转，按正常顺序加，考虑进位，最后再反转一次；

 + 【思路 2】：一遍顺序遍历链表
     数翻倍，就像同样的链表加自己，头结点 > 4 的时候，才会产生一个新的节点；
     >>> 后续节点也是 > 4 的时候，才会向前面进 1；不然，不会进位；<<<

     + 分析：
         + 时间复杂度：遍历一次：O(n)
         + 空间复杂度：O(1)

     + rank:
         + 时间效率：30 ms, 击败 99.06%
         + 空间效率：20.03 MB, 击败 47.17%
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

#【思路 2】：一遍顺序遍历链表
class Solution:
    def doubleIt(self, head: Optional[ListNode]) -> Optional[ListNode]:
        ret = head
        if head and head.val > 4:
            ret = ListNode(1, head)

        cur = head
        while cur:
            cur.val = (cur.val << 1) % 10
            if cur.next and cur.next.val > 4:
                cur.val += 1
            cur = cur.next

        return ret
    

def main():
    # lst = [9, 9, 9]
    lst = [1, 8, 9]
    head = ListNode.build_list(lst)
    ListNode.print_list(head)
    res = Solution().doubleIt(head)
    ListNode.print_list(res)

if __name__ == "__main__":
    main()
        