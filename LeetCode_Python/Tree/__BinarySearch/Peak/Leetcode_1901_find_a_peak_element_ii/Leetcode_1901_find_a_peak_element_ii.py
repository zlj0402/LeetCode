"""
@brief: Leetcode_1901_寻找峰值_II
@link: https://leetcode.cn/problems/find-a-peak-element-ii/description/
@author: liangj.zhang
@date: 28/9/2025

@Difficulty: Medium

@Label: Binary Search

@Retrospect(worthy 1 - 5): 4

@thoughts:
    + 【思路 1】：二分查找
        - 我是看了题解，才勉强理解；
        - 要不是先做了 Leetcode_162，更难理解怎么在纵向上找到一个 peak。

        疑问：
        这题又有一个容易困惑的地方：  
        在二分之后，横向 mid 使我们更接近峰顶，得到一个新的行，  
        又去找到这一行的最大值。那之前走过的行中，与该列对应的值，会不会大于新找到的最大值？  

        答案是不会的，就像区间关系 a0 < a < b < b1 的过程一样。

    + 分析：
        - 时间复杂度：
            * 以行进行二分：O(log m) * n（我的写法）
            * 以列进行二分：O(log n) * m
        - 空间复杂度：O(1)

    + rank:
        - 时间效率：0 ms, 击败 100%
        - 空间效率：49.27 MB, 击败 93.03%
"""

from typing import List


class Solution:
    def findPeakGrid(self, mat: List[List[int]]) -> List[int]:
        m, n = len(mat), len(mat[0])
        l, r = 0, m - 2

        max_val = max_idx = -1
        def get_max(i: int):
            nonlocal max_val, max_idx
            max_val = max_idx = -1
            for j, val in enumerate(mat[i]):
                if mat[i][j] > max_val:
                    max_val = mat[i][j]
                    max_idx = j
        
        while l <= r:
            mid = (l + r) // 2
            get_max(mid)
            if max_val > mat[mid + 1][max_idx]:
                r = mid - 1
            else:
                l = mid + 1
        
        get_max(l)
        return [l, max_idx]
    

def main():
    mat = [[10,20,40,50,60,70],[1,4,2,3,500,80]]
    print(Solution().findPeakGrid(mat))


if __name__ == "__main__":
    main()