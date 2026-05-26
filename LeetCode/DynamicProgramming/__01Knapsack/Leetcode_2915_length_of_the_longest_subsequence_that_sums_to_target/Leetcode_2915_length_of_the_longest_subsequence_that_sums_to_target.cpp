/**
 * @brief: Leetcode_2915_和为目标值的最长子序列的长度
 * @link: https://leetcode.cn/problems/length-of-the-longest-subsequence-that-sums-to-target/description/
 * @author: liangj.zhang
 * @date: 26/5/2026
 * 
 * + updated:
 *  + 26/5/2026: 【思路 1/2.1/2.2】
 * 
 * @Difficulty: Medium
 * 
 * @Label: Dynamic Programming & 01-Knapsack
 * 
 * @Retrospect(worthy 1 - 5): liangj.zhang
 * 
 * @thoughts:
 *  + 【思路 1】：回溯
 *      回溯 + dfs 的写法，的思路就是：
 *          选择当前的 idx 对应值之后，从 left 当中扣除；
 *          剩下的，交给下一次递归，做相同的事，就可以了；
 *      边界的处理就是：
 *          如果 left == 0 时，说明有一条 dfs 线，能获得目标和；返回 0，表示此次递归是有效的；
 *          idx >= n || left < 0，就说明这条 dfs 线，不能达到目标和，结束递归；
 *      dfs “归”之后，内容：
 *          回到某一节点之后，将该节点的所有返回情况进行比较，有合法的情况（即，能满足的情况），才选取合法的最大的 [序列长度 + 1（到达此节点，长度 + 1）]
 *          如果，一个合法的都没有，继续返回无效值；表明该条 dfs 线不符合情况；
 * 
 *      + 分析：
 *          + 时间复杂度：O(2^n)
 *          + 空间复杂度：O(n)
 *      ---
 *      超时
 * + 【思路 2】：动态规划 & 递推填表
 *      创建 arr[n + 1][target + 1],
 *      在 idx 处，t < nums[idx] 的范围，是 nums[idx] 值都比 t 大了，是不会有可能，从前面的值 + nums[idx] 到达 t == nums[idx] 的边界的；
 *          所以，t < nums[idx] => dp[idx][0-nums[idx]) 的情况，之前从前一轮 idx - 1 的状态组得到，没有变动；
 *      后面 t >= nums[idx] 的情况，除了从前一组状态继承过来，还多了 pre + nums[i] = t 的可能，从上一组 dp[idx - 1][t - nums[i]] 位置的可能结果再 + 1，与继承过来的进行比较；（当然，得前一个位置是有效情况）
 *      + 分析：
 *          + 时间复杂度：O(n * target)
 *          + 空间复杂度：O(n * target)
 *      + rank:
 *          + 时间效率：203 ms, 击败 35.82%
 *          + 空间效率：154.21 MB, 击败 32.50%
 * + 【思路 2 -- 写法 2】：动态规划 & 递推填表
 *      改变一下，默认的状态无效值，使得返回情况更简单；
 *      思路一点没变；
 */

#include <vector>
using std::vector;

// 【思路 2 -- 写法 2】：动态规划 & 递推填表
class Solution {
public:
        int lengthOfLongestSubsequence(vector<int>& nums, int target) {
        int n = nums.size();

        vector dp(n + 1, vector<int>(target + 1, -1));
        dp[0][0] = 0;

        for (int i = 0; i < n; ++i) {
            for (int t = 0; t <= target; ++t) { // 原来错误的写法: int t = 1; => 要将 f[0] = 1 延续下去，后面直接能从 0 到 t 的结果，也能算一个情况；

                dp[i + 1][t] = dp[i][t];
                if (t >= nums[i]) {
                    int pre = dp[i][t - nums[i]];
                    if (pre > -1)
                        dp[i + 1][t] = std::max(dp[i + 1][t], pre + 1);
                }
            }
        }

        return dp[n][target]; 
    }
};

// 【思路 2】：动态规划 & 递推填表
class Solution {
public:
    int lengthOfLongestSubsequence(vector<int>& nums, int target) {
        int n = nums.size();

        vector dp(n + 1, vector<int>(target + 1, 0));
        dp[0][0] = 1;

        for (int i = 0; i < n; ++i) {
            for (int t = 0; t <= target; ++t) { // 原来错误的写法: int t = 1; => 要将 f[0] = 1 延续下去，后面直接能从 0 到 t 的结果，也能算一个情况；
                // if (t < nums[i]) {
                //     dp[i + 1][t] = dp[i][t];
                // }
                // else if (int preStatus = dp[i][t - nums[i]]; preStatus == 0) {
                //     dp[i + 1][t] = dp[i][t];
                // }
                // else {
                //     // 错误写法：在没有选择从 dp[i][t - nums[i]] 过来之前，dp[i][t] 可能是有值的，如果比现在这种 preStatus + 1 情况大；那就漏掉了；
                //     // dp[i + 1][t] = std::max(dp[i + 1][t], preStatus + 1);
                // }

                dp[i + 1][t] = dp[i][t];
                if (t >= nums[i]) {
                    int pre = dp[i][t - nums[i]];
                    if (pre > 0)
                        dp[i + 1][t] = std::max(dp[i + 1][t], pre + 1);
                }
            }
        }

        return dp[n][target] == 0 ? -1 : dp[n][target] - 1; 
    }
};

// 【思路 1】：回溯
class Solution {
public:
    int lengthOfLongestSubsequence(vector<int>& nums, int target) {
        int n = nums.size();

        // 能达到 target，就在返回值后，递增个数；
        auto dfs = [&](this auto&& dfs, int idx, int left) -> int {
            if (left == 0) return 0;
            if (idx >= n || left < 0) return -2;

            int len = -2;
            for (int i = idx; i < n; ++i) {
                int tmp = dfs(i + 1, left - nums[i]);
                if (tmp != -2)
                    len = std::max(tmp + 1, len);
            }

            return len;
        };

        int ans = dfs(0, target);
        return ans == -2 ? -1 : ans; 
    }
};