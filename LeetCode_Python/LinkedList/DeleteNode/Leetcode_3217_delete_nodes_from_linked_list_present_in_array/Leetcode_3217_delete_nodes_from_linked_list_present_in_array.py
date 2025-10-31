"""
@brief: Leetcode_3217_从链表中移除在数组中存在的节点
@link: https://leetcode.cn/problems/delete-nodes-from-linked-list-present-in-array/description/
@author: liangj.zhang
@date: 31/10/2025

@Difficulty: Medium

@Label: HashMap & DeleteNode

@Retrospect(worthy 1 - 5): 3

@thoughts:
    + 【思路 1】：HashMap & DeleteNode
        应该很自然地能想到，用 set 这种结构来存储一遍需要删除的数组中的值；
        + 如果值的范围很小，优先使用固定的数组；
        + 如果值的范围很大，优先使用 STL 库的 set（set/unordered_set）；
        解题还有个优先处理的方式：静态的 set 集合，clear() 之后会保留空位数，
        下次重新放入值，不会重新申请空间。

        存入哈希之后，就变成单纯的删除元素问题，回归《Leetcode_203》。

        ps: 对于 C++ 的写法，最坑的是不需要自己手动回收（也没提示）；
            如果自己手动回收，Leetcode 后台会再回收一次，所以会报错；
            在周赛的时候，看不懂报错，那就凉凉，耽误时间。

    + 分析：
        + 时间复杂度：O(m + n) -> m 为数组长度，n 为链表长度；
        + 空间复杂度：O(m)；
    + rank：
        + 时间效率：62ms, 击败 84.75%
        + 空间效率：57.25 MB, 击败 52.66%
"""

import os
import sys

print(os.path.join(os.path.dirname(__file__)))
print(os.path.abspath(os.path.join(os.path.dirname(__file__), "../../../.."))) #f:\Code\zljgit\LeetCode
sys.path.append(os.path.abspath(os.path.join(os.path.dirname(__file__), "../../../..")))

from typing import List, Optional

from Include.PyLeetcode.LinkedList.LinkedList import ListNode

# Definition for singly-linked list.
# class ListNode:
#     def __init__(self, val=0, next=None):
#         self.val = val
#         self.next = next
class Solution:
    def modifiedList(self, nums: List[int], head: Optional[ListNode]) -> Optional[ListNode]:
        s = set(nums)

        dummy = ListNode(-1, head)
        cur = dummy
        while cur.next:
            if cur.next.val in s:
                cur.next = cur.next.next
            else:
                cur = cur.next
            
        return dummy.next
        