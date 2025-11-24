"""
@brief: Leetcode_508_出现次数最多的子树元素和
@link: https://leetcode.cn/problems/most-frequent-subtree-sum/description/
@author: liangj.zhang
@date: 24/11/2025

@Difficulty: Medium

@Label: Tree & HashMap

@Retrospect(worthy 1 - 5): 3

@thoughts:
  值得学习使用 max() / sorted() 的自定义比较器，以及对应的两种写法；
    ps: python 写法值的回顾的地方：获得 dict 的 values()，然后得到最大值；列表推导式

  + 分析：
      + 时间复杂度：遍历树 O(n) + 查找最大频次 O(n) + 再遍历找 key O(n)
      + 空间复杂度：O(h) + O(n) => O(n)

  + 写法 1
      + rank:
          + 时间效率：8 ms, 击败 47.68%
          + 空间效率：24.27 MB, 击败 95.94%

  + 写法 2
      + rank:
          + 时间效率：3 ms, 击败 99.03%
          + 空间效率：24.32 MB, 击败 94.79%
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
    def __init__(self) -> None:
        self.rec = {}

    def __findFrequentTreeSum(self, root: Optional[TreeNode]) -> int:
        if not root: return 0
        left = self.__findFrequentTreeSum(root.left)
        right = self.__findFrequentTreeSum(root.right)
        _sum = left + right + root.val
        if self.rec.get(_sum) is not None:
            self.rec[_sum] += 1
        else:
            self.rec[_sum] = 1
        return _sum

    def findFrequentTreeSum(self, root: Optional[TreeNode]) -> List[int]:
        self.__findFrequentTreeSum(root)
        _max = max(self.rec.values())
        # ret = []
        # for k, v in self.rec.items():
        #     if v == _max:
        #         ret.append(k)
        return [k for k, v in self.rec.items() if v == _max]
    