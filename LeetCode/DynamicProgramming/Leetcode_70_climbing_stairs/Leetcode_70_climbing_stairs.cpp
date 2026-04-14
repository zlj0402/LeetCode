/**
 * @brief: Leetcode_70_爬楼梯
 * @link: https://leetcode.cn/problems/climbing-stairs/description/?envType=study-plan-v2&envId=top-100-liked
 * @author: liangj.zhang
 * @date: 14/4/2026
 * 
 * @Difficulty: Easy
 * 
 * @Label: Dynamic Programming
 * 
 * @Retrospect(worthy 1 - 5): 4 -- classic
 * 
 * @thoughts:
 *                                                          ┌───  70
 *                                                      ┌───      69
 *                                                  ┌───          68
 *                                              ....             ...
 *                                          ┌───                  4
 *                                      ┌───                      3
 *                                  ┌───                          2
 *                              ┌───                              1
 *          --------------------                                  0
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
 *      到达节点 2 的可能性，是节点 1 的可能性 + 节点 2 的可能性；
 *      更清楚的理解是：节点 2 到所有其下叶子结点的路径数量；
 *      ---
 *      再以这种方式理解节点 3；
 *      节点 n 也就清晰了；
 *      这种自底向上写法的，边界：f(0) == 1, f(1) == 1，代表着一条路径；
 *  + 【思路 1】：DP + 递推 + 填表  --  自底向上的写法: >>> DP(表填充) <<<
 *      典型的 DP 递推：f(n) = f(n - 1) + f(n - 2)
 *      
 *      + 分析：
 *          + 时间复杂度：O(n)
 *          + 空间复杂度：O(n)
 *      + rank:
 *          + 时间效率: 0 ms, 击败 100%
 *          + 空间效率：7.80 MB, 击败 62.26%
 * 
 *  + 【思路 2】：>>> 状态压缩 DP <<<  -- 也叫：滚动数组优化（Rolling Array)
 *      cur = prev1 + prev2;
 *      本质是：只保留必要的状态，把 DP 数组压成常数变量；（前两个状态
 *      
 *      + 分析：
 *          + 时间复杂度：O(n)
 *          + 空间复杂度：O(1)
 *      + rank:
 *          + 时间效率：0 ms，击败 100%
 *          + 空间效率：7.64 MB, 击败 87.81%
 */

#include <vector>
using std::vector;

class Solution {
public:
    int climbStairs(int n) {    // n >= 1
        int prev2 = 1;  // step 0
        int prev1 = 1;  // step 1
        for (int i = 2; i <= n; ++i) {
            int cur = prev1 + prev2;
            prev2 = prev1;
            prev1 = cur;
        }
        return prev1;
    }
};

// 【思路 1】：DP + 递推 + 填表  --  自底向上的写法 
class Solution {
public:
    int climbStairs(int n) {    // n >= 1
        vector<int> rec(n + 1, 0);
        rec[0] = 1;
        rec[1] = 1;
        for (int i = 2; i <= n; ++i) {
            rec[i] = rec[i - 1] + rec[i - 2];
        }
        return rec[n];
    }
};