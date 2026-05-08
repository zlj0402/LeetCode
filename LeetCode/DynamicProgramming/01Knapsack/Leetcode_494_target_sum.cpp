/**
 * @brief: Leetcode_494_目标和
 * @link: https://leetcode.cn/problems/target-sum/description/
 * @author: liangj.zhang
 * @date: 8/5/2026
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
 */

#include <vector>
#include <algorithm>
#include <numeric>
using std::vector;

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