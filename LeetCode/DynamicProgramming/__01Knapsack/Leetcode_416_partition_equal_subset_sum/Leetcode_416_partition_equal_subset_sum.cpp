#include <vector>
#include <numeric>
using std::vector;

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