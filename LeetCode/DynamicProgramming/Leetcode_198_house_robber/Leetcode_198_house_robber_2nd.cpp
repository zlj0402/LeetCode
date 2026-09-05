/**
 * @brief: Leetcode_198_打家劫舍 the second
 * @link: https://leetcode.cn/problems/house-robber/description/?envType=study-plan-v2&envId=top-100-liked
 * @author: liangj.zhang
 * @date: 2026/09/05
 * 
 * @Difficulty: Medium
 * 
 * @Label: Dynamic Programming
 * 
 * @thoughts:   
 *  + 【思路 1】：动态规划，自顶向下
 *  + 【思路 2】：动态规划，自顶向上
 *      代码上没有什么变化，只有边界情况的改变；
 * 
 *      + rank:
 *          + 时间效率：0 ms，击败 100%
 *          + 空间效率：
 *              + 思路 1：10.44 MB, 击败 54.93%
 *              + 思路 2：10.51 MB, 击败 40.09%
 */

#include <vector>
using std::vector;

//【思路 1】：动态规划，自顶向下
class Solution {
public:
    int rob(vector<int>& nums) {
        auto n = nums.size();
        vector<int> rec(n, -1);

        auto dfs = [&] (this auto&& dfs, int idx) {
            if (idx < 0) return 0;

            if (rec[idx] < 0) {
                int ret = std::max(dfs(idx - 1), dfs(idx - 2) + nums[idx]);
                rec[idx] = ret;
            }

            return rec[idx];
        } (n - 1); // n >= 1

        return rec[n - 1];
    }
};

//【思路 2】：动态规划，自顶向上
class Solution {
public:
    int rob(vector<int>& nums) {
        auto n = nums.size();
        vector<int> rec(n, -1);

        auto dfs = [&] (this auto&& dfs, int idx) {
            if (idx >= n) return 0;

            if (rec[idx] == -1) {
                int ret = std::max(dfs(idx + 1), dfs(idx + 2) + nums[idx]);
                rec[idx] = ret;
            }

            return rec[idx];
        } (0);

        return rec[0];
    }
};