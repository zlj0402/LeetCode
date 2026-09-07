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
 *      + 分析：
 *          + 时间复杂度：O(n)，已经走过的节点会直接返回，虽然没有进去，但也会遍历；
 *          + 空间复杂度：O(1)
 *      + rank:
 *          + 时间效率：0 ms，击败 100%
 *          + 空间效率：
 *              + 思路 1：10.44 MB, 击败 54.93%
 *              + 思路 2：10.51 MB, 击败 40.09%
 * 
 *  + 【思路 3】：递推
 *      f(i) = max(f(i - 1), f(i - 2) + nums[i])
 *      dfs -> f 数组；递归 -> 循环；递归边界 -> 数组初始值；
 *      
 *      这里没写：见第一次刷的 【思路 4】
 * 
 *  + 【思路 4】：动态规划 -- 自顶向下
 *      f(i) = max(f(i + 1), f(i + 2) + nums[i])
 *  + 【思路 5】：动态规划 -- 自底向上
 *      f(i) = max(f(i - 1), f(i - 2) + nums[i])
 * 
 *      + 分析：
 *          + 时间复杂度：O(n)
 *          + 空间复杂度：O(1)
 *      + rank：
 *          + 思路 1：
 *              + 时间效率：0 ms, 击败 100%
 *              + 空间效率：9.92 MB, 击败 88.04%
 *          + 思路 2：
 *              + 时间效率：0 ms, 击败 100%
 *              + 空间效率：9.86 MB, 击败 94.07%    
 */

#include <vector>
using std::vector;

//【思路 5】：动态规划 -- 自底向上
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

// 【思路 4】：动态规划 -- 自顶向下
class Solution {
public:
    int rob(vector<int>& nums) {
        int prev2 = 0, prev1 = 0;
        int n = nums.size();
        for (int i = n - 1; i >= 0; --i) {
            int tmp = prev1;
            prev1 = std::max(prev1, prev2 + nums[i]);
            prev2 = tmp;
        }
        return prev1;
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