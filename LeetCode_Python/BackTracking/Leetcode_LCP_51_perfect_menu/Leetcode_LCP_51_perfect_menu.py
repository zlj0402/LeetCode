"""
@brief: Leetcode_LCP_51_烹饪料理
@link: https://leetcode.cn/problems/UEcfPD/description/
@author: liangj.zhang
@date: 18/2/2026

@Difficulty: Easy

@Label: DFS & BackTracking

@Retrospect(worthy 1 - 5): 4

@thoughts:
 + 【思路 1】：回溯，选与不选 DFS
     理解起来比枚举的要好理解一点
     + 分析：
         + 时间复杂度：O(5 * 2^n)，同上面是一样的；
         + 空间复杂度：O(n) -> 临时空间
     + rank:
         + 时间效率：50 ms, 击败 58.03%
         + 空间效率：19.70 MB, 击败 5.07%
"""

from typing import List


class Solution:

    def __possible(self, mat: List, cookbook: List) -> bool:
        for i in range(mat.__len__()):
            if mat[i] - cookbook[i] < 0:
                return False
        return True
        
    def perfectMenu(self, materials: List[int], cookbooks: List[List[int]], attribute: List[List[int]], limit: int) -> int:
        n = cookbooks.__len__()
        maxDelicious = -1

        def dfs(i: int, delicious: int, full: int) -> None:
            nonlocal maxDelicious
            if i == n:
                if full >= limit and delicious > maxDelicious:
                    maxDelicious = delicious
                return
            
            dfs(i + 1, delicious, full)

            if self.__possible(materials, cookbooks[i]):
                for k in range(materials.__len__()):
                    materials[k] -= cookbooks[i][k]
                dfs(i + 1, delicious + attribute[i][0], full + attribute[i][1])
                for k in range(materials.__len__()):
                    materials[k] += cookbooks[i][k]

        dfs(0, 0, 0)

        return maxDelicious