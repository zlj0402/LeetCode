/**
 * @brief: Leetcode_746_使用最小花费爬楼梯_2nd
 * @link: https://leetcode.cn/problems/min-cost-climbing-stairs/description/
 * @author: liangj.zhang
 * @date: 2026-09-09
 * 
 * @Difficulty: Easy
 * 
 * @Label: DP
 * 
 * @Retrospect(worthy 1 - 5): 3
 * 
 * @thoughts:
 *  + 【思路 1】：动态规划
 *      可以从 0 或者从 1 台阶开始，=> 那么在台阶 0 和台阶 1 的最小 cost 就是 0
 *      后面就是正常的 递推；
 *      ---
 *      看例题，最后一节台阶是 cost[n-1] 后面的位置，相当于 end; => 所以遍历的边界是 i <= n;
 * 
 *      + 分析：
 *          + 时间复杂度：O(n)
 *          + 空间复杂度：O(1)
 *      + rank:
 *          + 时间效率：0 ms, 击败 100%
 *          + 空间效率：17.08 MB, 击败 95.46%
 */

#include <vector>
using std::vector;

class Solution {
public:
    int minCostClimbingStairs(vector<int>& cost) {
        int prev1 = 0;    // 初始，站在台阶 2 的 min cost
        int prev2 = 0;          // 站在台阶 1 的 min cost
        int n = cost.size();
        for (int i = 2; i <= n; ++i) {
            int tmp = prev1;
            prev1 = std::min(prev2 + cost[i - 2], prev1 + cost[i - 1]);
            prev2 = tmp;
        }

        return prev1;
    }
};