"""
@brief: Leetcode_2397_被列覆盖的最多行数
@link: https://leetcode.cn/problems/maximum-rows-covered-by-columns/description/
@author: liangj.zhang
@date: 4/2/2026

@Difficulty: Medium

@Label: BackTracking(DFS) | Bitmap

@Retrospect(worthy 1 - 5): 4

@thoughts:
#  + 【思路 1】：BackTracking(DFS)
#      回溯相当于，遍历的方式不重复的挑出每种情况
#      当达到 numSelect 时，查看跟这一行的和是不是相同，相同则可以记上一行；
#      所有行被相比较之后，与最大值相比；
#      + 分析：
#          + 时间复杂度：遍历 matrix 得到每行的和：O(m*n)
#            + DFS: O(C(n, numSelect) * m * numSelect)
#          + 空间复杂度：O(m) 局部数组，dfs: O(numSelect)

 + 【思路 1】：Bitmap
     本来没有理解这种做法的，第二天就突然有所理解了；
     理解参考代码注释；
     + 分析：
         + 时间复杂度：O(m*n) + O(2^n), m->rowCnt, n->colCnt
         + 空间复杂度：O(m) 临时数组
"""


from typing import List


class Solution:
    def maximumRows(self, matrix: List[List[int]], numSelect: int) -> int:
        rowCnt = matrix.__len__()
        colCnt = matrix[0].__len__()
        matMask = [0] * rowCnt
        for i in range(rowCnt):
            for j in range(colCnt):
                matMask[i] |= matrix[i][j] << j

        maxCnt = -1
        for mask in range(1 << colCnt):
            if mask.bit_count() != numSelect: continue  # int.bit_count() -> python 3.8+
            cnt = 0
            for e in matMask:
                if e & mask == e:
                    cnt += 1
            if cnt > maxCnt: maxCnt = cnt

        return maxCnt