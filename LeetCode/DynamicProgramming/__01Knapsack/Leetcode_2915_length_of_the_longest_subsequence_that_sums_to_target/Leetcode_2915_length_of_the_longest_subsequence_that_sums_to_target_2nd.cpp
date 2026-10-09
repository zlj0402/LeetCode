/**
 * @breif: Leetcode_2915_和为目标值的最长子序列的长度_2nd
 * @link: https://leetcode.cn/problems/length-of-the-longest-subsequence-that-sums-to-target/description/
 * @author: liangj.zhang
 * @date: 2026/10/09
 * 
 * @Difficulty: Medium
 * 
 * @Label: 01Knapsack
 * 
 * @Retrospect(worthy 1 - 5): 5 -- 难考虑周全
 * 
 * @thoughts:
 *  + 【思路 1】：回溯 -- 超时，超时不是关键
 *      + 注释中，原来错误的写法：
 *          写得时候，没有考虑到，在选与不选，两者当中，如果都没有构成 dfs 路径和是 target，那么
 *              就不应该，在选择的时候，每次都默认给选择的情况 + 1;
 *              虽然可能因为 MIN 取得够小，只要有一个可能构成 target 的路径，就会将默认 + 1 的错误情况取消掉，
 *              但是如果没有一个 dfs 路径和构成 target，那么得到的结果 res 就是 MIN + 递归深度的结果（也不是准确的递归深度，因为在 left < num[idx] 时，不会走选择的路径，就不会默认 +1）；
 *              res == INIMIN ? -1 : res; ==> 既不是 -1，也不是正数；
 *      + 分析：
 *          + 时间复杂度：O(2^n)
 *          + 空间复杂度：O(n)
 */

#include <vector>
using std::vector;

//【思路 1】：回溯 -- 超时，超时不是关键
class Solution {
public:
    int lengthOfLongestSubsequence(vector<int>& nums, int target) {
        int INTMIN = -100000;
        auto dfs = [&](this auto&& dfs, int idx, int left) -> int {
            if (idx < 0) return left == 0 ? 0 : INTMIN; // 原来错误的写法：if (idx < 0) return left == 0 ? 1 : INTMIN;
            
            if (left < nums[idx]) return dfs(idx - 1, left);

            // 原来错误的写法：
            // return std::max(dfs(idx - 1, left), dfs(idx - 1, left - nums[idx]) + 1); // 有可能选与不选，两种路径都不能构成路径和是 target

            int skip = dfs(idx - 1, left);
            int take = dfs(idx - 1, left - nums[idx]);

            if (take != INTMIN) { // dfs 路径的组合结果是否构成 target
                return std::max(skip, take + 1);
            }

            return skip;
        };

        int res = dfs(nums.size() - 1, target);
        return res == INTMIN ? -1 : res;
    }
};
