/**
 * @brief: Leetcode_2861_最大合金数
 * @link: https://leetcode.cn/problems/maximum-number-of-alloys/description/
 * @author: liangj.zhang
 * @date: 20/9/2025
 * 
 * @Difficulty: Medium
 * 
 * @Label: Binary Search
 * 
 * @Retrospect(worthy 1 - 5): 4
 * 
 * @thoughts:
 *  + 【思路 1】：二分查找
 *      + 假设 k 是 生产一份金属的消耗，那么就有公式 (k 就是代码中的 com_cost)：
 *          + k * 金属个数 - 原有的、用到的储量 <= budget
 *              + 具有单调性
 *          + 这个公式就能用来进行 二分查找
 *      + 下一个问题，是怎么确定 二分查找的范围，即金属个数范围；
 *          + 下手前，在纸上画了画；得到的结论是
 *              + 左值：stock[x, y, z, ...] composition[x0, y0, z0, ...]
 *                  + 个数是 x/x0 y/y0 z/z0 ... 中的最小值，通过原来的库存就能生产的金属数量，不需要 budget 的部分；
 *                  + 现在想想它也应该加上 budget / k；
 *              + 右值：x/x0 y/y0 z/z0 ... 中的最大值，通过原来的库存最多能生产的；然后加上 budget / k；
 *                  + 调试的时候，发现特殊的情况，composition[] 中合金的构造只需要一种金属；
 *                  + 这种时候不能忽略掉余数，以及 budget / k 的余数，两个余数之和，可能再多构成一份合金；
 *      + 分析：
 *          + 时间复杂度：O(k * n) + O(k * log( len(stock) ))
 *          + 空间复杂度：O(1)
 * 
 *      + rank:
 *          + 时间效率：0 ms, 击败 100%
 *          + 空间效率：58.83 MB, 击败 94.03%
 */

#include <vector>
#include <iostream>
using std::cout;
using std::endl;
using std::vector;

class Solution {
public:
    int maxNumberOfAlloys(int n, int k, int budget, vector<vector<int>>& composition, vector<int>& stock, vector<int>& cost) {
        
        int max_cnt = 0;
        for (int i = 0; i < k; ++i) {

            int com_cost = 0;
            // 确定个数的范围
            int min_range = INT_MAX;
            int max_range = -1;
            for (int j = 0; j < n; ++j) {
                
                com_cost += composition[i][j] * cost[j];

                int times = stock[j] / composition[i][j];
                if (times < min_range)
                    min_range = times;
                
                if (times > max_range)
                    max_range = times;
            }
            
            min_range += budget / com_cost;
            // 加 1 => 为了避免漏了 stock / composition 之后的余数，和 budget / com_cost 的余数，两余数之和，恰好能多得一份合金的情况
            max_range += budget / com_cost + 1; 
            int l(min_range), r(max_range);
            long long total_cost = 0;
            while (l <= r) {

                int mid = l + (r - l) / 2;  // mid -> 假定的金属个数
                total_cost = 1LL * mid * com_cost;
                for (int j = 0; j < n; ++j) {
                    
                    //total_cost -= (stock[j] < composition[i][j] * mid) ? 
                    //    stock[j] * cost[j] : composition[i][j] * mid * cost[j]; 
                    if (stock[j] < 1LL * composition[i][j] * mid) 
                        total_cost -= 1LL * stock[j] * cost[j];
                    else 
                        total_cost -= 1LL * composition[i][j] * mid * cost[j];
                }

                if (total_cost > budget)
                    r = mid - 1;
                else 
                    l = mid + 1;
            }

            if (max_cnt < r)
                max_cnt = r;
        }

        return max_cnt;
    }
};

int main() {

    int n = 1;
    int k = 8;
    int budget = 69;
    vector<vector<int>> composition = {{8},{9},{10},{10},{4},{4},{7},{6}};
    vector<int> stock = {10};
    vector<int> cost = {9};

    // int n = 3;
    // int k = 2;
    // int budget = 15;
    // vector<vector<int>> composition = {{1,1,1},{1,1,10}};
    // vector<int> stock = {0,0,0};
    // vector<int> cost = {1,2,3};

    cout << Solution().maxNumberOfAlloys(n, k, budget, composition, stock, cost) << endl;
}