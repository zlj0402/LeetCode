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
 */

#include <vector>
#include <iostream>
using std::vector;

class Solution {
public:
    int climbStairs(int n, vector<int>& costs) {
        int prev3 = 0, prev2 = 0, prev1 = 0;
        vector<int> prev(3, 0);
        int cnt = costs.size();
        for (int i = 1; i <= cnt; ++i) {
            int tmp = prev1;
            int min_ = 10'0000'0001;
            for (int j = 3; j > 0; --j) {
                int pre = prev[j - 1];
                if (i - j >= 0) {
                    prev[j - 1] += costs[i - 1] + j * j;
                }
                min_ = prev[j - 1] != 0 ? std::min(prev[j - 1], min_) : min_;
                prev[j - 1] = pre;  // 复原
            }
            prev[2] = prev[1];
            prev[1] = prev[0];
            prev[0] = min_;
        }

        return prev[0];
    }
};

int main() {
    vector<int> nums = {4};
    std::cout<< Solution().climbStairs(nums.size(), nums) << std::endl;
}