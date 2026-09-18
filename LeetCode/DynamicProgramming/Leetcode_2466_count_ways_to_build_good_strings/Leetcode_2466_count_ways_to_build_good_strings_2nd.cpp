/**
 * @brief: Leetcode_2466_统计构造好字符串的方案数
 * @link: https://leetcode.cn/problems/count-ways-to-build-good-strings/description/
 * @author: liangj.zhang
 * @date: 2026/09/14
 * 
 * @updated:
 *      + 2026/09/18: add 【思路 2】：记忆化搜索
 * 
 * @Difficulty: Medium
 * 
 * @Label: DP
 * 
 * @Retrospect(worthy 1 - 5): 4
 * 
 * @thoughts:
 *  + 【思路1 -- 写法1】：动态规划
 *      还是把握住 f(n) = Relation(f(n1), f(n2))
 *      有这个意识，还是在看了第一次的题解之后，有理解
 *      
 *      中间，有两个子字符串，怎么都无法构成的位置，那就是有可能某个位置的方案数是 0
 *      某个位置的方案数，就是取决于前面两个位置的方案数之和；
 * 
 *      这题完全就是 Leetcode_70 爬楼梯方案数的进阶，进阶在哪里呢，
 *          原来由前面紧贴的两个位置决定了，
 *          这次不是紧贴的，不过好在位置差还是固定的；
 * 
 *      + 分析：
 *          + 时间复杂度：O(high)
 *          + 空间复杂度：O(100001) == O(1)，其实严谨点，算 O(high)
 *      + rank:
 *          + 时间效率：7 ms, 击败 58.47%
 *          + 空间效率：8.23 MB, 击败 98.91%
 * 
 *  + 【思路 1 -- 写法 2】：动态规划
 *      参考了第一次写的方式，减少了数组元素类型的大小，减少循环当中取模操作；
 *      + 分析：同上
 *      + rank：    
 *          + 时间效率：2 ms, 击败 99.32%
 *          + 空间效率：8.19 MB, 击败 99.04%
 * 
 *  + 【思路 2】：记忆化搜索
 *      在递归当中记录；
 *      最开始想这个递归怎么写？这有边界的递归...
 *      想麻烦了，就拿范围内的每个值去递归；每次递归记录的值越来越多；会过略掉很多；
 *          某个点有记录就不会深入的递归下去，时间复杂度还是没变，依旧 O(n);
 *      + 分析：
 *          + 时间复杂度：O(high)
 *          + 空间复杂度：算是 O(high)
 *      + rank:
 *          + 时间效率：7 ms, 击败 56.75%
 *          + 空间效率：11.19 MB, 击败 92.09%
 */

#include <vector>
#include <cstring>
using std::vector;

#define MOD 10'0000'0007
#define MAXCNT 100001

// 【思路 2】：记忆化搜索
class Solution {
private:
    static vector<int> rec;
public:
    int countGoodStrings(int low, int high, int zero, int one) {
        std::memset(rec.data(), -1, sizeof(int) * (high + 1));
        rec[0] = 1;
        auto dfs = [&](this auto&& dfs, int left) {
            if (left < 0) return 0;
            
            unsigned long long ret = 0;
            if (int idx = left - zero; idx >= 0 && rec[idx] != -1) 
                ret += rec[idx];
            else 
                ret += dfs(idx);

            if (int idx = left - one; idx >= 0 && rec[idx] != -1) 
                ret += rec[idx];
            else 
                ret += dfs(idx);

            return rec[left] = ret % MOD;
        };

        unsigned long long ret = 0;
        for (int i = low; i <= high; ++i) {
            ret += dfs(i);
        }
        return ret % MOD;
    }
};

vector<int> Solution::rec(MAXCNT, 0);

// // 【思路 1 -- 写法 2】：动态规划，减少循环中的取模操作
// class Solution {
// private:
//     static unsigned int rec[MAXCNT];
// public:
//     int countGoodStrings(int low, int high, int zero, int one) {
//         std::memset(rec, 0, sizeof(unsigned int) * (high + 1));
//         rec[0] = 1;

//         for (int i = std::min(zero, one); i <= high; ++i) {
//             // f(n) = rec[n - zero] + rec[n - one]
//             unsigned long long tmp = (i - zero >= 0 ? rec[i - zero] : 0) + (i - one >= 0 ? rec[i - one] : 0);
//             rec[i] = tmp % MOD;
//         }

//         unsigned long long ret = 0;
//         for (int i = low; i <= high; ++i) {
//             ret += rec[i];
//         }

//         return ret % MOD;
//     }
// };

// unsigned int Solution::rec[MAXCNT];

// // 【思路1 -- 写法1】：动态规划
// class Solution {
// private:
//     static unsigned int rec[MAXCNT];
// public:
//     int countGoodStrings(int low, int high, int zero, int one) {
//         std::memset(rec, 0, sizeof(unsigned int) * (high + 1));
//         rec[0] = 1;

//         for (int i = std::min(zero, one); i <= high; ++i) {
//             // f(n) = rec[n - zero] + rec[n - one]
//             if (i - zero >= 0) rec[i] = (rec[i] + rec[i - zero]) % MOD;
//             if (i - one >= 0) rec[i] = (rec[i] + rec[i - one]) % MOD; 
//         }

//         unsigned int ret = 0;
//         for (int i = low; i <= high; ++i) {
//             ret = (ret + rec[i]) % MOD;
//         }

//         return ret;
//     }
// };

// unsigned int Solution::rec[MAXCNT];

int main() {
    int low = 2;
    int high = 3;
    int zero = 1;
    int one = 2;

    unsigned int ret = Solution().countGoodStrings(low, high, zero, one);
    return ret;
}