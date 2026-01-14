/**
 * @brief: Leetcode_78_子集
 * @link: https://leetcode.cn/problems/subsets/submissions/691382290/
 * @author: liangj.zhang
 * @date: 14/1/2026
 * 
 * @Difficulty: Medium
 * 
 * @Label: BackTracking
 * 
 * @Retrospect(worthy 1 - 5): 5 【枚举选与不选的思想很优雅】
 * 
 * @thoughts:
 *  + 【思路 1】：回溯 -- 子集型问题
 *      子集型问题，就是解决完当前问题，子问题是同样的做法；（也即递归性）
 * 
 *      + 分析：
 *          + 时间复杂度：O(2^n * n), *n -> 拷贝每一个结果；
 *          + 空间复杂度：O(2^n * n) -> 算上结果空间
 *      + rank:
 *          + 时间效率：0 ms, 击败 100%
 *          + 空间效率：12.98 MB, 击败 5.03%  
 */
#include <vector>
using std::vector;

class Solution {
public:
    vector<vector<int>> subsets(vector<int>& nums) {
        
        int n = nums.size();
        vector<int> path;
        vector<vector<int>> ret;
        auto dfs = [&](this auto&&dfs, int i) -> void {

            if (i == n) {

                ret.emplace_back(vector<int>(path));
                return;
            }
            dfs(i + 1);     // 不选择，直接进入下一个节点

            path.push_back(nums[i]);
            dfs(i + 1);     // 选择，推入值，回退之后，推出值；
            path.pop_back();
        };

        dfs(0);

        return ret;
    }
};