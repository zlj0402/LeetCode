"""
@brief: Leetcode_2105_给植物浇水_II
@link: https://leetcode.cn/problems/watering-plants-ii/description/
@author: liangj.zhang
@date: 2/9/2025

@Difficulty: Medium

@Label: Two Pointers(Facing)

@Retrospect(worthy 1 - 5): 2

@thoughts:
    就是简单的双指针，从两端遍历；
    水不够，就先填满，再扣除；记录下重新填满的次数就可以了；

    + 【思路 1】：相向双指针
        + 分析：
            + 时间复杂度：O(N)
            + 空间复杂度：O(1)

        + rank:
            + 时间效率：31 ms, 击败 92.04%
            + 空间效率：32.49 MB, 击败 19.57%
"""


from typing import List

class Solution:

    def minimumRefill(self, plants: List[int], capacityA: int, capacityB: int) -> int:

        refill_cnt = 0

        cl = capacityA
        cr = capacityB
        l = 0
        r = len(plants) - 1

        while l <= r:
            if l == r:
                if cl >= cr:
                    if cl < plants[l]:
                        refill_cnt += 1
                        cl = capacityA
                    cl -= plants[l]
                else:
                    if cr < plants[r]:
                        refill_cnt += 1
                        cr = capacityB
                    cr -= plants[r]
            else:
                if cl < plants[l]:
                    refill_cnt += 1
                    cl = capacityA
                cl -= plants[l]
                if cr < plants[r]:
                    refill_cnt += 1
                    cr = capacityB  
                cr -= plants[r]
            l += 1
            r -= 1
        return refill_cnt

"""
class Solution:
    def __init__(self):
        self.refill_cnt = 0

    # python 当中没有 pass by reference 的概念
    # 只能通过 return 来更新 water_left 的值
    def watering(self, water_left, cost, capacity):
        if water_left < cost:
            water_left = capacity
            self.refill_cnt += 1
        water_left -= cost
        return water_left

    def minimumRefill(self, plants: List[int], capacityA: int, capacityB: int) -> int:

        self.refill_cnt = 0
        cl = capacityA
        cr = capacityB
        l = 0
        r = len(plants) - 1

        while l <= r:
            if l == r:
                if cl >= cr:
                    cl = self.watering(cl, plants[l], capacityA)
                else:
                    cr = self.watering(cr, plants[r], capacityB)
            else:
                cl = self.watering(cl, plants[l], capacityA)
                cr = self.watering(cr, plants[r], capacityB)
            l += 1
            r -= 1
        return self.refill_cnt
"""