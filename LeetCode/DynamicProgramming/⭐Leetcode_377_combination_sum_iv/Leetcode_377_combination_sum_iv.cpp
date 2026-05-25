/**
 * @brief: Leetcode_377_组合总和_Ⅳ
 * @link: https://leetcode.cn/problems/combination-sum-iv/description/
 * @author: liangj.zhang
 * @date: 2/5/2026
 * 
 * @Difficulty: Medium
 * 
 * @Label: Dynamic Programming
 * 
 * @Retrospect(worthy 1 - 5): 4
 * 
 * @thoughts:
 *  + 【思路 1】：动态规划，递推填表
 *      刚做完 Leetcode_2466 过来的，这两题一模一样；
 *      ---
 *      以前的 <动态规划，状态压缩> 题目，能够压缩，是因为
 *          当前值的结果，只取决于固定数量的 前置位置的结果，加上此次变化，得到新的结果；
 *      这两次做的题（Leetcode_2466, 和当前这题），虽然结果还是没变，由前面几个值决定，但是数量已经产生不确定性；
 *          因此，思考内容上，多了内部循环的一小点变化；
 *      ---
 *      组合这题，我觉得回溯的思路，依旧能解的，
 *          不过相比 动态规划的 O(n^2) 复杂度，回溯指数级的时间复杂度，还是更慢；
 * 
 *      + 分析：
 *          + 时间复杂度：O(n * target)
 *          + 空间复杂度：O(n)
 *      + rank:
 *          + 时间效率：0 ms, 击败 100%
 *          + 空间效率：9.19 MB, 击败 22.88%
 */

#include <vector>
using std::vector;

class Solution {
public:
    int combinationSum4(vector<int>& nums, int target) {
        vector<unsigned int> rec(target + 1, 0);
        rec[0] = 1;
        int size = nums.size();
        for (int i = 1; i <= target; ++i) {
            for (int j = 0; j < size; ++j) {
                rec[i] += (i - nums[j] < 0) ? 0 : rec[i - nums[j]];
            }
        }

        return rec[target];
    }
};