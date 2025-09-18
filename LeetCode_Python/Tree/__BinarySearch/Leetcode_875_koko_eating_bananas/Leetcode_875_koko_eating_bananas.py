"""
@brief: Leetcode_875_爱吃香蕉的珂珂
@link: https://leetcode.cn/problems/koko-eating-bananas/description/
@autor: liangj.zhang
@date: 18/9/2025

@Difficulty: Medium

@Label: Binary Search

@Retrospect(worthy 1 - 5): 4

@thoughts:
    + 【思路 1】：二分查找
        第一次没想出来，看了灵神的题解...
        + 昨天做的是 Leetcode_275_h_index_ii，二分循环体里的判定条件，单调变换的是不等式的右边；
        + 今天做的是单调变换的是不等式的左边；

        + 引用灵神的部分题解逻辑：
            + 如果珂珂能用 k=4 的速度吃掉所有香蕉，那么也能用更快的速度 k=5,6,⋯ 吃掉所有香蕉。
            + 如果珂珂不能用 k=3 的速度吃掉所有香蕉，那么也不能用更慢的速度 k=2,1,⋯ 吃掉所有香蕉。
            + 这种单调性意味着我们像二分查找那样，把答案 k 猜出来。

        + 我们就是取到一个速度，进行一次 ceil & sum 的求和；
        + 速度慢了，就取后半段中点的速度；
        + 速度快了，就取前半段中点的速度；
        + 然后就是确定速度的范围，我喜欢闭区间进行：
            + k = 1，是最低速度；题目保证 n ≤ h ==> 1 <= h/n
            + k = max(piles)，是最快的速度；再快，必定不能满足慢慢吃的条件了；

        + 还要明白一点，正整数运算理论：⌈k / p⌉ = ⌊(k - 1) / p⌋ + 1
        + 计算机中，除法 / 相当于 ⌊ ⌋，所以：⌈k / p⌉ = (k - 1) // p + 1

        + 分析：
            + 时间复杂度：找到最大值 O(log n); 速度 U，每次求 ceil & sum => O(log U) * n
            + 空间复杂度：O(1)

        + rank:
            + 时间效率：119 ms, 击败 97.52%
            + 空间效率：18.58 MB, 击败 64.97%
"""

from typing import List


class Solution:
    def minEatingSpeed(self, piles: List[int], h: int) -> int:
        size = piles.__len__()
        l, r = 1, max(piles)
        while l <= r:
            mid = (l + r) // 2
            if sum([(pile - 1) // mid for pile in piles]) <= h - size:
                r = mid - 1
            else:
                l = mid + 1
        return l
    
def main():
    piles = [30,11,23,4,20]
    h = 5
    print(Solution().minEatingSpeed(piles, h))

if __name__ == "__main__":
    main()