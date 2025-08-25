"""
@brief: Leetcode_15_3sum
@link: https://leetcode.cn/problems/3sum/description/
@author: liangj.zhang
@date: 25/8/2025

@Difficulty: Medium
@Label: Two Pointers(Facing)
@Retrospect(Worthy 0 - 5): 2

@thoughts:
    1. 排个序
    2. 选定一个 值
    3. 剩余范围内，最左最右两个指针；
    4. 三数和 > 0, 右指针向左移；
    5. 三数和 < 0, 左指针向右移；
    6. 三数和 == 0, 记录；可以继续左移右移，以免有相同的数值；

    时间复杂度分析：O(nlogn)（排序） + O(n^2)（内外层遍历） == O(n^2)

    rank: 
        时间效率：443 ms, 击败 85.71%
        空间效率：20.21 MB, 击败 92.22%
"""
from typing import List

class Solution:
    def threeSum(self, nums: List[int]) -> List[List[int]]:

        res = []
        nums.sort()
        for i in range(len(nums) - 2):
            
            if i != 0 and nums[i] == nums[i - 1]:
                continue

            if nums[i] + nums[i + 1] + nums[i + 2] > 0 or \
                nums[i] + nums[-1] + nums[-2] < 0:
                continue

            j = i + 1
            k = len(nums) - 1
        
            while j < k:
                sum = nums[i] + nums[j] + nums[k]
                if sum < 0:
                    j = j + 1
                elif sum > 0:
                    k = k - 1
                else:
                    res.append([nums[i], nums[j], nums[k]])
                    while j < k and nums[j + 1] == nums[j]: j = j + 1
                    while j < k and nums[k - 1] == nums[k]: k = k - 1
                    j = j + 1
                    k = k - 1
        return res

def main():
    
    nums = [-1,0,1,2,-1,-4]
    res = Solution().threeSum(nums)

    for v in res:
        for e in v:
            print(e, end=" ")
        print()

if __name__ == "__main__":
    main()
