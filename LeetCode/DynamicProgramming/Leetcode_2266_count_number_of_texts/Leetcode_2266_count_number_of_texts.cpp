/**
 * @brief: Leetcode_2266_统计打字方案数
 * @link: https://leetcode.cn/problems/count-number-of-texts/description/
 * @author: liangj.zhang
 * @date: 5/5/2026
 * 
 * @Difficulty: Medium
 * 
 * @Label: Dynamic Programming
 * 
 * @Retrospect(worthy 1 - 5): 4
 * 
 * @thoughts:
 *  + 【思路 1】：动态规划，递推填表 -- 记忆化搜索
 *      做完 《Leetcode_377_组合总和_Ⅳ》《Leetcode_2466_统计构造好字符串的方案数》做的这题，
 *      所以思路还是比较清晰的，
 *      ---
 *      同一个按键，表示不是字母，是通过按下次数来决定的，
 *      就可以把 按一下，理解为跨一个阶梯；
 *              按两下，理解为跨两个阶梯；
 *              按三下，理解为跨三个阶梯；
 *      ---
 *      只考虑组合情况，所有三个字母的按键，都可以使用同一个记忆话数组；
 *                      所有四个字母的按键，都可以使用自己的记忆化数组；
 *      我的思路是，用一个static数组，面对其他 case 的时候，已经考虑过的范围，直接用数组中的结果就好了，
 *      当遇到更大的范围，从最大的位置再开始，继续进行递推；
 *      ---
 *      这种方式应该是最优的记忆化，唯一有消耗的，就是扩容带来的消耗；
 *          还有个小缺点，就是稍微麻烦一点；
 * 
 *      + 分析：
 *          + 时间复杂度：遍历字符串 O(n) + 最坏情况，需要做 O(n) 的递推；
 *          + 空间复杂度：O(n)，虽然是静态的变量，但也可以算作是 O(n)【按照复杂度的定义不是】
 *      + rank:
 *          + 时间效率：11 ms, 击败 70.29%
 *          + 空间效率：15.90 MB, 击败 64.56%
 */

#include <string>
#include <vector>
#include <unordered_map>
#include <iostream>
using std::vector;
using std::string;
using std::unordered_map;

#define um unordered_map
#define MOD 10'0000'0007
class Solution {
private:
    static vector<int> steps;
    static um<int, std::pair<int, vector<unsigned int>>> recs;

public:
    int countTexts(string pressedKeys) {
        unsigned int ret = 1;

        int lastChar = '0';
        int lastCnt = 0;
        for (auto c : pressedKeys) {
            if (c != lastChar) {
                ret = (1ULL * ret * recs[steps[lastChar - '0']].second[lastCnt]) % MOD;
                lastChar = c;
                lastCnt = 0;
            }
            auto &rec = recs[steps[lastChar - '0']];
            if (++lastCnt <= rec.first) {   // lastCnt 新的变化
                continue;
            }
            else {
                ++rec.first;    // 新的变化
                unsigned long long sum = 0;
                for (int i = 1; i <= steps[lastChar - '0']; ++i) {
                    int idx = rec.first - i;
                    sum += idx < 0 ? 0 : rec.second[idx];
                }
                rec.second.push_back({static_cast<unsigned int>(sum % MOD)});
            }
        }
        ret = (1ULL * ret * recs[steps[lastChar - '0']].second[lastCnt]) % MOD;

        return ret;
    }
};

vector<int> Solution::steps = {0, 0, 3, 3, 3, 3, 3, 4, 3, 4};

um<int, std::pair<int, vector<unsigned int>>> Solution::recs = {
    {0, {0, {1}}},  // special design, for first char
    {3, {0, {1}}},
    {4, {0, {1}}}
};

int main() {
    string pressedKeys = "22233";
    std::cout << Solution().countTexts(pressedKeys) << std::endl;
}