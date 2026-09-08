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
 *  + 【思路 1】：动态规划
 *  从底向上，踩上的那级台阶的可能，由前两级的台阶的可能决定：
 *      依旧：f(i) = max(f(i - 1), f(i - 2) + 1)
 *      上面的关系写错了，虽然任然是由前两项决定，但关系是：
 *          f(i) = f(i - 1) + f(i - 2)
 *          初值：prev1 = 1, prev2 = 0
 *  那我倒着写，自底向下
 *      f(i) = f(i - 1) + f(i - 2)
 * 
 *      + 分析：
 *          + 时间复杂度：O(n)
 *          + 空间复杂度：O(1)
 *      + rank:
 *          + 时间效率：0 ms
 *          + 空间效率：7.70 MB, 击败 78.23%
 * 
 *  + 【思路 2】：递归
 *      超时
 *      + 分析：
 *          + 时间复杂度：O(2^n)
 *          + 空间复杂度：O(n)
 * 
 *  + 【思路 3】：记忆化搜索
 *      + 分析：
 *          + 时间复杂度：O(n)
 *          + 空间复杂度：O(n)
 *      + rank: 
 *          + 时间效率：0 ms
 *          + 空间效率：8.56 MB, 击败 14.40%
 *      
 */

#include <vector>
#include <algorithm>
using std::vector;

// 【思路 1】：动态规划
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

//【思路 2】：递归
class Solution {
public:
    int climbStairs(int n) {
        if (n <= 0) {
            if (n == 0) return 1;
            return 0;
        }        

        return climbStairs(n - 1) + climbStairs(n - 2);
    }
};

// 【思路 3】：记忆化搜索
class Solution {
public:
    int climbStairs(int n) {

        vector<int> rec(n + 1, 0);
        auto dfs = [&] (this auto&& dfs, int n) {
            if (n < 0) return 0;
            if (n == 0) return 1;

            if (rec[n] != 0) return rec[n];
            else {
                rec[n] = dfs(n - 1) + dfs(n - 2);
                return rec[n];
            }
        };

        return dfs(n);
    }
};