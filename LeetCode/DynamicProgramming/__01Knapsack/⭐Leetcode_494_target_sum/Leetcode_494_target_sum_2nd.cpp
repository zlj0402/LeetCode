/**
 * @brief: Leetcode_494_目标和_2nd
 * @link: https://leetcode.cn/problems/target-sum/description/
 * @author: liangj.zhang
 * @date: 2026/09/03
 * 
 * @updated:
 *      + 2026/09/23: add【思路 2】：记忆化搜索
 * 
 * @Difficulty: Medium
 * 
 * @Label: 01Knapsack
 * 
 * @Retrospect(worthy 1 - 5): 5 -- classic
 * 
 * @thoughts:
 *  + 【思路 1】：纯 dfs
 *      + 分析：
 *          + 时间复杂度：O(2^n)
 *          + 空间复杂度：O(n)
 *      + rank:
 *          + 时间效率：339 ms, 击败 21.09%
 *          + 空间效率：11.58 MB, 击败 85.24%
 *  + 【思路 2】：记忆化搜索
 *      + 分析：
 *          + 时间复杂度：O(n * t)
 *              + n = nums.size()
 *              + t = (sum - |target|) / 2，最坏 sum
 *              - 状态总数：idx 有 n 个取值（0 到 n-1），left 有 t+1 个取值（0 到 t）
 *              - 每个状态 (idx, left) 最多计算一次（记忆化剪枝）
 *              - 每次状态转移是 O(1)（最多分支两种情况）
 *              - 总时间 = O(n × t)
 *              => 最坏情况下 t ≈ sum/2，所以也可以表示为 O(n × sum)。
 *          + 空间复杂度：O(n * t)
 *              + 记忆化数组 rec：大小 n × (t+1)，占主导
 *              + 递归调用栈：最深 n 层，O(n)
 *      + rank:
 *          + 时间效率：3 ms, 击败 70.68%
 *          + 空间效率：14.98 MB, 击败 34.17%
 *      + 补充说明:
 *          + 这是一个典型的 0-1 背包计数问题：
 *              + 通过数学转换，将 "正负号分配" 转化为 "选若干数和为 t"
 *              + t 取 (sum - |target|) / 2 而非 (sum + target) / 2 是为了让背包容量更小，优化常数
 *          当 sum 较大但 n 较小时，这个 DP 可能不如直接 DFS（指数级但实际剪枝多）；
 *          当 sum 适中时，这个 DP 是伪多项式时间的高效解法。
 */ 
#include <vector>
#include <numeric>
#include <cmath>
using std::vector;

class Solution {
public:
    int findTargetSumWays(vector<int>& nums, int target) {
        // 负数绝对值和为 p
        // 那么正数之和为 sum - p
        // (sum - p) - p = target => 2p = sum - target;

        // p = (sum - target) / 2; 正数之和 q = sum - p = (sum + target) / 2
        // target > 0 时，q > p
        // target < 0 时，p > q
        // (sum - std::abs(target)) / 2 => 就是最小的一方，无论 target 是正是负
        int sum = std::accumulate(nums.begin(), nums.end(), 0);
        int t = (sum - abs(target)) / 2;
        if (t < 0 || (sum - abs(target)) % 2) return 0;

        int n = nums.size();
        vector<vector<int>> rec (n, vector<int>(t + 1, -1)); // t -> 目标和，可能为 0，所以加 1

        // return 的是该 idx 处 left 的可能
        // 由 idx-1 的 left 和 left - nums[idx] 处决定
        auto dfs = [&](this auto&& dfs, int idx, int left) {
            if (idx < 0) return left == 0 ? 1 : 0;
            auto& r = rec[idx][left];
            if (r != -1) return r;

            if (left < nums[idx]) return r = dfs(idx - 1, left);

            return r = dfs(idx - 1, left - nums[idx]) + dfs(idx - 1, left);
        } (n - 1, t);

        return rec[n - 1][t];
    }
};

class Solution {
public:
    int findTargetSumWays(vector<int>& nums, int target) {
        int sum = accumulate(nums.begin(), nums.end(), 0);

        // 负数和 p
        // 则正数和为 sum - p
        // (sum - p) - p = target
        // sum - target = 2p

        int p = sum - target;

        if (p < 0 || p % 2)
            return 0;

        auto dfs = [&] (this auto&& dfs, int idx, int left) {

            if (idx < 0) return left == 0 ? 1 : 0;

            if (left < nums[idx]) return dfs(idx - 1, left);

            return dfs(idx - 1, left) + dfs(idx - 1, left - nums[idx]);
        };

        return dfs(nums.size() - 1, p / 2);
    }
};