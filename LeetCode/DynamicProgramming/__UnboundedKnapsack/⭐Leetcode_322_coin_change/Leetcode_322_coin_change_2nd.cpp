/**
 * @brief: Leetcode_322_零钱兑换_2nd
 * @link: https://leetcode.cn/problems/coin-change/description/
 * @author: liangj.zhang
 * @date: 2026/09/27
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
 */
#include <vector>
using std::vector;

//【思路 1】：完全背包（每个值都能被选无数次）
class Solution {
private:
    static constexpr int INF = __INT_MAX__;
public:
    int coinChange(vector<int>& coins, int amount) {
        vector<int> rec(amount + 1, -1);
        rec[0] = 1;
        int coinCnt = coins.size();
        for (int i = 1; i <= amount; ++i) {
            int min_ = INF;
            for (int j = 0; j < coinCnt; ++j) {
                int tmp = i - coins[j];
                if (tmp >= 0 && rec[tmp] > 0) {
                    min_ = std::min(rec[tmp], min_);
                }
            }
            rec[i] = min_ == INF ? 0 : min_ + 1;
        }

        return rec[amount] == INF ? -1 : rec[amount] - 1;
    }
};

int main() {
    vector<int> coins = {1, 2, 5};
    int amount = 11;
    Solution().coinChange(coins, amount);
}