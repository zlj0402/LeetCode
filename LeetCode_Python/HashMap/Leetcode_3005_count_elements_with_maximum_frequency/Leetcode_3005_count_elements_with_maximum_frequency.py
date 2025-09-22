"""
@brief: Leetcode_3005_最大频率元素计数
@link: https://leetcode.cn/problems/count-elements-with-maximum-frequency/description/
@author: liangj.zhang
@date: 22/9/2025

@Difficulty: Easy (Score: 1217)

@Label: Array, HashMap

@Retrospect(worthy 1 - 5): 1

@thoughts:
    + 【思路 1】：哈希
        - 做这题，是因为它是今天的每日一题 ^^，赚币 ing，争取早日获得力扣电脑包；
        - 看到条件：
            1 <= nums.length <= 100
            1 <= nums[i] <= 100
          立马放弃了 STL 库；
          转用数组（且用 static），手动哈希；
        - 同频率，用个计数；
          出现新的大频率，计数重置为 1。

        - 分析：
            时间复杂度：O(n)
            空间复杂度：O(n)

        - rank:
            - 写法1：
                - 时间效率：0 ms, 击败 100%
                - 空间效率：22.20 MB, 击败 100%
            - 写法2：
                - 时间效率：0 ms, 击败 100%
                - 空间效率：17.46 MB, 击败 65.38%
"""

from collections import defaultdict
from typing import List

# 【思路 1】：写法1：哈希 & List
"""
class Solution:
    MAXLEN = 101
    def maxFrequencyElements(self, nums: List[int]) -> int:
        arr = [0] * self.MAXLEN
        max_fre = -1
        max_fre_cnt = 0

        for e in nums:
            arr[e] += 1
            if arr[e] > max_fre:
                max_fre = arr[e]
                max_fre_cnt = 1
            elif arr[e] == max_fre:
                max_fre_cnt += 1
        return max_fre * max_fre_cnt
"""

# 【思路 1】：写法2：哈希 & defaultdict
class Solution:
    def maxFrequencyElements(self, nums: List[int]) -> int:
        cnt = defaultdict(int)
        max_fre = -1
        max_fre_cnt = 0
        for e in nums:
            cnt[e] += 1
            c = cnt[e]
            if cnt[e] > max_fre:
                max_fre = c
                max_fre_cnt = 1
            elif cnt[e] == max_fre:
                max_fre_cnt += 1
        return max_fre * max_fre_cnt