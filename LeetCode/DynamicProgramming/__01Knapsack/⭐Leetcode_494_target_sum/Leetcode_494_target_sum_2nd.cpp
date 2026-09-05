#include <vector>
#include <numeric>
using std::vector;

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