"""
@brief: Leetcode_74_搜索二维矩阵
@link: https://leetcode.cn/problems/search-a-2d-matrix/description/
@author: liangj.zhang
@date: 26/9/2025

@Difficulty: Medium

@Label: Binary Search, Exclusive Method

@Retrospect(worthy 1 - 5): 2

@thoughts:
    + 【思路 1】：二分查找
        - 这题本质上跟在一维数组中查找差不多；
        - 只需要把二维矩阵坐标映射到一维即可。

    + 分析：
        - 时间复杂度：O(log n)
        - 空间复杂度：O(1)

    + rank:
        - 时间效率：0 ms, 击败 100%
        - 空间效率：17.84 MB, 击败 83.68%
"""

from typing import List


class Solution:
    def searchMatrix(self, matrix: List[List[int]], target: int) -> bool:
        m, n = len(matrix), len(matrix[0])
        l, r = 0, m * n - 1
        while l <= r:
            mid = (l + r) // 2
            x = mid // n
            y = mid % n
            if matrix[x][y] < target:
                l = mid + 1
            else:
                r = mid - 1
        return True if l != m * n and matrix[l // n][l % n] == target else False