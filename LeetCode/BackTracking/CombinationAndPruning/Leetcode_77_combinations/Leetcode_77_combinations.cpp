/**
 * @brief: Leetcode_77_组合
 * @link: https://leetcode.cn/problems/combinations/description/
 * @author: liangj.zhang
 * @date: 25/2/2026
 * 
 * @updated:
 *  + 10/3/2026: add 【思路 2 -- 写法 1/2】：选与不选子集型回溯 -- 组合 -- 剪枝
 * 
 * @Difficulty: Medium
 * 
 * @Label: Backtracking & Pruning
 * 
 * @Retrospect(worthy 1 - 5): 4, classic
 * 
 * @thoughts:
 *  + 【思路 1】：枚举回溯 -- 组合 -- 剪枝
 *      枚举回溯：每次选中一个数，后续从剩下的数中，继续选取一个（即递归）；
 *          所有组合的过程，参考：Leetcode_78_子集
 *      剪枝：1. 当 path.size() == k 时，直接 return，这样后面继续选中的话，长度肯定会超过 k，一定都不符合情况
 *           2. 当剩下的长度不够，组成长度为 k 个的组合，遍历的后续，可选的数据会越来越短，从第一个不符合长度的位置，就直接 return: if (path.size() + (n - j) + 1 < k) return;
 *              -- 第 2 点剪枝，是看灵神的视频的
 *      + 分析：
 *          + 时间复杂度：O(C(n, k) * k)
 *          + 空间复杂度：O(k)
 *      + rank:
 *          + 时间效率：43 ms, 击败 96.67%
 *          + 空间效率：61.2 MB, 击败 84.25%
 * 
 *  + 【思路 2 -- 写法 1】：选与不选子集型回溯 -- 组合 -- 剪枝
 *      选与不选
 *      + 分析：
 *          + 时间复杂度：O(C(n, k) * k)
 *          + 空见复杂度：O(k)
 *      + rank:
 *          + 时间效率：95 ms, 击败 27.16%
 *          + 空间效率：107.52 MB, 击败 16.01%
 *  + 【思路 2 -- 写法 2】：选与不选子集型回溯 -- 组合 -- 剪枝
 *      与写法 1 相比，唯一不同是，最后的组合数，刚好和剩余 k 相同时；
 *      本来递归到底就是刚刚好的，那我直接遍历全部加进来；遍历比递归消耗略小，不然【思路 1】和【思路 2】同复杂度，但时间并不在同一区域的原因;
 *      + 分析：同写法1，以及思路1
 *      + rank:
 *          + 时间效率：91 ms, 击败 35.48%
 *          + 空间效率：106.29 MB, 击败 17.48%
 */

#include <vector>
using std::vector;

// class Solution {
// public:
//     vector<vector<int>> combine(int n, int k) {
        
//         vector<int> path;
//         vector<vector<int>> ans;

//         auto dfs = [&](this auto&& dfs, int idx) -> void {

//             if (path.size() == k) {

//                 ans.push_back(path);
//                 return;
//             }

//             for (int j = idx; j <= n; ++j) {

//                 if (path.size() + (n - j) + 1 < k) return;

//                 path.push_back(j);
//                 dfs(j + 1);
//                 path.pop_back();
//             }
//         };

//         dfs(1);

//         return ans;
//     }
// };

// 【思路 2 -- 写法 1】：选与不选子集型回溯 -- 组合 -- 剪枝
class Solution {
public:
    vector<vector<int>> combine(int n, int k) {
        
        vector<int> path;
        vector<vector<int>> ans;

        auto dfs = [&](this auto&& dfs, int idx, int k) -> void {

            if (k == 0) {
                ans.push_back(path);
                return;
            }

            // 当剩余位数不足时退出；
            if (idx > n) return;

            // 选
            path.push_back(idx);
            dfs(idx + 1, k - 1);
            path.pop_back();

            // 不选
            dfs(idx + 1, k);
        };

        dfs(1, k);

        return ans;
    }
};

class Solution {
public:
    vector<vector<int>> combine(int n, int k) {
        
        vector<int> path;
        vector<vector<int>> ans;

        auto dfs = [&](this auto&& dfs, int idx, int k) -> void {

        if (k == 0) {
            ans.push_back(path);
            return;
        }

        // 剩余不够
        if (idx + (k - 1) > n) return;

        // 当剩余位数刚好时，遍历加进来，和递归加进来的消耗差，还是不大的；
        // 剩余刚好
        if (n - idx + 1 == k) {
            for (int i = idx; i <= n; ++i)
                path.push_back(i);

            ans.push_back(path);

            for (int i = idx; i <= n; ++i)
                path.pop_back();
            return;
        }

        // 选
        path.push_back(idx);
        dfs(idx + 1, k - 1);
        path.pop_back();

        // 不选
        dfs(idx + 1, k);
    };

        dfs(1, k);

        return ans;
    }
};

int main() {
    Solution().combine(4, 2);
}