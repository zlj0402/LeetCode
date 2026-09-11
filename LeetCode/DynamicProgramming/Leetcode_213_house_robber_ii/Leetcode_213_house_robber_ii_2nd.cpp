/**
 * @brief: Leetcode_213_打家劫舍_II_2nd
 * @link: https://leetcode.cn/problems/house-robber-ii/description/
 * @author: liangj.zhang
 * @date: 2026/09/11
 * 
 * @Difficulty: Medium
 * 
 * @Label: Dynamic Programming
 * 
 * @Retrospect(worthy 1 - 5): 4
 * 
 * @thoughts:
 *  + 【思路 1】：动态规划
 *      idx0 idx(n-1) 不能同时取，
 *      那就 [0, n-2] 取一次， [1, n-1] 取一次；
 *  
 *      取得最大值有 3 种情况，
 *      1. idx0 idx(n-2) 两个边界都取了
 *      2. idx1 idx(n-1) 
 *      3. idx1 idx(n-2)
 *      3 种边界情况，就算真的出现第 3 种情况，1 和 2 都会包含的；
 *      ---
 *      还有一种特殊情况就是只有一个元素，直接返回；
 *      ====
 *      思路还是受到以前的记忆导向；
 * 
 *      + 分析：
 *          + 时间复杂度：O(n)
 *          + 空间复杂度：O(1)
 *      + rank:
 *          + 时间效率：0 ms, 击败 100%
 *          + 空间效率：10.18 MB, 66.30%
 */

#include <vector>
using std::vector;

class Solution {
public:
    int rob(vector<int>& nums) {
        int prev2 = 0, prev1 = 0;
        int n = nums.size();
        if (n == 1) return nums[0];

        auto func = [](int n, int *data) {
            int prev2 = 0, prev1 = 0;
            for (int i = 0; i < n; ++i) {
                int tmp = prev1;
                prev1 = std::max(prev2 + data[i], prev1);
                prev2 = tmp;
            }
            return prev1;
        };

        return std::max(func(n-1, nums.data()), func(n-1, nums.data() + 1));
    }
};