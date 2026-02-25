/**
 * @brief: Leetcode_77_组合
 * @link: https://leetcode.cn/problems/combinations/description/
 * @author: liangj.zhang
 * @date: 25/2/2026
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
 */

#include <vector>
using std::vector;

class Solution {
public:
    vector<vector<int>> combine(int n, int k) {
        
        vector<int> path;
        vector<vector<int>> ans;

        auto dfs = [&](this auto&& dfs, int idx) -> void {

            if (path.size() == k) {

                ans.push_back(path);
                return;
            }

            for (int j = idx; j <= n; ++j) {

                if (path.size() + (n - j) + 1 < k) return;

                path.push_back(j);
                dfs(j + 1);
                path.pop_back();
            }
        };

        dfs(1);

        return ans;
    }
};