/**
 * @brief: Leetcode_2466_统计构造好字符串的方案数
 * @link: https://leetcode.cn/problems/count-ways-to-build-good-strings/description/
 * @author: liangj.zhang
 * @date: 2/5/2026
 * 
 * @Difficulty: Medium
 * 
 * @Label: Dynamic Programming
 * 
 * @Retrospect(worthy 1 - 5): 5
 * 
 * @thoughts:
 *  + 【思路 1】：动态规划
 *      还是看了灵神题解，才有了思路的；
 *      ---
 *      还是记住动态规划的一条思路线：当前结果的和，是由前面的有直接关联的，加上（规则）变换得到的；
 *      比如 zero = 2, one = 4;
 *      rec[2] = 1
 *          00
 *      rec[4] = rec[4 - zero] + rec[4 - one] = rec[2] + rec[0] = 1 + ? (这里，才知道 rec[0] 要为 1，后面才有值)
 *                                                              = 1 + 1 = 2
 *          0000,
 *          1111
 *      rec[6] = rec[6 - zero] + rec[6 - one] = rec[4] + rec[2] = 2 + 1 = 3
 *          0000 00
 *          1111 00
 *          ---
 *          00 1111
 *      rec[8] = rec[8 - zero] + rec[8 - one] = rec[6] + rec[4] = 3 + 2 = 5
 *          0000 0000
 *          1111 0000
 *          00 111100
 *          ---
 *          0000 1111
 *          1111 1111
 *      -----------------
 *      用图示在纸上，演示一遍，我才更加清楚：  
 *      边界时，
 *          (i - zero < 0 ? 0 : rec[i - zero]) + (i - one < 0 ? 0 : rec[i - one]);
 *      i - zero < 0 或者 i - one < 0，是没有构成字符串情况的，理应让 i - zero/one < 0 时，返回 0
 *      i - zero == 0 或者 i - one == 0，是第一次构成这个长度的字符串，情况是 1；==> 即 rec[0] = 1
 *      ---
 *      其他无法构成字符串的长度，在初始化时，就已经是 rec[i] = 0;
 *      ---
 *      还有一点就是，结果可能会很大，需要考虑类型 & 按题目要求取模；
 *      
 *      + 分析：
 *          + 时间复杂度：O(n)
 *          + 空间复杂度：O(n)
 *      + rank:
 *          + 时间效率：3 ms, 击败 98.95%
 *          + 空间效率：11.37 MB, 击败 83.33%
 */

#include <vector>
using std::vector;

#define MOD 10'0000'0007
class Solution {
public:
    int countGoodStrings(int low, int high, int zero, int one) {
        vector<unsigned int> rec(high + 1, 0);
        rec[0] = 1;

        for (int i = 1; i <= high; ++i) {
            unsigned long long tmp = (i - zero < 0 ? 0 : rec[i - zero]) + (i - one < 0 ? 0 : rec[i - one]);
            rec[i] = tmp % MOD;
        }

        unsigned long long sum = 0;
        for (int i = low; i <= high; ++i) {
            sum += rec[i];
        }

        return sum % MOD;
    }
};

int main() {
    int low = 3;
    int high = 3;
    int zero = 1;
    int one = 1;

    Solution().countGoodStrings(low, high, zero, one);
}