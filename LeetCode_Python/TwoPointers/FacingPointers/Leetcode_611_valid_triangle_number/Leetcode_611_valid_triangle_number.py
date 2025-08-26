"""
@brief: Leetcode_611_有效三角形的个数
@link: https://leetcode.cn/problems/valid-triangle-number/description/
@author: liangj.zhang
@date: 26/8/2025

@Difficulty: Medium
@Label: Two Pointers(Facing)
@Retrospect(worthy 1 - 5): 3

@thoughts:
    + 思路 1：排序 + 枚举长边的相向双指针
        + 三角形的构成规则：任意两边之和大于第三边 a + b > c
            + 上面的形式是不是很眼熟：i + j > k（nums[i] + nums[j] == target）
                + 我们处理过 3sum ≈ target -> https://leetcode.cn/problems/3sum-closest/description/
                + 还处理不好两数的？
                + 只不过这里的 target 是我们自己的数据，那我们就倒着来，k 是大数，
                    + 循环内部是 i + j > target，两数大于 target
                + 印象中，三角形的规则还有一个规律：
                    + 较小的两边之和 > 第三边，一定能构成三角形；
                + 那么我们就可以开始了；
        + 分析：
            + 时间复杂度：排序 O(nlogn) + 相向双指针 O(n^2)
            + 空间复杂度：没有申请额外与数组长度相关的栈或堆空间 O(1)
        + rank:
            + 时间效率：403 ms, 击败 75.84%
            + 空间效率：17.54 MB, 击败 67.42%
"""

from typing import List


class Solution:
    def triangleNumber(self, nums: List[int]) -> int:

        nums.sort()
        cnt = 0
        size = len(nums)
        
        for k in range(size - 1, 1, -1):

            if (nums[k - 1] + nums[k - 2] < nums[k]): continue
            if nums[0] + nums[1] > nums[k]:
                cnt += (k - 1) * k * (k + 1) // 6
                return cnt

            i = 0
            j = k - 1
            while i < j:
                sum = nums[i] + nums[j]
                if sum > nums[k]:
                    cnt += j - i
                    j -= 1
                else: #sum <= nums[k]
                    i += 1
                
        return cnt
    
def main():
    nums = [2,2,3,4]
    print(Solution().triangleNumber(nums))

if __name__ == "__main__":
    main()
