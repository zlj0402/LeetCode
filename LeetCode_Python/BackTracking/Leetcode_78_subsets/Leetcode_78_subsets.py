"""
@brief: Leetcode_78_子集
@link: https://leetcode.cn/problems/subsets/submissions/691382290/
@author: liangj.zhang
@date: 14/1/2026

@updated:
 + 16/1/2026: add 【思路 1 -- 写法 2】：回溯 -- 子集型问题 -- 每次必须枚举一个数，但集合不能重复，按顺序进行

@Difficulty: Medium

@Label: BackTracking

@Retrospect(worthy 1 - 5): 5 【枚举选与不选的思想很优雅】

@thoughts:
 + 【思路 1 -- 写法 1】：回溯 -- 子集型问题 -- 当前位置数字，选与不选的抉择
     子集型问题，就是解决完当前问题，子问题是同样的做法；（也即递归性）

     + 分析：
         + 时间复杂度：O(2^n * n), *n -> 拷贝每一个结果；
         + 空间复杂度：O(2^n * n) -> 算上结果空间
     + rank:
         + 时间效率：0 ms, 击败 100%
         + 空间效率：19.26 MB, 击败 5.08%

 + 【思路 1 -- 写法 2】：回溯 -- 子集型问题 -- 每次必须枚举一个数，但集合不能重复，按顺序进行
     + 分析：同 写法 1
     + rank:
         + 时间效率：0 ms, 击败 100%
         + 空间效率：19.27 MB, 击败 5.08%
     + ps:
         Q1: 想一想两种写法在空间上的效率为什么不一样？
"""

# 【思路 1 -- 写法 1】：回溯 -- 子集型问题 -- 当前位置数字，选与不选的抉择
"""
class Solution:
    def subsets(self, nums: List[int]) -> List[List[int]]:
        path = []
        ret = []
        n = nums.__len__()
        def dfs(i: int) -> None:
            if i == n:
                ret.append(path.copy())
                return

            dfs(i + 1)

            path.append(nums[i])
            dfs(i + 1)
            path.pop()
        dfs(0)
        return ret
"""

from typing import List

# 【思路 1 -- 写法 2】：回溯 -- 子集型问题 -- 每次必须枚举一个数，但集合不能重复，按顺序进行

class Solution:
    def subsets(self, nums: List[int]) -> List[List[int]]:
        path = []
        res = []
        n = nums.__len__()

        def dfs(i: int) -> None:
            res.append(path.copy())

            for j in range(i, n):
                path.append(nums[j])
                dfs(j + 1)  
                path.pop()

        dfs(0)
        return res
    

def main():
    nums = [1, 2, 3]
    print(Solution().subsets(nums))

if __name__ == "__main__":
    main()