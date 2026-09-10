/**
 * @brief: Leetcode_3693_爬楼梯_II_2nd
 * @link: https://leetcode.cn/problems/climbing-stairs-ii/description/
 * @author: liangj.zhang
 * @date: 2026-09-10
 * 
 * @Difficulty: Medium
 * 
 * @Label: Linear DP
 * 
 * @Retrospect(worthy 1 - 5): 4
 * 
 * @thoughts:
 *  + 【思路 1】：动态规划
 *      这题跟 Leetcode_70_climbing_stairs 一模一样；
 *      一次最多两阶梯 -> 变一次最多3阶梯
 *      一个是方式数 -> 一个是 cost，cost 需要考虑开始边界是否在 0 之外
 *      
 *      这次写的跟以前写的思路一样，不过个人觉得没有以前写的那么简洁；（主要是边界处理上）
 *      + 分析：
 *          + 时间复杂度：3 * O(n) == O(n)
 *          + 空间复杂度：O(1) 
 *      + rank:
 *          + 时间效率: 9 ms，击败 75.76%
 *          + 空间效率：165.90 MB, 击败 77.08%
 * 
 *  + 【思路 2】：递归
 *      知道递归会超时，但就是想写一下递归；
 *      但还是想了很久，说明思考递归的方式还是有问题，得想好每一遍做的同样的事是什么，和边界结束情况（这次是边界结束情况没有想明白，试探着写出来的）
 *      对于边界 0 的情况要单独处理；
 *      + 分析：
 *          + 时间复杂度：O(3^n)
 *          + 空间复杂度：O(n)
 * 
 *  + 【思路 3】：记忆化搜索
 *      写的不是很好，
 *      想简化的话会超时
 *      ===
 *      后面发现原因，for(int s : {1,2,3}) => {1,2,3} 每次构造->额外开销
 * 
 *      + 分析：
 *          + 时间复杂度：O(n)
 *          + 空间复杂度：O(1)
 *      + rank:
 *          + 时间效率：77 ms, 击败 5.17%
 *          + 空间效率：184.43 MB, 击败 5.02%
 */

#include <vector>
#include <iostream>
using std::vector;

// 【思路 2】：递归
class Solution {
private:
    static constexpr int INF = 10'0000'0001;
public:
    int climbStairs(int n, vector<int>& costs) {
        
        auto dfs = [&](this auto &&dfs, int idx) {
            // if (idx < 0) return INF;
            // if (idx == 0) return 0; // 递归想了很久，似乎必须有 0 这个条件

            if (idx <= 0) return idx == 0 ? 0 : INF;
            int curMin = INF;
            for (int s : {1, 2, 3}) {
                curMin = std::min(curMin, dfs(idx - s) + costs[idx - 1] + s * s);
            }
            return curMin;
        };

        return dfs(n);
    }
};

// 【思路 3】：记忆化搜索
class Solution {
private:
    static constexpr int INF = 10'0000'0001;
public:
    int climbStairs(int n, vector<int>& costs) {

        vector<int> rec(n + 1, INF);
        rec[0] = 0;
        
        auto dfs = [&](this auto &&dfs, int idx) {
            if (idx < 0) return INF;

            if (rec[idx] != INF) {
                return rec[idx];
            }
            else {
                // 注释掉的这块会超时
                // int curMin = INF;
                // for (int s : {1, 2, 3})  // 问题出在 {1,2,3} => 会重复构造
                //     if (idx >= s) 
                //         curMin = min(curMin, dfs(idx - s) + costs[idx - 1] + s * s);
                
                // return rec[idx] = curMin;

                int curMin = INF;
                if (idx >= 1) curMin = std::min(curMin, dfs(idx - 1) + costs[idx - 1] + 1);
                if (idx >= 2) curMin = std::min(curMin, dfs(idx - 2) + costs[idx - 1] + 4);
                if (idx >= 3) curMin = std::min(curMin, dfs(idx - 3) + costs[idx - 1] + 9);
                rec[idx] = curMin;
                return curMin;
            }
        };

        return dfs(n);
    }
};

// class Solution {
// public:
//     int climbStairs(int n, vector<int>& costs) {
//         int prev3 = 0, prev2 = 0, prev1 = 0;
//         vector<int> prev(3, 0);
//         int cnt = costs.size();
//         for (int i = 1; i <= cnt; ++i) {
//             int tmp = prev1;
//             int min_ = 10'0000'0001;
//             for (int j = 3; j > 0; --j) {
//                 int pre = prev[j - 1];
//                 if (i - j >= 0) {
//                     prev[j - 1] += costs[i - 1] + j * j;
//                 }
//                 min_ = prev[j - 1] != 0 ? std::min(prev[j - 1], min_) : min_;
//                 prev[j - 1] = pre;  // 复原
//             }
//             prev[2] = prev[1];
//             prev[1] = prev[0];
//             prev[0] = min_;
//         }

//         return prev[0];
//     }
// };

int main() {
    vector<int> nums = {4};
    std::cout<< Solution().climbStairs(nums.size(), nums) << std::endl;
}