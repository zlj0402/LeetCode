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
 *  + 【思路 1】：递归搜索 + 保存计算结果 == 记忆化搜索，自顶向下
 *  + 【思路 2】：递归搜索 + 保存计算结果 == 记忆化搜索，自顶向上
 *      dfs(i) = max(dfs(i - 1), dfs(i - 2) + nums[i])
 *      代码上没有什么变化，只有边界情况的改变；
 * 
 *      + rank:
 *          + 时间效率：0 ms，击败 100%
 *          + 空间效率：
 *              + 思路 1：10.44 MB, 击败 54.93%
 *              + 思路 2：10.51 MB, 击败 40.09%
 * 
 *  + 【思路 3】：递推
 *      f(i) = max(f(i - 1), f(i - 2) + nums[i])
 */

#include <vector>
using std::vector;

class Solution {
public:
    int rob(vector<int>& nums) {
        int pre2 = 0, pre1 = 0;
        int n = nums.size();
        for (int i = 0; i < n; ++i) {
            int tmp = std::max(pre2 + nums[i], pre1);
            pre2 = pre1;
            pre1 = tmp;
        }
        return pre1;
    }
};

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