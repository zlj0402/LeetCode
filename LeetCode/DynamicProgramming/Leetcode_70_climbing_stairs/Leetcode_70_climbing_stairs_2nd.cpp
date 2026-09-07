/**
 * @brief: Leetcode_70_climbing_stairs_2nd
 * @link: https://leetcode.cn/problems/climbing-stairs/description/
 * @author: liangj.zhang
 * @date: 2026/09/07
 * 
 * @Difficulty: Easy
 * 
 * @Label: DP
 * 
 * @thoughts:
 *  从底向上，踩上的那级台阶的可能，由前两级的台阶的可能决定：
 *      依旧：f(i) = max(f(i - 1), f(i - 2) + 1)
 *      上面的关系写错了，虽然任然是由前两项决定，但关系是：
 *          f(i) = f(i - 1) + f(i - 2)
 *          初值：prev1 = 1, prev2 = 0
 *  那我倒着写，自底向下
 *      f(i) = f(i - 1) + f(i - 2)
 */

#include <algorithm>

class Solution {
public:
    int climbStairs(int n) {
        int prev1 = 1, prev2 = 0;
        for (int i = n - 1; i >= 0; --i) {
            int tmp = prev1;
            prev1 = prev1 + prev2;
            prev2 = tmp;
        }
        return prev1;
    }
};