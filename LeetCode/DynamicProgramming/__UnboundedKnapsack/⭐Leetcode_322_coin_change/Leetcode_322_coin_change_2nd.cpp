/**
 * @brief: Leetcode_322_零钱兑换_2nd
 * @link: https://leetcode.cn/problems/coin-change/description/
 * @author: liangj.zhang
 * @date: 2026/09/28
 * 
 * @updated: 
 *  + 2026/09/29: add 【思路 1 -- 写法 2】：完全背包
 * 
 * @Difficulty: Medium
 * 
 * @Label: DP
 * 
 * @Retrospect(worthy 1 - 5): 5
 * 
 * @thoughts:
 *  + 【思路 1】：完全背包（每个值都能被选无数次）
 *      + 分析：
 *          + 时间复杂度：O(amount * coinCnt)
 *          + 空间复杂度：O(amount)
 *      + rank:
 *          + 时间效率：31 ms, 击败 24.52%
 *          + 空间效率：17.57 MB, 击败 53.73%
 *  + 【思路 1 -- 写法 2】：完全背包
 *      + 分析：
 *          + 时间复杂度：O(amount * coinCnt)
 *          + 空间复杂度：O(amount)
 *      + rank:
 *          + 时间效率：19 ms, 击败 81.50%
 *          + 空间效率：12.41 MB，击败 98.01%
 */

#include <vector>
#include <cstring>
using std::vector;

class Solution {
private:
    static constexpr int MAXCNT = 10001;
    static constexpr int INF = __INT_MAX__;
    static vector<int> rec;
public:
    int coinChange(vector<int>& coins, int amount) {
        for (int i = 1; i <= amount; ++i) rec[i] = -1;
        rec[0] = 0;
        
        int coinCnt = coins.size();
        for (int i = 1; i <= amount; ++i) {
            int min_ = INF;
            for (int j = 0; j < coinCnt; ++j) {
                int tIdx = i - coins[j];
                if (tIdx >= 0 && rec[tIdx] >= 0) {
                    min_ = std::min(rec[tIdx], min_);
                }
            }
            if (min_ != INF) rec[i] = min_ + 1;
        }

        return rec[amount];
    }
};

vector<int> Solution::rec(MAXCNT, 0);

//【思路 1】：完全背包（每个值都能被选无数次）
class Solution {
private:
    static constexpr int INF = __INT_MAX__;
public:
    int coinChange(vector<int>& coins, int amount) {
        vector<int> rec(amount + 1, -1);
        rec[0] = 0;
        int coinCnt = coins.size();
        for (int i = 1; i <= amount; ++i) {
            int min_ = INF;
            for (int j = 0; j < coinCnt; ++j) {
                int tmp = i - coins[j];
                if (tmp >= 0 && rec[tmp] != -1) {
                    min_ = std::min(rec[tmp], min_);
                }
            }
            rec[i] = min_ == INF ? -1 : min_ + 1;
        }

        return rec[amount];
    }
};

int main() {
    vector<int> coins = {1, 2, 5};
    int amount = 11;
    Solution().coinChange(coins, amount);
}