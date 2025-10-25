"""
@brief: Leetcode_237_删除链表中的节点  
@link: https://leetcode.cn/problems/delete-node-in-a-linked-list/description/  
@author: liangj.zhang  
@date: 25/10/2025  

@Difficulty: Medium  

@Label: Delete Node  

@Retrospect(worthy 1 - 5): 2  

@thoughts:
 + 【思路 1】：复制下一个节点值，再删除下一个节点；  
     我应该最初看到这道题的时候，也没想出来；  
     >>> 难道真有不用知道上一个节点，就能删掉当前节点，并连接上链表？没有； <<<  
     脑筋急转弯的题，意识到上面一点就行了；  
     + 分析：  
         + 时间复杂度：O(1)  
         + 空间复杂度：O(1)  
     + rank:  
         + 时间效率：37 ms, 击败 94.99%  
         + 空间效率：17.75 MB, 击败 52.24%  
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
    def deleteNode(self, node):
        """
        :type node: ListNode
        :rtype: void Do not return anything, modify node in-place instead.
        """
        node.val = node.next.val
        node.next = node.next.next
        