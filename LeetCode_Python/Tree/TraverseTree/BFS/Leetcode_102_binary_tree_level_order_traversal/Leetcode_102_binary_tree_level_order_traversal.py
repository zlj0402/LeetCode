"""
@brief: Leetcode_102_二叉树的层序遍历
@link: https://leetcode.cn/problems/binary-tree-level-order-traversal/description
@author: liangj.zhang
@date: 29/12/2025

@Difficulty: Medium

@Label: Binary Tree、BFS

@brief content: 一层一层的遍历二叉树

@thoughts:
 + 【思路 1】：用自己实现的队列，进行 BFS
     外层循环条件 => while (front < rear)
     内层循环条件 => while (front < last_rear) , 小于上一次的 rear
     + 使用了两个优化的小技巧
         + tmp 提前申请上一层节点数的 2 倍空间；
         + 转移 tmp 时使用 std::move 转移资源不复制；

     + 分析：
         + 时间复杂度：O(n)
         + 空间复杂度：O(n) -> 虽然我是固定大小，可以认为是 O(n) 的
     + rank:
         + 时间效率：0 ms, 击败 100%
         + 空间效率：17.94 MB, 击败 91.15%
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
    arr = [0] * MAXSIZE
    def levelOrder(self, root: Optional[TreeNode]) -> List[List[int]]:
        if not root: return []

        self.arr = Solution.arr
        front = rear = 0
        ret = []

        self.arr[rear] = root; rear += 1
        while front < rear:
            tmp = []
            last_rear = rear

            while front < last_rear:
                cur = self.arr[front]; front += 1
                tmp.append(cur.val)
                if cur.left: self.arr[rear] = cur.left; rear += 1
                if cur.right: self.arr[rear] = cur.right; rear += 1

            ret.append(tmp)
        return ret