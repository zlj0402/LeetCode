/**
 * @brief: Leetcode_322_零钱兑换
 * @link: https://leetcode.cn/problems/coin-change/description/
 * @author: liangj.zhang
 * @date: 25/5/2026
 * 
 * @Difficulty: Medium
 * 
 * @Label: Unbounded Knapsack
 * 
 * @Retrospect(worthy 1 - 5): 5
 * 
 * @thoughts:
 *  + 【思路 1.1】：副作用性（命令式）递归 -- 因为它的核心逻辑不是靠返回值构建出答案，而是靠副作用——也就是修改函数外部的 minCnt 变量——来留下最终结果
 *      现在越来越觉得，回溯就是完全的暴力求解；
 *      ---
 *      超时
 *  + 【思路 1.2】：返回值式递归
 *      这种写法，更容易平滑过度到，记忆化搜索的阶段；
 *      ---
 *      但也还是递归，超时
 *  + 【思路 2】：状态压缩
 *      刚写这题的时候，我还在往 01背包上带，想不透（其实视频第二题，已经归为完全背包）
 *      我没有想那么多，越思考，越觉得，这题不是跟 《Leetcode_377》一模一样；
 *      每一个 target 路径上的值，都是可以由前 n 个 nums[i] 的节点决定；
 *          重心还是，公式：f[t] = 前面的节点决定；
 *      + 分析：
 *          + 时间复杂度：O(n * amount)
 *          + 空间复杂度：O(amount)
 *      + rank:
 *          + 时间效率：8 ms, 击败 99.46%
 *          + 空间效率：17.45 MB, 击败 86.03%
 */

#include <vector>
#include <iostream>
#include <functional>
using std::vector;

// 【思路 2】：状态压缩
class Solution {
public:
    int coinChange(vector<int>& coins, int amount) {
        int n = coins.size();
        const unsigned int INF = __INT_MAX__;
        vector<unsigned int> dp(amount + 1, INF);
        dp[0] = 0;

        for (int i = 1; i <= amount; ++i) {
            for (int j = 0; j < n; ++j) {
                if (i - coins[j] >= 0) {
                    dp[i] = std::min(dp[i], dp[i - coins[j]] + 1);
                }
            }
        }

        return dp[amount] == INF ? -1 : dp[amount];
    }
};

// 【思路 1.2】：返回值式递归
class Solution {
public:
    int coinChange(vector<int>& coins, int amount) {
        int n = coins.size();
        const int INF = 1e9;

        std::function<int(int,int)> dfs = [&](int idx, int left) -> int {
            if (left == 0) return 0;
            if (left < 0 || idx == n) return INF;

            int res = INF;

            for (int i = idx; i < n; ++i) {
                int sub = dfs(i, left - coins[i]);
                if (sub != INF) {
                    res = std::min(res, sub + 1);
                }
            }

            return res;
        };

        int ans = dfs(0, amount);
        return ans == INF ? -1 : ans;
    }
};

// 【思路 1.1】：副作用性（命令式）递归
class Solution {
public:
    int coinChange(vector<int>& coins, int amount) {
        int size = coins.size();
        int minCnt = __INT_MAX__;

        auto dfs = [&](this auto&& dfs, int idx, int left, int cnt) { 
            if (left == 0 && cnt < minCnt) minCnt = cnt;

            if (idx == size || left <= 0) {
                return;
            }

            for (int i = idx; i < size; ++i) {
                dfs(i, left - coins[i], cnt + 1);
            }
        };

        dfs(0, amount, 0);

        return minCnt == __INT_MAX__ ? -1 : minCnt;
    }
};

int main() {
    vector<int> coins = {1, 2, 5};
    int amount = 11;
    std::cout << Solution().coinChange(coins, amount) << std::endl;
}