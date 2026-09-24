/**
 * @brief: Leetcode_494_目标和_2nd
 * @link: https://leetcode.cn/problems/target-sum/description/
 * @author: liangj.zhang
 * @date: 2026/09/03
 * 
 * @updated:
 *      + 2026/09/23: add【思路 2】：记忆化搜索
 *      + 2026/09/24: add【思路 3】：动态规划 -- 状态压缩
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
 *  + 【思路 3】：动态规划 -- 状态压缩（直接跳过了滚动数组了..）
 *      + 分析: 
 *          + 时间复杂度：O(n * t) == O(n * sum)
 *          + 空间复杂度：O(t) == O(sum)
 *      + rank:
 *          + 时间效率：0 ms, 击败 100%
 *          + 空间效率：12.31 MB, 击败 53.26%
 */ 
#include <vector>
#include <numeric>
#include <cmath>
using std::vector;

// 【思路 3】：动态规划 -- 状态压缩
class Solution {
public:
    int findTargetSumWays(vector<int>& nums, int target) {
        // 现在问题已经变成，从 nums 当中找出和为 (sum - abs(target)) / 2 的可能
        int sum = std::accumulate(nums.begin(), nums.end(), 0);
        int t = (sum - abs(target)) / 2;
        if (t < 0 || (sum - abs(target)) % 2) return 0;

        int n = nums.size();
        vector<int> rec = vector<int>(t + 1, 0); // 现在存的是 t+1 范围内，每个位置的可能性
        rec[0] = 1; // 每个 idx，都有一个范围段，是前面 [0, idx-1] 

        int sum_ = 0;
        for(int i = 0; i < n; ++i) {
            sum_ += nums[i];
            for (int j = std::min(t, sum_); j >= nums[i]; --j) {
                // 每个位置的可能性 = 上次该位置遗留下来的 + （该位置 - nums[i] 上一次遗留值）
                /**
                 * 参考 【思路 2】 的：
                 * if (left < nums[idx]) return r = dfs(idx - 1, left); =》 当值 j < nums[i]，那么直接用继承过来的值就可以了；
                 * return r = dfs(idx - 1, left - nums[idx]) + dfs(idx - 1, left); =》 要么再多一种可能，是从 rec[j - nums[i]] 跳过来的，两个位置的可能性相加
                 */
                rec[j] += rec[j - nums[i]];
            }
        }
        return rec[t];
    }
};

//【思路 2】：记忆化搜索
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

// 【思路 1】：纯 dfs
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