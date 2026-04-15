/**
 * @brief: Leetcode_746_使用最小花费爬楼梯
 * @link: https://leetcode.cn/problems/min-cost-climbing-stairs/description/
 * @author: liangj.zhang
 * @date: 15/4/2026
 * 
 * @Difficulty: Easy
 * 
 * @Label: Dynamic Programming
 * 
 * @Retrospect(worthy 1 - 5): 4 -- classic - 同 Leetcode_70_climbing_stairs
 * 
 * @thoughts:
 *                                                          ┌─── --------- 平面(70) ---------
 *                                                      ┌───      69
 *                                                  ┌───          68
 *                                              ....             ...
 *                                          ┌───                  3
 *                                      ┌───                      2
 *                                  ┌───                          1
 *                              ┌───                              0
 *      以 70 阶台阶图示：
 *          想要踏上最后一级台阶 70，从地面 0 开始；
 *                                                                70
 *                                                             /      \
 *                                                            69      68
 *                                                          /    \ 
 *                                                        68      67
 *                                                      /    \
 *                                                    ...
 *                                                   /   \ 
 *                                                  3 
 *                                               /     \ 
 *                                              2       1
 *                                             / \ 
 *                                            1   0
 *                                            |
 *                                            0
 *      题目：可以选择从下标为 0 或下标为 1 的台阶
 *          ==> 就是边界，上到 stair 0 和 stair 1 的代价都是 0；
 *      但是离开某个 stair i，就要加上 cost[i]
 *  + 【思路 1】：DP + 递推 + 填表  --  自底向上的写法: >>> DP(表填充) <<<
 *      依旧是: f(n) = f(n - 1) + f(n - 2) => 只表示，当前值取决于前两个结果
 *      + 分析：
 *          + 时间复杂度：O(n)
 *          + 空间复杂度：O(n)
 *      + rank:
 *          + 时间效率：0 ms, 击败 100%
 *          + 空间效率：17.27 MB, 击败 67.13%
 * 
 * + 【思路 2】：>>> 状态压缩 DP <<<  -- 也叫：滚动数组优化（Rolling Array)
 *      cur = std::min(prev1 + cost[i - 1], prev2 + cost[i - 2])
 *      本质是：只保留必要的状态，把 DP 数组压成常数变量；
 *      + 分析：
 *          + 时间复杂度：O(n)
 *          + 空间复杂度：O(1)
 *      + rank:
 *          + 时间效率：0 ms, 击败 100%
 *          + 空间效率：17.22 MB, 击败 81.22%
 */

#include <vector>
using std::vector;

// 【思路 1】：DP + 递推 + 填表  --  自底向上的写法: >>> DP(表填充) <<<
class Solution {
public:
    int minCostClimbingStairs(vector<int>& cost) {
        int stepCnt = cost.size();
        int prev2, prev1;
        prev1 = prev2 = 0;
        for (int i = 2; i <= stepCnt; ++i) {
            int cur = std::min(prev1 + cost[i - 1], prev2 + cost[i - 2]);
            prev2 = prev1;
            prev1 = cur;
        }

        return prev1;
    }
};

// 【思路 2】：>>> 状态压缩 DP <<<  -- 也叫：滚动数组优化（Rolling Array)
class Solution {
public:
    int minCostClimbingStairs(vector<int>& cost) { // 2 <= cost.length <= 1000
        int stepCnt = cost.size();

        // 换个思路停在那，不收费；
        vector<int> step(stepCnt + 1, 0);
        for (int i = 2; i <= stepCnt; ++i) {
            // 到达 step[i] 时的开销
            step[i] = std::min(step[i - 1] + cost[i - 1], step[i - 2] + cost[i - 2]);
        }

        return step[stepCnt];
    }
};