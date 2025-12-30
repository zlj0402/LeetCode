
"""
@brief: Leetcode_103_二叉树的锯齿形层序遍历
@link: https://leetcode.cn/problems/binary-tree-zigzag-level-order-traversal/description/
@author: liangj.zhang
@date: 30/12/2025

@Difficulty: Medium

@Label: BFS

@Retrospect(worthy 1 - 5): 5

@thoughts:
 + 【思路 1】：BFS, 理清过程；
     还是不要按着题目的要求的顺序，给节点赋值，来举例子，给我弄晕了；
     例子：
                 3
                / \
               9   20
              / \  / \
             1  2 15  7
            /\ /\  /\  /\
          13 9 5 1 7 2 4 8

     3
     |   // 顺存
     9, 20                       // 先 20，后 9
     |   // 倒存
     7, 15, 2, 1                 // 先 1，后 7
     |   // 顺存
     13, 9, 5, 1, 7, 2, 4, 8     // 先 13，后 8
     
     这种方式：每次倒着遍历，顺着存；（那应该有完全对立的另一种解题方式）
     ，还有只改变节点在 arr[] 中位置的方式；就是比较绕；

     + 分析：
         + 时间复杂度：O(n)
         + 空间负载的：虽是固定大小，其实也是 O(n)
     + rank:
         + 时间效率：0 ms, 击败 100%
         + 空间效率：17.17 MB, 击败 98.08%
"""

import os
import sys

print(os.path.join(os.path.dirname(__file__)))
print(os.path.abspath(os.path.join(os.path.dirname(__file__), "../../../../.."))) #f:\Code\zljgit\LeetCode
sys.path.append(os.path.abspath(os.path.join(os.path.dirname(__file__), "../../../../..")))

from typing import Optional, List

from Include.PyLeetcode.Tree.Tree import TreeNode

# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:
    MAXSIZE = 2001
    arr = [None] * 2001
    
    def __init__(self) -> None:
        self.front = self.rear = 0
        self.reverse = False
        self.arr = Solution.arr

    def reverse_trav_xxx_save(self, tmp: List, sequence_save: bool) -> None:
        last_rear, last_front = self.rear, self.front
        self.front = self.rear

        while True:
            last_rear -= 1
            if last_rear < last_front: break

            cur = self.arr[last_rear]
            tmp.append(cur.val)

            if sequence_save:
                if cur.left: self.arr[self.rear] = cur.left; self.rear += 1
                if cur.right: self.arr[self.rear] = cur.right; self.rear += 1
            else:
                if cur.right: self.arr[self.rear] = cur.right; self.rear += 1
                if cur.left: self.arr[self.rear] = cur.left; self.rear += 1



    def zigzagLevelOrder(self, root: Optional[TreeNode]) -> List[List[int]]:
        if root is None: return []

        ret = []
        self.arr[self.rear] = root; self.rear += 1
        while self.front < self.rear:
            tmp = []
            self.reverse = not self.reverse
            self.reverse_trav_xxx_save(tmp, self.reverse)
            ret.append(tmp)

        return ret