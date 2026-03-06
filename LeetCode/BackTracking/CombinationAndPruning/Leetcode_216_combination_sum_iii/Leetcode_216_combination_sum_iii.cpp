/**
 * @brief: Leetcode_216_组合总和_III
 * @link: https://leetcode.cn/problems/combination-sum-iii/
 * @author: liangj.zhang
 * @date: 26/2/2026
 * 
 * @updated: 
 *  + 7/3/2026: add 【思路 2】：选与不选回溯 + 剪枝
 * 
 * @Difficulty: Medium
 * 
 * @Label: Backtracking & Pruning
 * 
 * @Retrospect(worthy 1 - 5): 3
 * 
 * @thoughts:
 *  + 【思路 1】：枚举回溯 + 剪枝
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
 * 
 *  + 【思路 2】：选与不选回溯 + 剪枝
 *      上面能够想到 回溯之前最开始前 k 个数之和 > n，后 k 个数之和时 < n 时是边界条件，已经很接近最完美剪枝了；
 *      把这个想法融进循环当中，就是最完美的剪枝；
 *      已经选择的 sum 和 + 剩余的范围内的 剩余k 的前k个数之和 = sum + (idx + 0) + (idx + 1) + ... (idx + k - 2) + (idx + k - 1)
 *                                                         = sum + k * idx + k * (k - 1) / 2
 *      已经选择的 sum 和 + 剩余的范围内的 剩余k 的后k个数之和 = sum + 9 + ... + (9 - (k - 2)) + (9 - (k - 1))
 *                                                         = sum + 9 * k - k * (k - 1) / 2 < n
 *      + 分析：
 *          + 时间复杂度：【思路 1】的分析是按完全剪枝分析的，但代码现在发现不是完美剪枝；参考【思路 1】的分析
 *          + 空间复杂度：O(k)
 *      + rank:
 *          + 时间效率：0 ms, 击败 100%
 *          + 空间效率：8.99 MB, 击败 8.29%
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

// 【思路 2】：选与不选回溯 + 剪枝
class Solution {
public:
    vector<vector<int>> combinationSum3(int k, int n) {

        vector<int> path;
        vector<vector<int>> ans;
        
        auto dfs = [&](this auto&& dfs, int idx, int k, int sum) -> void {

            if (k == 0) {
                if (sum == n) ans.push_back(path);
                return;
            }
            
            // 数量剪枝：剩余位数不够 剩余k 时，就直接 return
            if (9 - idx + 1 < k) return;
            // 和剪枝：
            // 1. 已选择的项和 sum + 剩余最小 k 个数和(剩余数的剩余前k个) > n，都比目标 n 大的话，后面就不用遍历了；
            // 2. 已选择的项和 sum + 剩余最大 k 个数和(剩余数的倒数后k个) < n, 都比目标 n 小的话，后面就不用遍历了；
            if (sum + k * idx + (k - 1) * k / 2 > n || sum + 9 * k - (k * k - k) / 2 < n) return;

            // 选
            path.push_back(idx);
            dfs(idx + 1, k - 1, sum + idx);
            path.pop_back();

            // 不选
            dfs(idx + 1, k, sum);
        };

        dfs(1, k, 0);

        return ans;
    }
};