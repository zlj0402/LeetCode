/**
 * @breif: Leetcode_2915_和为目标值的最长子序列的长度_2nd
 * @link: https://leetcode.cn/problems/length-of-the-longest-subsequence-that-sums-to-target/description/
 * @author: liangj.zhang
 * @date: 2026/10/09
 * 
 * @updated:
 *  + 2026/10/10:
 *      + add 【思路 2 -- 写法 1】：记忆化搜索，有隐形的坑
 *      + add 【思路 2 -- 写法 2】：记忆化搜索，正确写法
 * 
 * @Difficulty: Medium
 * 
 * @Label: 01Knapsack
 * 
 * @Retrospect(worthy 1 - 5): 5 -- 难考虑周全
 * 
 * @thoughts:
 *  + 【思路 1】：回溯 -- 超时，超时不是关键
 *      + 注释中，原来错误的写法：
 *          写得时候，没有考虑到，在选与不选，两者当中，如果都没有构成 dfs 路径和是 target，那么
 *              就不应该，在选择的时候，每次都默认给选择的情况 + 1;
 *              虽然可能因为 MIN 取得够小，只要有一个可能构成 target 的路径，就会将默认 + 1 的错误情况取消掉，
 *              但是如果没有一个 dfs 路径和构成 target，那么得到的结果 res 就是 MIN + 递归深度的结果（也不是准确的递归深度，因为在 left < num[idx] 时，不会走选择的路径，就不会默认 +1）；
 *              res == INIMIN ? -1 : res; ==> 既不是 -1，也不是正数；
 *      + 分析：
 *          + 时间复杂度：O(2^n)
 *          + 空间复杂度：O(n)
 * 
 *  + 【思路 2 -- 写法 1】：记忆化搜索，有隐形的坑
 *  + 【思路 2 -- 写法 2】：记忆化搜索，正确写法
 *      + 写法 1：自己让所有默认状态值和无解时的返回值，都为 INTMIN;
 *                  那么就会在整个都无解的 case 中，记忆化搜索退化成回溯，无解值被认为是默认状态，以为没有得到过结果，下次再过来时，会重新走一遍递归；
 *                  面对 case 中，数组长度比较大的情况，就会超时，因为回溯的时间复杂度是 O(2^n) 比如：
 *                      nums = [3,7,6,7,2,2,2,10,7,10,8,7,7,10,7,3,1,2,8,3,5,1,5,8,4,8,8,7,6,2,4,8,10,9,5,9,2,3,1,7,4,10,7,5,2,8,6,5,1,3,5,9,9,10,6,10]
 *                      target = 162
 *                  写法 1 和 思路1（回溯）都卡在了上面这个 case；
 *      + 写法 2：让默认值与无解值不一样，这样每次判断，只要判断这个状态位置是否有结果就可以了：
 *                  if (res != DEF) {} ==> 不等于原来的默认值，就是有结果，即使无解也是一种结果；
 *                + 不会发生，原来是无解，跑到后面又有解了的情况吗？
 *                      不会。 这是记忆化搜索能成立的核心前提——同一个状态 (idx, left) 的答案是一个确定的函数值，只取决于这两个参数，跟到达它的路径无关。
 *                      + dfs(idx, left) 的定义是："用 nums[0..idx] 这些数，凑出和为 left 的最长子序列长度"。
 *                      + 给定 (idx, left)，这个值是唯一确定的。
 *                      + 所以一旦算出来是"无解"，它永远是无解，不可能换个调用路径就变成有解。
 *      + 分析：
 *          + 时间复杂度：O(n * target)
 *          + 空间复杂度：O(n * target)
 *      + rank:
 *          + 时间效率：412 ms, 击败 7.74%
 *          + 空间效率：150.60 MB, 击败 53.87%
 */

#include <vector>
using std::vector;

// 【思路 2 -- 写法 2】：记忆化搜索，正确写法
class Solution {
private:
    static constexpr int DEF = -100000;
public:
    int lengthOfLongestSubsequence(vector<int>& nums, int target) {
        if (std::accumulate(nums.begin(), nums.end(), 0) < target) return -1;

        int size = nums.size();
        vector<vector<int>> rec(size, vector<int>(target + 1, DEF));
        
        [&](this auto&& dfs, int idx, int left) {
            if (idx < 0) return left == 0 ? 0 : -1; // -1 => 无解

            auto &res = rec[idx][left];
            if (res != DEF) {}
            else if (left < nums[idx]) return res = dfs(idx - 1, left);
            else {
                int skip = dfs(idx - 1, left);
                int take = dfs(idx - 1, left - nums[idx]);
                if (take != -1) res = std::max(skip, take + 1);
                else res = skip;
            }

            return res;
        } (size - 1, target);

        return rec[size - 1][target];
    }
};

// 【思路 2 -- 写法 1】：记忆化搜索，有隐形的坑
class Solution {
private:
    static constexpr int INTMIN = -100000;
public:
    int lengthOfLongestSubsequence(vector<int>& nums, int target) {
        if (accumulate(nums.begin(), nums.end(), 0) < target) return -1;
        int size = nums.size();
        vector<vector<int>> rec(size, vector<int>(target + 1, INTMIN)); 
        
        auto dfs = [&](this auto&& dfs, int idx, int left) {
            if (idx < 0) return left == 0 ? 0 : INTMIN; // 错误写法：默认状态值和无解是同一个值

            auto &res = rec[idx][left];
            if (res != INTMIN) {}
            else if (left < nums[idx]) return res = dfs(idx - 1, left);
            else {
                int skip = dfs(idx - 1, left);
                int take = dfs(idx - 1, left - nums[idx]);
                if (take != INTMIN) res = std::max(skip, take + 1);
                else res = skip;
            }

            return res;
        };

        dfs(size - 1, target);
        int res = rec[size - 1][target];
        return res == INTMIN ? -1 : res;
    }
};

//【思路 1】：回溯 -- 超时，超时不是关键
class Solution {
public:
    int lengthOfLongestSubsequence(vector<int>& nums, int target) {
        int INTMIN = -100000;
        auto dfs = [&](this auto&& dfs, int idx, int left) -> int {
            if (idx < 0) return left == 0 ? 0 : INTMIN; // 原来错误的写法：if (idx < 0) return left == 0 ? 1 : INTMIN;
            
            if (left < nums[idx]) return dfs(idx - 1, left);

            // 原来错误的写法：
            // return std::max(dfs(idx - 1, left), dfs(idx - 1, left - nums[idx]) + 1); // 有可能选与不选，两种路径都不能构成路径和是 target

            int skip = dfs(idx - 1, left);
            int take = dfs(idx - 1, left - nums[idx]);

            if (take != INTMIN) { // dfs 路径的组合结果是否构成 target
                return std::max(skip, take + 1);
            }

            return skip;
        };

        int res = dfs(nums.size() - 1, target);
        return res == INTMIN ? -1 : res;
    }
};
