"""
@brief: Leetcode_987_二叉树的垂序遍历  
@link: https://leetcode.cn/problems/vertical-order-traversal-of-a-binary-tree/description/  
@author: liangj.zhang  
@date: 9/11/2025  

@Difficulty: Hard（实话说是，Hard 里简单的）  

@Label: Tree(Traverse) + HashMap/Set  

@Retrospect(worthy 1 - 5): 5  

@thoughts:
 + 【思路 1】：dfs + hashmap/multiset  
     我的第一想法就是这个，先 dfs 遍历一遍，加上行列的记录；  
     将一个值的信息封装成 col, row, val => E(x, y, z)，并在类中定义排序规则（如通过 `__lt__`）；  
     放入一个总的 multiset（Python 可用 `sorted()` 或 `heapq` 模拟），  
     或者使用字典，列作为 key，列表（包含 (row, val)）作为 value；  
     实际上这两种方式效果类似，我用的是一个总的 multiset 思路。  

     + 值得回顾的点是：比较方式的几种写法（Python 对应排序 key）：
         1. 自定义类的 `__lt__` 方法  
         2. `sorted(..., key=lambda e: (e.x, e.y, e.z))`  

     + 分析：  
         + 时间复杂度：O(n)，dfs 一遍 + 排序 O(nlogn) => O(nlogn)  
         + 空间复杂度：O(n)  
     + rank:  
         + 时间效率：0 ms, 击败 100%  
         + 空间效率：17.93 MB, 击败 34.66%  
"""

import os
import sys

print(os.path.join(os.path.dirname(__file__)))
print(os.path.abspath(os.path.join(os.path.dirname(__file__), "../../.."))) #f:\Code\zljgit\LeetCode
sys.path.append(os.path.abspath(os.path.join(os.path.dirname(__file__), "../../..")))

from typing import List, Optional

from Include.PyLeetcode.Tree.Tree import TreeNode

# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:
    def __init__(self):
        self.rec = []

    def __verticalTraversal(self, root: Optional[TreeNode], y: int, x: int) -> None:
        if not root: return
        self.rec.append({'x': x, 'y': y, 'z': root.val})
        self.__verticalTraversal(root.left, y + 1, x - 1)
        self.__verticalTraversal(root.right, y + 1, x + 1)

    def verticalTraversal(self, root: Optional[TreeNode]) -> List[List[int]]:
        self.rec.clear()
        self.__verticalTraversal(root, 0, 0)
        self.rec.sort(key = lambda coor: (coor['x'], coor['y'], coor['z']))
        
        print(self.rec)
        tmp = []
        ans = []
        last_x = self.rec[0]['x']
        for e in self.rec:
            if last_x != e['x']:
                ans.append(tmp)
                tmp = []    # 原来写的经典，错误: tmp.clear()，传进去的一直是 tmp 的引用，ans里面的几个值，都是同一个 tmp 的引用，tmp 只保留最后一次的值；ans 里面应该保留一份当次 tmp 的拷贝；
                last_x = e['x']
            tmp.append(e['z'])
        ans.append(tmp)

        return ans