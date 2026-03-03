/**
 * @brief: Leetcode_39_组合总和
 * @link: https://leetcode.cn/problems/combination-sum/description/
 * @author: liangj.zhang
 * @date: 2/3/2026
 * 
 * @updated:
 *  + 3/3/2026: add 【思路 2】：选与不选回溯 -- 剪枝
 * 
 * @Difficulty: Medium
 * 
 * @Label: Backtracking & 剪枝 & dfs
 * 
 * @Retrospect(worthy 1 - 5): 3 + 5(classic)
 * 
 * @thoughts:
 *  + 【思路 1】：枚举回溯 -- 剪枝
 *      一开始就不自觉的，认为先排序一遍好方便后面剪枝；
 *      我按升序排列；O(nlogn)
 *      这时候再按顺序回溯，当出现第一个大于 target 的位置，
 *      此处的 for (size_t j = idx; j < candidates.size(); ++j) 后面都不用遍历了，以及每个位置后面的回溯，直接 return；
 *     
 *      + 分析：
 *          + 时间复杂度：n-> candidates.size(); T->target; min = candidates[0](排序后的)
 *              + 排序 -> O(nlogn)
 *              + 递归的最大深度 -> O(T/min) -> 假设为 O(d), 最坏的情况(min = 1)，d = T
 *              + 每层的分支数：每层最多有 n 种选择（理论上），但实际上随着 sum 增加，可选数量会减少；
 *              + 回溯的最坏情况：O(n^d) = O(n^(T/min))，没有重复值，越到后面可选择越少；
 *              + 总共：O(nlogn) + O(n^(T/min))
 *          + 空间复杂度：
 *              + 递归栈深度：O(T/min)
 *              + path 空间：O(T/min)
 *              + 结果：O(解的总数 * 平均长度)
 *      + rank:
 *          + 时间效率：0 ms, 击败 100%
 *          + 空间效率：13.83 MB, 击败 89.04%
 * 
 * + 【思路 2】：选与不选回溯 -- 剪枝
 *      模板过程没什么说的，写了那么多回溯了；
 *      值得提的是，不选的时候，让 dfs 能够选到下一个的可能：dfs(j + 1, sum); idx 向后移一位
 *      主要来分析：
 *          1. if (idx == candidates.size() || target - sum < candidates[idx]) return;
 *          2. if (idx == candidates.size() || sum > target) return;
 *      在排完序，面对所有组合的时候，上面两种剪枝的方式，【1】的效果更有效；
 *      原来以为，【2】只是在比 【1】dfs 的时候，多一层而已(idx 的下一层再选中就 > target)；以及以 idx 为起始的循环，剩余部分也都多一层就结束了；
 *      但并非这样，不选的时候是：dfs(j + 1, sum);
 *      进入到多的一层 idx + 1 后退出，回退到 j = idx 为起始的循环，下一步是 不选 的步骤，
 *          对于后续的 不选，这样的操作会 dfs 到底；
 *      不如在 dfs 到 j = idx 为起始时，加上 当前值，> target 就直接 return；断绝拖拉到下层，递归次数少剪枝了一半；
 *      ------------
 *      回过头来再看看 枚举回溯中，修改成循环外部 sum > target 剪枝条件，
 *          1. 原来的完全剪枝，循环内：if (sum + candidates[j] <= target) {
 *          2. 想尝试的剪枝，循环外：if (sum > target) return;
 *      细细想想【2】 j = idx 为起始开始，下一步再加上就会 > target，
 *      选举到 idx + 1 时，它也会进入 dfs，下一步再退出回来；
 *      ...
 *      直到最后一个都是如此，进入下一层都会 > target，在退出来；没有递归到底的情形；
 *      总结：
 *          所以，枚举回溯，使用循环外 if(sum > target)，并不会增加很多递归深度；
 *      每次边界多一层递归（【2】），应该是比每层都会有的 if 判断多的 + candidates[j] （【1】）的消耗要多一些的；
 * 
 *      + 分析：
 *          + 时间复杂度：完全剪枝，复杂度同枚举回溯完全剪枝一样 O(nlogn) + O(n^(T/min))
 *          + 空间复杂度：递归树的高度 ≈ target / min(candidates)；每个节点最多有 N 个分支；
 *              + 递归栈空间：O(T/M)
 *              + 路径 path 存储空间：O(T/M)
 *              + 结果存储空间：O(结果数量 × 平均路径长度)
 *      + rank:
 *          + 时间效率：0 ms, 击败 100%
 *          + 空间效率：13.70 MB, 击败 98.21%
 */

#include <vector>
#include <algorithm>
using std::sort;
using std::vector;

// 【思路 1】：枚举回溯 -- 剪枝
class Solution {
public:
    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        
        vector<int> path;
        vector<vector<int>> ans;

        sort(candidates.begin(), candidates.end());

        auto dfs = [&](this auto&& dfs, int idx, int sum) -> void {

            if (sum == target) {

                ans.push_back(path);
                return;
            }

            for (size_t j = idx; j < candidates.size(); ++j) {

                if (sum + candidates[j] <= target) {

                    path.push_back(candidates[j]);
                    dfs(j, sum + candidates[j]);
                    path.pop_back();
                }
                else return;
            }
        };

        dfs(0, 0);

        return ans;
    }
};

// 【思路 2】：选与不选回溯 -- 剪枝
class Solution {
public:
    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        
        vector<int> path;
        vector<vector<int>> ans;

        std::sort(candidates.begin(), candidates.end());

        auto dfs = [&](this auto&& dfs, int idx, int sum) -> void {

            if (sum == target) {
                
                ans.push_back(path);
                return;
            }

            //if (sum > target || idx == candidates.size()) return; // 本以为只是差了一层深度；其实不是，不选的那个分支，会递归到底；
            if (idx == candidates.size() || target - sum < candidates[idx]) return;

            path.push_back(candidates[idx]);
            dfs(idx, sum + candidates[idx]);
            path.pop_back();

            dfs(idx + 1, sum);
        };

        dfs(0, 0);

        return ans;
    }
};