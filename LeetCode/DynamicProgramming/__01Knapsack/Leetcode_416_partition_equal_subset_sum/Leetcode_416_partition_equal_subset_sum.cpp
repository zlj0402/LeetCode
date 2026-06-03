/**
 * @brief: Leetcode_416_分割等和子集
 * @link: https://leetcode.cn/problems/partition-equal-subset-sum/description/
 * @author: liangj.zhang
 * @date: 29/5/2026
 * 
 * @updated:
 *      + 29/5/2026: add 【思路 1】：动态规划 -- 递推填表
 *      + 30/5/2026: add 【思路 2 -- 写法1】：动态规划 -- 状态压缩
 *                   add 【思路 2 -- 写法2】：动态规划 -- 状态压缩 -- 这题的标准方式
 * 
 * @Difficulty: Medium
 * 
 * @Label: Dynamic Programming & 01-Knapsack
 * 
 * @Retrospect(worthy 1 - 5): 4
 * 
 * @thoughts:
 *  + 【思路 1】：动态规划 -- 递推填表
 *      从底向上递推，还写递推填表的过程，是为了加强理解递推填表到，状态压缩的变换过程；
 *      ---
 *      这题的主要是，
 *          1. 转换问题：分成两个子集，子集的和加起来是数组之和；=> 那么我只要找到和为 sum / 2，那么剩下的另一半，不就是另一个集合；
 *                      转换后的问题：从 nums 数组中，选与不选数组元素，使得和为 sum/2； => 典型的 01-Knapsack
 *          2. 只要存在就行，可以不用延续之前做的 Leetcode_494 Leetcode_2915，求方案数，求方案中最长的序列；
 *                      如果采用求方案数的方式，方案的可能和会很大，还要考虑溢出等等；
 *                      最佳方式，有没有，见 【思路 2 -- 写法 2】
 *      + 分析：
 *          + 时间复杂度：O(n * sum(nums))
 *          + 空间复杂度：O(n * sum(nums))
 *      + rank:
 *          + 时间效率：171 ms, 击败 10.88%
 *          + 空间效率：108.70 MB, 击败 5.05%
 * 
 *  + 【思路 2 -- 写法1】：动态规划 -- 状态压缩
 *      压缩成一个数组，使用的方案中最长序列的方式；
 *      + 分析：
 *          + 时间复杂度：O(n * sum(nums)) 加了优化，最坏是这种情况；
 *          + 空间复杂度：O(sum(nums))
 *      + rank:
 *          + 时间效率：27 ms, 击败 94.21%
 *          + 空间效率：14.56 MB, 击败 58.69%
 *  + 【思路 2 -- 写法2】：动态规划 -- 状态压缩 -- 这题的标准方式
 *      不使用方案中最长序列，也不求方案数的方式；
 *      只看有没有；
 *      + 分析：同 【思路 2 -- 写法1】
 *      + rank:
 *          + 时间效率：26 ms, 击败 96.26%
 *          + 空间效率：14.79 MB, 击败 45.33%
 */

#include <vector>
#include <numeric>
using std::vector;

// 【思路 2 -- 写法2】：动态规划 -- 状态压缩 -- 这题的标准方式
class Solution {
public:
    bool canPartition(vector<int>& nums) {
        int sum = std::accumulate(nums.begin(), nums.end(), 0);
        if (sum % 2) return false;

        int target = sum / 2;
        int n = nums.size();
        vector<int> dp(target + 1, 0);
        dp[0] = 1;

        sum = 0;
        for (int i = 0; i < n; ++i) {
            sum += nums[i];
            for (int j = std::min(target, sum); j >= nums[i]; --j) {
                dp[j] |= dp[j - nums[i]];
            }
        }

        return dp[target];
    }
};

// 【思路 2 -- 写法1】：动态规划 -- 状态压缩
class Solution {
public:
    bool canPartition(vector<int>& nums) {
        int sum = std::accumulate(nums.begin(), nums.end(), 0);
        if (sum % 2) return false;

        int target = sum / 2;
        int n = nums.size();
        vector<int> dp(target + 1, 0);
        dp[0] = 1;

        sum = 0;
        for (int i = 0; i < n; ++i) {
            sum += nums[i];
            for (int j = std::min(target, sum); j >= nums[i]; --j) {
                int pre = dp[j - nums[i]];
                if (pre) {
                    dp[j] = std::max(dp[j], pre + 1);
                }
                // dp[j] += dp[j - nums[i]];
            }
        }

        return dp[target];
    }
};

// 【思路 1】：动态规划 -- 递推填表
// 分割成两个子集，每个子集的和相等 => sum(set1) + sum(set2) = sum(all), sum(set1) = sum(set2)
// 那么只要找到一组和为 sum(all) / 2，那就是有可能了；
// 所以问题，就变成：在这一组数当中，选择某些数，每个数最多使用一次的问题；
class Solution {
public:
    bool canPartition(vector<int>& nums) {
        int sum = std::accumulate(nums.begin(), nums.end(), 0);
        if (sum % 2) return false;

        int target = sum / 2;
        int n = nums.size();
        // vector dp(nums.size() + 1, vector<int>(target + 1, 0));
        vector dp(nums.size() + 1, vector<long long>(target + 1, 0));
        dp[0][0] = 1;

        for (int i = 0; i < n; ++i) {
            for (int j = 0; j <= target; ++j) {
                dp[i+1][j] = dp[i][j];
                if (j >= nums[i]) {
                    // 这题只要有结果就好，不需要找最长的序列，也不需要到达 target 有多少种可能；
                        // 达到 target 最长序列
                        // int pre = dp[i][j - nums[i]];
                        // if (pre) {
                        //     dp[i+1][j] = std::max(dp[i+1][j], pre + 1);
                        // }
                    // 达到 target 有多少种可能 => 这种方式，容易相加 overflow，long long 类型都挡不住
                    dp[i+1][j] += dp[i][j - nums[i]];
                }
            }
        }

        return dp[n][target];
    }
};