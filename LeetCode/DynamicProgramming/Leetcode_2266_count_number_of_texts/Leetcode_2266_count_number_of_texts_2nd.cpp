/**
 * @brief: Leetcode_2266_统计打字方案数_2nd
 * @link: https://leetcode.cn/problems/count-number-of-texts/description/
 * @author: liangj.zhang
 * @date: 2026/09/16
 * 
 * @updated:
 *  + 2026/09/17: add 【思路 1 -- 写法 2】：动态规划，空间 O(1)
 * 
 * @Difficulty: Medium
 * 
 * @Label: DP
 * 
 * @Retrospect(worthy 1 - 5): 5
 * 
 * @thoughts:
 *  + 【思路 1 -- 写法 1】：动态规划
 *      这题相比 Leetcode_2466 又多套了一层，增加了动态规划的次数；
 *      不过间距，在每个子动态规划中是固定的
 *      ===
 *      这题，这次的难点在于取模的问题；
 *          unsigned int ret = 1;
 *          unsigned long long tmp = ret * dp(...);  // 错误！
 *          ret = tmp % MOD;
 *      跟下面是不一样的；
 *          unsigned long long ret = 1;
 *          unsigned long long tmp = ret * dp(...);
 *          ret = tmp % MOD;
 *      两个整乘数在 bytes 都小于 4 字节时，会提升到 int，
 *      已经是 int * int，是不会默认根据左边赋值对象，在乘法之前提升的；
 *      当 int * int 的结果超过 int 的范围，会截断；
 * 
 *      unsigned int 截断的效果是：ret % (2^32)，跟我们要取模的 10^9 + 7 是不一样的；
 *      如果一直是取模同一个 MOD 结果是不受影响的；
 * 
 *      + 分析
 *          + 时间复杂度：O(n) * 2 * (3,4) == O(n)
 *          + 空间复杂度：O(n) -> dp 内部使用 O(target)
 *      + rank:
 *          + 时间效率：4 ms, 击败 82.16%
 *          + 空间效率：18.69 MB, 击败 53.76%
 * 
 *  + 【思路 1 -- 写法 2】：动态规划，空间 O(1)
 *      既然是每个 dp，间距不变的方式，那我也想写一种，明天写一下吧；
 *      ===
 *      收获就是写了一个通用的 stepNdp() 应对方案数的（间距是连着的）；
 *          - >>> 中间的取模很折腾，值得学习这里的这种频繁取模的用法；<<<
 *      + 分析：
 *          + 时间复杂度：O(n) * (3, 4) == O(n)
 *          + 空间复杂度：O(1)
 *      + rank:
 *          + 时间效率：2 ms，击败 90.28%
 *          + 空间效率：14.56 MB, 击败 95.58%
 */

#include <string>
#include <vector>
#include <array>
#include <numeric>
using std::vector;
using std::string;
using std::array;

// 【思路 1 -- 写法 2】：动态规划，空间 O(1)
class Solution {
private:
    static constexpr int MOD = 10'0000'0007;
    static constexpr string keyboard[] = {
        "", "", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"
    };
    // static constexpr array<int, 3> a3 = {1, 2, 4};
    // static constexpr array<int, 4> a4 = {1, 2, 4, 8};

    unsigned int stepNdp(int stepR, int stepCnt) {
        if (stepCnt <= stepR) return 1 << (stepCnt - 1);

        vector<unsigned int> arr(stepR);
        for (int i = 0; i < stepR; ++i) {
            arr[i] = 1 << i;  // 2^i
        }

        unsigned int curSum = std::accumulate(arr.begin(), arr.end(), 0);
        int curIdx = 0;
        // 这个循环 取模 可以反复学习
        for (int i = stepR; i < stepCnt; ++i) {
            auto new_val = curSum;
            curSum = ((curSum * 2) % MOD + MOD - arr[curIdx]) % MOD;  // ✓ 正确的模运算
            arr[curIdx] = new_val % MOD;
            curIdx = (curIdx + 1) % stepR;
        }

        return arr[(curIdx + stepR - 1) % stepR];
    }
public:
    int countTexts(string pressedKeys) {
        unsigned long long ret = 1;
        char lastC = pressedKeys[0];
        int lastCnt = 0;
        for (int i = 0; i < pressedKeys.size(); ++i) {
            if (lastC == pressedKeys[i]) ++lastCnt;
            else {
                // 不能拿一个 unsigned long long 取值取到底，再在循环外取模
                // 截断之后再取模，是错误， ret = tmp % MOD 每一次遍历都需要；
                unsigned long long tmp = ret * stepNdp(keyboard[lastC - '0'].size(), lastCnt);
                ret = tmp % MOD;
                lastC = pressedKeys[i];
                lastCnt = 1;
            }
        }
        unsigned long long tmp = ret * stepNdp(keyboard[lastC - '0'].size(), lastCnt);
        ret = tmp % MOD;

        return ret;
    }
};

// 【思路 1 -- 写法 1】：动态规划
class Solution {
private:
    static constexpr int MOD = 10'0000'0007;
    static constexpr string keyboard[] = {
        "", "", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"
    };
public:
    int countTexts(string pressedKeys) {
        auto dp = [](int stepR, int target) -> unsigned int {
            vector<unsigned int> rec(target + 1, 0);
            rec[0] = 1;
            for (int i = 1; i <= target; ++i) {
                unsigned long long tmp = 0;
                for (int j = 1; j <= stepR; ++j) {
                    tmp += (i - j < 0 ? 0 : rec[i - j]);
                }
                rec[i] = tmp % MOD;
            }
            return rec[target];
        };

        unsigned long long ret = 1;
        char lastC = pressedKeys[0];
        int lastCnt = 0;
        for (int i = 0; i < pressedKeys.size(); ++i) {
            if (lastC == pressedKeys[i]) ++lastCnt;
            else {
                // 不能拿一个 unsigned long long 取值取到底，再在循环外取模
                // 截断之后再取模，是错误， ret = tmp % MOD 每一次遍历都需要；
                unsigned long long tmp = ret * dp(keyboard[lastC - '0'].size(), lastCnt);
                ret = tmp % MOD;
                lastC = pressedKeys[i];
                lastCnt = 1;
            }
        }
        unsigned long long tmp = ret * dp(keyboard[lastC - '0'].size(), lastCnt);
        ret = tmp % MOD;

        return ret;
    }
};