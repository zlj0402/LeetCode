/*
 * @brief: Leetcode_46_全排列
 * @link: https://leetcode.cn/problems/permutations/description/
 * @author: liangj.zhang
 * @date: 11/3/2026
 * 
 * @updated:
 *  + 11/2/2026: add Python version 【思路 1】：枚举回溯 -- 排列
 *  + 17/3/2026: add C++ version 【思路 1】：枚举回溯 -- 排列
 *
 * @Difficulty: Medium
 *
 * @Label: Backtracking & Permutation
 *
 * @Retrospect(worthy 1 - 5): 4, classic
 *
 * @thoughts:
 *   + 【思路 1】：枚举回溯 -- 排列
 *     >>> path[idx] 从剩余可选数中，选择一个数填入 <<<
 *     一个是 path，另一个是要维护一个我们知道，还没有选择数的集合
 *     （至于这个集合的实现，是一个真的集合结构，还是采用 array 和 标志位 array，异或其他方式）
 *     ----
 *     这是写的第一个排列型回溯，有一个感受记录一下（也在下面的当中）：
 *     组合型回溯，我们是在 dfs 外的固定数组中，选择某个数 nums[idx]，idx 是 dfs 的参数；
 *     排列型回溯，我们是在 剩余集合中选择一个数，dfs 时的 idx 是 path 当中要填入的下标；
 *     -- 就是有这么个不同；
 *
 *     + 分析：
 *         + 时间复杂度：排列的可能是 n!，所以：O(n * n!)
 *         + 空间复杂度：不算上结果，path -> O(n), dfs -> O(n), summary: O(n)
 *
 *     + rank:
 *         + 空间效率：0 ms, 击败 100%
 *         + 时间效率：10.32 MB, 击败 91.46%
 */

#include <vector>
using std::vector;

class Solution {
public:
    vector<vector<int>> permute(vector<int>& nums) {
        
        vector<bool> flags(nums.size(), false);
        vector<int> path(nums.size(), 0);
        vector<vector<int>> ans;
        auto dfs = [&](this auto&& dfs, int idx) -> void {

            if (idx == nums.size()) {
                ans.push_back(path);
                return;
            }

            for (int i = 0; i < nums.size(); ++i) {
                if (flags[i] == false) {
                    flags[i] = true;
                    path[idx] = nums[i];
                    dfs(idx + 1);
                    path[idx] = 0;
                    flags[i] = false;
                }
            }
        };

        dfs(0);

        return ans;
    }
};