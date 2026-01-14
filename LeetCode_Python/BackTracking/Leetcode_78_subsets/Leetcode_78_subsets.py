"""
/**
 * @brief: Leetcode_78_子集
 * @link: https://leetcode.cn/problems/subsets/submissions/691382290/
 * @author: liangj.zhang
 * @date: 14/1/2026
 * 
 * @Difficulty: Medium
 * 
 * @Label: BackTracking
 * 
 * @Retrospect(worthy 1 - 5): 5 【枚举选与不选的思想很优雅】
 * 
 * @thoughts:
 *  + 【思路 1】：回溯 -- 子集型问题
 *      子集型问题，就是解决完当前问题，子问题是同样的做法；（也即递归性）
 * 
 *      + 分析：
 *          + 时间复杂度：O(2^n * n), *n -> 拷贝每一个结果；
 *          + 空间复杂度：O(2^n * n)
 *      + rank:
 *          + 时间效率：0 ms, 击败 100%
 *          + 空间效率：19.26 MB, 击败 5.08%  
 */
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