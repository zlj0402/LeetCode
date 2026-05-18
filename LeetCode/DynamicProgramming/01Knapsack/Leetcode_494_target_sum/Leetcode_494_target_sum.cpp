/**
 * @brief: Leetcode_494_目标和
 * @link: https://leetcode.cn/problems/target-sum/description/
 * @author: liangj.zhang
 * @date: 8/5/2026
 * 
 * @updated:
 *  + 13/5/2026: add 【思路 3】：递归，记忆化搜索
 * 
 * @Difficulty: Medium
 * 
 * @Label: 01 Knapsack | backtracking
 * 
 * @Retrospect(worthy 1 - 5): 5
 * 
 * @thoughts:
 *  + 【思路 1】：纯回溯
 *      默认是加（不选），否则是减（选）
 *      + 分析：
 *          + 时间复杂度：O(2^n)
 *          + 空间复杂度：O(n)，递归深度
 *      + rank:
 *          + 时间效率：1382 ms, 击败 5.03%
 *          + 空间效率：11.41 MB, 击败 90.34%
 * + 【思路 2】：回溯，转换问题后剪枝
 *      + 正数和：p
 *      - 正数和：s - p
 *      公式：p - (s - p) = t
 *      得：p = (s + t) / 2
 * 
 *      首先 p 肯定是整数，如果 (s + t) / 2 不是整数，就没有结果为 target 的可能；=> s + t 是偶数
 *      0 <= sum(nums[i]) <= 1000、-1000 <= target <= 1000
 *      其次，p 是 + 正数和，就算没有前面加上 + 的组合，至少也是 0； => p >= 0 ==> s + t 是非负数，否则结果没有为 target 的可能；
 * 
 *      + 分析：
 *          + 时间复杂度：能够剪枝了 nums[idx] > left，会比 O(2^n) 小很多
 *          + 空间复杂度：最坏还是 O(n)
 *      + rank:
 *          + 时间效率：459 MB, 击败 21.86%
 *          + 空间复杂度：11.41 MB， 击败 90.74%
 * + 【思路 3】：递归，记忆化搜索
 *      >>> 转换为只要能找到 和为xxx 的问题；<<<
 *      转换问题的思路，见代码中附带的连着的注释；
 * 
 *      递归的方式，dfs 返回的结果表示，
 *      在递归中，dfs(idx - 1, left) 返回的是从位置 0 到位置 idx-1 的所有可能组合数，是一个完整的结果，不是增量。
 *      >>> 所以是 res =，而不是 res +=; <<<
 *      + 分析：
 *          + 时间复杂度：O(n * dp_size), dp_size 可用 sum 代替，即 O(n * sum)
 *          + 空间复杂度：O(n * dp_size)，dp_size 可用 sum 代替，即 O(n * sum)
 *      + rank:
 *          + 时间效率：3 ms, 击败 72.20%
 *          + 空间效率：17.31 MB, 击败 8.49%
 * + 【思路 4】：递推，填表
 *      + 分析：同上
 *      + rank:
 *          + 时间效率：7 ms, 击败 44.24%
 *          + 空间效率：15.06 MB, 击败 31.43%
 */

// 【思路 4】：递推，填表
#include <vector>
#include <algorithm>
#include <numeric>
using std::vector;

class Solution {
public:
    int findTargetSumWays(vector<int>& nums, int target) {
        int sum_target = std::accumulate(nums.begin(), nums.end(), 0) - std::abs(target);
        if (sum_target < 0 || sum_target % 2) return 0;

        int size = nums.size();
        target = sum_target / 2;
        vector dp(size + 1, vector<int>(sum_target / 2 + 1, 0));
        dp[0][0] = 1;
        // f[idx][left] = f[idx - 1][left] + f[idx - 1][left - nums[idx]]
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j <= target; ++j) {
                if (j < nums[i]) {
                    dp[i + 1][j] += dp[i][j];
                }
                else {
                    dp[i + 1][j] += dp[i][j] + dp[i][j - nums[i]];
                }
            }
        }

        return dp[size][target];
    }
};

// 【思路 3】：递归，记忆化搜索
class Solution {
public:
    int findTargetSumWays(vector<int>& nums, int target) {
        // 假设：加正号的那些数的和是 p，会加负号的那些数的和是 q；
        // 则有：p - q = target
        // 有 nums，我们就能求出所有数之和：s
        // 则有：s = p + q
        // 得到：p = (s + target) / 2, q = (s - target) / 2
        
        // p 和 q 都是要 >= 0 的，
        // 还能得到什么呢？
        // (s + target) >= 0, (s - target) / 2 >= 0 ==> s - abs(target) >= 0
        // p 和 q 都是整数 ==> (s + target) % 2 == 0 or (s - target) % 2 == 0 取其中一个就可以
        // 如果上述两个条件都完成不了的话，也就不符合我们的推论，也就无法达成题目的要求；

        // 满足上面的条件，就能有组合的可能，但有多少种可能，就需要算法来解决了
        // 对于每个 case, s 和 target 都是已知的
        // 我们需要知道组合得到 p 有多少种可能（直到 p 就直到 q，探寻其中一方的可能，就直到另一方有几种可能）

        // 当 target > 0 时，q 值更小；q = (s - target) / 2
        // 当 target < 0 时，p 值更小；p = (s + target) / 2
        // ==> 无论何时，s - abs(target) 都是任何情况下，最小的那一方；

        int new_target = accumulate(nums.begin(), nums.end(), 0) - std::abs(target);

        if (new_target / 2 < 0 || new_target % 2) return 0;

        vector dp(nums.size(), vector<int>(new_target + 1, -1));
        auto dfs = [&](this auto&& dfs, int idx, int left) -> int {
            if (idx < 0) return left == 0 ? 1 : 0;

            auto &res = dp[idx][left];
            
            if (res > -1) return res;
            else if (left < nums[idx]) {
                return res = dfs(idx - 1, left); // 意思：只能不选nums[idx]，返回的就是不选情况下的所有组合数; // 如果用 +=，会把之前可能存在的垃圾值也加上，导致错误结果
            }
            else {
                return res = dfs(idx - 1, left - nums[idx]) + dfs(idx - 1, left);
            }
        };

        return dfs(nums.size() - 1, new_target / 2);
    }
};

// 【思路 2】：回溯，转换问题后剪枝
class Solution {
public:
    int findTargetSumWays(vector<int>& nums, int target) {
        // + 正数和：p
        // - 正数和：s - p
        // 公式：p - (s - p) = t
        // 得：p = (s + t) / 2

        int sum = accumulate(nums.begin(), nums.end(), 0);

        auto dfs = [&](this auto&& dfs, int idx, int left) {
            if (idx < 0) {
                return left == 0 ? 1 : 0;
            }

            if (nums[idx] > left) {
                return dfs(idx - 1, left);
            }
            else {
                return dfs(idx - 1, left) + dfs(idx - 1, left - nums[idx]);
            }
        };

        if (sum + target < 0 || (sum + target) % 2) {
            return 0;
        }

        return dfs(nums.size() - 1, (sum + target) / 2);
    }
};

// 【思路 1】：纯回溯
class Solution {
public:
    int findTargetSumWays(vector<int>& nums, int target) {
        
        int cnt = 0;
        auto dfs = [&](this auto&& dfs, int idx, int left) {

            if (idx >= nums.size()) {
                if (left == target) {
                    ++cnt;
                }
                return;
            }

            // 不选，加
            dfs(idx + 1, left + nums[idx]);

            // 选，减
            dfs(idx + 1, left - nums[idx]);
        };

        dfs(0, 0);

        return cnt;
    }
};