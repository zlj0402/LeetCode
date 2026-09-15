/**
 * @brief: Leetcode_377_组合总和_Ⅳ_2nd
 * @link: https://leetcode.cn/problems/combination-sum-iv/description/
 * @author: liangj.zhang
 * @date: 2026/09/15
 * 
 * @Difficulty: Medium
 * 
 * @Label: 动态规划
 * 
 * @Retrospect(worthy 1 - 5): 4
 * 
 * @thoughts:
 *  按灵神视频题单的顺序做过来，这题又是上一题 Leetcode_2466 的进阶，
 *  Leetcode_70 爬楼梯那题，是数量固定（一次迈1阶或2阶），距离差值也固定（1,2）；
 *  Leetcode_2466 是数量固定，但距离差值是每个 cases 不同的；
 *  这题是每个 cases，数量不固定，距离差值也不固定；
 * 
 *  + 【思路 1】 动态规划
 *      思想还是一样的，每个位置的可能性，由其前面已经求出来的可能性决定；
 *      f(n) = f(n1) + f(n2) + ...
 * 
 *      + 分析：
 *          + 时间复杂度：O(n * target)
 *          + 空间复杂度：O(1001) == O(1)，实际算 O(target)
 *      + rank:
 *          + 时间效率：0 ms, 击败 100%
 *          + 空间效率：8.81 MB, 击败 99.25%
 */

#include <vector>
using std::vector;

class Solution {
private:
    static constexpr int MAXN = 1001;
    static unsigned int rec[MAXN];
public:
    int combinationSum4(vector<int>& nums, int target) {
        std::memset(rec, 0, sizeof(unsigned int) * (target + 1));
        rec[0] = 1;
        int n = nums.size();
        for (int i = 1; i <= target; ++i) {
            for (int j = 0; j < n; ++j) {
                rec[i] += i - nums[j] < 0 ? 0 : rec[i - nums[j]];
            }
        }

        return rec[target];
    }
};

unsigned int Solution::rec[MAXN];