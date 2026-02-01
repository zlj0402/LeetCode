/**
 * @brief: Leetcode_LCP_51_烹饪料理
 * @link: https://leetcode.cn/problems/UEcfPD/description/
 * @author: liangj.zhang
 * @date: 1/2/2026
 * 
 * @Difficulty: Easy
 * 
 * @Label: DFS & BackTracking
 * 
 * @Retrospect(worthy 1 - 5): 4
 * 
 * @thoughts:
 *  + 【思路 1】：DFS
 *      刚看完题目，感觉这题条件有点多，写起来倒还行，反倒一次性通过；
 *      BackTracking 该干嘛的地方就干嘛，
 *      该递归下一个的时候，就递归下一个，该扣除状态值时扣除状态值，该回溯的时候回溯；就这样先把伪代码写好，然后对号入座每一步；
 *      
 *      + 分析：
 *          + 时间复杂度：O(5 * 2^n), n -> 菜谱的个数 => O(2^n)
 *          + 空间复杂度：O(n)
 *      + rank:
 *          + 时间效率：4 ms, 击败 83.58%
 *          + 空间效率：22.77 MB, 击败 86.57%
 */

#include <vector>
using std::vector;

class Solution {
private:
    bool possible(vector<int>& mat, vector<int>& cookbook) {

        for (int i = 0; i < mat.size(); ++i) {

            if (mat[i] - cookbook[i] < 0)
                return false;
        }
        return true;
    }
public:
    int perfectMenu(vector<int>& materials, vector<vector<int>>& cookbooks, vector<vector<int>>& attribute, int limit) {

        int n = cookbooks.size();
        int maxDelicious = -1;

        auto dfs = [&](this auto&& dfs, int i, int delicious, int full) -> void {

            if (full >= limit && delicious > maxDelicious) {
                maxDelicious = delicious;
            }

            for (int j = i; j < n; ++j) {

                if (possible(materials, cookbooks[j])) {

                    for (int k = 0; k < materials.size(); ++k)
                        materials[k] -= cookbooks[j][k];
                    
                    dfs(j + 1, delicious + attribute[j][0], full + attribute[j][1]);
                    
                    // backtracking
                    for (int k = 0; k < materials.size(); ++k)
                        materials[k] += cookbooks[j][k];
                }

            }
        };

        dfs(0, 0, 0);

        return maxDelicious;
    }
};