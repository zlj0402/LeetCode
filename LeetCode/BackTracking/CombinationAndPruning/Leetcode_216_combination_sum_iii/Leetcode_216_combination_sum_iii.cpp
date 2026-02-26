/**
 * @brief: Leetcode_216_组合总和_III
 * @link: 组合总和 III
 * @author: liangj.zhang
 * @date: 26/2/2026
 * 
 * @Difficulty: Medium
 * 
 * @Label: Backtracking & Pruning
 * 
 * @Retrospect(worthy 1 - 5): 3
 * 
 * @thoughts:
 *  + 【思路 1】：回溯 + 剪枝
 *      正常的回溯已经没问题了吧
 *      剪枝1：正常能有结果的条是，前 k 个数之和是 <= n 的，且 后 k 个数之和是 >= n 的
 *              即 1 + ... + k <= n <= [(9 - (k - 1)] + ... + {9 - [k - (k - 1)]} + [9 - (k - k)]
 *              高斯公式：(k + 1) * k / 2 <= n <= 9 *k - (k - 1) * k / 2
 *              反过来，当 (k + 1) * k / 2 > n 时，或者 9 *k - (k - 1) * k / 2 < n 时，是一定没有结果的
 *      剪枝2：当前 path 当中的和已经 > n，后续是不用再关心了，全部跳过
 *      剪枝3：当 path.size() + 9 - j + 1 -> 就算能遍历到最后的个数（最后能放到 path 中的个数） < k 的话，也直接结束
 * 
 *      + 分析：
 *          + 时间复杂度：O(C(n, k) * k)
 *          + 空间复杂度：O(k)
 *      + rank:
 *          + 时间效率：0 ms, 击败 100%
 *          + 空间效率：8.49 MB, 击败 95.41%
 */

#include <vector>
using std::vector;

// 正常回溯
class Solution {
public:
    vector<vector<int>> combinationSum3(int k, int n) {
        
        vector<int> path;
        vector<vector<int>> ans;

        auto dfs = [&](this auto&& dfs, int idx, int k, int curSum) -> void {

            if (k == 0) {
                if (curSum == n) ans.push_back(path);
                return;
            }

            for (int j = idx; j <= 9; ++j) {
                
                path.push_back(j);
                dfs(j + 1, k - 1, curSum + j);
                path.pop_back();
            }
        };

        dfs(1, k, 0);

        return ans;
    }
};

// 【思路 1】：回溯 + 剪枝
// 从小到大 dfs 时，
// 当出现 > k 的情况，不仅 dfs 不用 dfs 下去，当层的遍历也可以结束了；
class Solution {
public:
    vector<vector<int>> combinationSum3(int k, int n) {
        
        vector<int> path;
        vector<vector<int>> ans;

        auto dfs = [&](this auto&& dfs, int idx, int k, int curSum) -> void {

            if (k == 0) {
                if (curSum == n) ans.push_back(path);
                return;
            }

            for (int j = idx; j <= 9; ++j) {
                
                if (curSum + j > n) return; // 剪枝 2：和已经大于目标 n; 放在循环内更合适，放在外的话是 if (curSum > n)，似乎不能阻止上一层 iter

                if (path.size() + 9 - j + 1 < k) return;    // 剪枝 3：就算 dfs 到最后，剩余的个数不够，这里就结束

                path.push_back(j);
                dfs(j + 1, k - 1, curSum + j);
                path.pop_back();
            }
        };

        if ((k + 1) * k > 2 * n || (19 * k - k * k) < 2 * n) return {}; // 剪枝 1：边界条件都无法满足
        dfs(1, k, 0);

        return ans;
    }
};