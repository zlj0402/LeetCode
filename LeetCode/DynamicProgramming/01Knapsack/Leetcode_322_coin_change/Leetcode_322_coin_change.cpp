/**
 * @brief: Leetcode_322_零钱兑换
 * @link: https://leetcode.cn/problems/coin-change/description/
 */

#include <vector>
#include <iostream>
#include <functional>
using std::vector;

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