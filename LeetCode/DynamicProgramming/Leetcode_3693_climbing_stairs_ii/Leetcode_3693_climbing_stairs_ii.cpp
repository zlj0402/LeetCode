/**
 * @brief: Leetcode_3693_爬楼梯_II
 * @link: https://leetcode.cn/problems/climbing-stairs-ii/description/
 * @author: liangj.zhang
 * @date: 16/4/2026
 * 
 * @updated:
 *  + 17/4/2026: add【思路 2】：>>> 状态压缩 DP <<<  -- 也叫：滚动数组优化（Rolling Array)
 * 
 * @Difficulty: Medium
 * 
 * @Label: Dynamic Programming
 * 
 * @Retrospect(worthy 1 - 5): 3 -- 题目难理解，不然给 4 分
 * 
 * @thoughts:
 *                                                 ⬇
 *                                                 n
 *                                             n-1┌──
 *                                             ┌──
 *                                        3 ...
 *                                     2 ┌──
 *                               ⬇  1 ┌──
 *                               0 ┌── 
 *                              ┌── 
 *      题目的意思：求得从 stair 0 走到 stair n 的最小消耗；
 *      最难理解的一句话：你还得到了一个长度为 n 的 下标从 1 开始 的整数数组 costs，其中 costs[i] 是第 i 级台阶的成本。
 *          这句 "下标从 1 开始" 的整数数组 costs => 想表述是 costs 中的数据，从左往右，表示的是阶梯1 到 阶梯n [stair 1, stair n]，每个阶梯的 cost;
 *          即 cost[0] -> 代表 stair 1 的 cost
 *             cost[1] -> 代表 stair 2 的 cost, ...
 *      以示例 2 作图示：
 *                                               ⬇
 *                                               4
 *                                           3  ┌───
 *                                       2  ┌─── c4:2 -- costs[3]
 *                               ⬇   1  ┌─── c3:6 -- costs[2]
 *                               0  ┌─── c2:1 -- costs[1]
 *                              ┌─── c1:5 -- costs[0]
 *      阶梯上面的数字，是阶梯编号
 *      阶梯下面 c1:5 => 上到 stair 1 的 cost;(成本定义公式的前半部分)
 *              c3:6 => 上到 stair 3 的 cost;
 * 
 *      公式：f(j) = std::min(f(j - 1) + cost[j - 1] + (j - (j - 1))^2， 即 f(j) = std::min(f(j - 1) + cost[j - 1] + 1，
 *                           f(j - 2) + cost[j - 1] + (j - (j - 2))^2,                     f(j - 2) + cost[j - 1] + 4，
 *                           f(j - 3) + cost[j - 1] + (j - (j - 3))^2)                     f(j - 3) + cost[j - 1] + 9)
 *          cost[j - 1] 表示的是 stair j 的 cost;
 * 
 *  + 【思路 1】：DP + 递推 + 填表  --  自底向上的写法: >>> DP(表填充) <<<
 *      f(n) = std::min(f(n - 1) + cost[n - 1] + (n - (n - 1))^2，
 *                      f(n - 2) + cost[n - 1] + (n - (n - 2))^2,
 *                      f(n - 3) + cost[n - 1] + (n - (n - 3))^2)
 *      由简单的爬楼梯题，当前结果由前两个决定，变成了，当前结果由前3个决定；
 *          有了前三个结果之后，算上从各自到当前阶梯的消耗，去最小值 => 得到当前阶梯的值；
 *      ---
 *      这题的难点，在于题目意思的理解，见上面图示；
 *      
 *      + 分析：
 *          + 时间复杂度：O(n)
 *          + 空间复杂度：O(n)
 *      + rank:
 *          + 时间效率：11 ms, 击败 72.65%
 *          + 空间效率：173.56 MB, 击败 63.04%
 * 
 *  + 【思路 2】：>>> 状态压缩 DP <<<  -- 也叫：滚动数组优化（Rolling Array)
 *      本质是：只保留必要的状态，把 DP 数组压成常数变量； -- 因为当知道前 3 个结果之后，加上当前 3 个各自路径的消耗，就能求得结果；
 *      + 分析：
 *          + 时间复杂度：O(n)
 *          + 空间复杂度：O(1)
 *      + rank:
 *          + 时间效率：0 ms, 击败 100%
 *          + 空间效率：165.76 MB, 击败 85.08%
 */
#include <vector>
#include <algorithm>
#include <iostream>
using std::cout;
using std::endl;
using std::vector;

// 【思路 2】：>>> 状态压缩 DP <<<  -- 也叫：滚动数组优化（Rolling Array)
class Solution {
public:
    int climbStairs(int n, vector<int>& costs) {
        int size = costs.size();
        int prev3 = 0; // stair -2 => f(-2)
        int prev2 = 0; // stair -1 => f(-1)
        int prev1 = 0; // stair 0  =>  f(0) => 到达第一个台阶 0，没有步骤，开销为 0
        for (int j = 1; j <= size; ++j) {
            // j - 1 的台阶，跳到 j
            int curMin = prev1 + (costs[j - 1] + 1);
            // j - 2 的台阶，跳到 j
            if (j - 2 >= 0) { curMin = std::min(curMin, prev2 + (costs[j - 1] + 4)); }
            // j - 3 的台阶，跳到 j
            if (j - 3 >= 0) { curMin = std::min(curMin, prev3 + (costs[j - 1] + 9)); }
            prev3 = prev2;
            prev2 = prev1;
            prev1 = curMin;
        }
        return prev1;
    }
};

// 【思路 1】：DP + 递推 + 填表  --  自底向上的写法: >>> DP(表填充) <<<
class Solution {
public:
    int climbStairs(int n, vector<int>& costs) { // 1 <= costs.length <= 10^5
        int size = costs.size();
        vector<int> f(size + 1, 0);
        // f(n) = std::min(f(n - 1) + cost[n - 1] + (n - (n - 1))^2, 
        //                 f(n - 2) + cost[n - 1] + (n - (n - 2))^2,
        //                 f(n - 3) + cost[n - 1] + (n - (n - 3))^2)
        for (int i = 1; i <= size; ++i) {
            int minCur = f[i - 1] + costs[i - 1] + 1;
            
            if (i - 2 >= 0) {
                minCur = std::min(minCur, f[i - 2] + costs[i - 1] + 4); // 原来错误的写法：std::min(minCur, f[i - 2] + costs[i - 2] + 4);
            }

            if (i - 3 >= 0) {
                minCur = std::min(minCur, f[i - 3] + costs[i - 1] + 9); // 原来错误的写法：std::min(minCur, f[i - 3] + costs[i - 3] + 9);
            }
            f[i] = minCur;
            // std::cout << i << ", " << f[i] << std::endl;
        }

        return f[size];
    }
};

int main() {
    vector<int> costs = {1, 2, 3, 4};
    Solution().climbStairs(costs.size(), costs);
}