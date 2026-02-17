/**
 * @brief: Leetcode_LCP_51_烹饪料理
 * @link: https://leetcode.cn/problems/UEcfPD/description/
 * @author: liangj.zhang
 * @date: 1/2/2026
 * 
 * @updated: 
 *  + 15/2/2026: add【思路 1】：回溯，枚举 DFS
 *  + 17/2/2026: add【思路 1 -- 写法 2】：回溯，选与不选 DFS
 * 
 * @Difficulty: Easy
 * 
 * @Label: DFS & BackTracking
 * 
 * @Retrospect(worthy 1 - 5): 4
 * 
 * @thoughts:
 *  + 【思路 1】：回溯，枚举 DFS
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
 * 
 *  + 【思路 2】：位掩码来枚举
 *      mask = 10110 -> 表示选了第1、2、4个菜
 *      + 分析：
 *          + 时间复杂度：O(5 * 2^n)，同上面是一样的；
 *          + 空间复杂度：O(n) -> 临时空间
 *      + rank:
 *          + 时间效率：15 ms, 击败 17.25%
 *          + 空间效率：24.02 MB, 击败 34.51%
 * 
 * + 【思路 1 -- 写法 2】：回溯，选与不选 DFS
 *      理解起来比枚举的要好理解一点
 *      + 分析：同 【思路 1】
 *      + rank:
 *          + 时间效率：0 ms, 击败 100%
 *          + 空间效率：22.82 MB, 击败 80.36%
 */

#include <vector>
using std::vector;

//【思路 1】：回溯，枚举 DFS
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

// 【思路 2】：位掩码来枚举
class Solution {
public:
    int perfectMenu(vector<int>& materials, vector<vector<int>>& cookbooks, vector<vector<int>>& attribute, int limit) {

        int n = cookbooks.size();
        int maxDelicious = -1;

        for (int mask = 0; mask < (1 << n); ++mask) {

            vector<int> need(materials.size(), 0);
            int full = 0;
            int delicious = 0;
            for (int j = 0; j < n; ++j) {   // j -> 第几道菜

                if (mask & (1 << j)) {

                    // 求 need
                    for (int k = 0; k < materials.size(); ++k) {
                        need[k] += cookbooks[j][k];
                    }
                    // 求最新的 full / delicious
                    full += attribute[j][1];
                    delicious += attribute[j][0];
                }
            }
            
            bool ok = true;
            // materials 是否还够用, full >= limit ?
            for (int k = 0; k < materials.size(); ++k) {
                
                if (need[k] > materials[k]){
                    
                    ok = false;
                    break;
                }
            }

            // delicious > max?
            if (ok && full >= limit) {
                if (delicious > maxDelicious)
                    maxDelicious = delicious;
            }

        }

        return maxDelicious;
    }
};

// 【思路 1 -- 写法 2】：回溯，选与不选
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

            if (i == n) {
                
                if (full >= limit && delicious > maxDelicious) {
                    maxDelicious = delicious;
                }
                return;
            }

            dfs(i + 1, delicious, full);

            if (possible(materials, cookbooks[i])) {

                for (int k = 0; k < materials.size(); ++k)
                    materials[k] -= cookbooks[i][k];
                
                dfs(i + 1, delicious + attribute[i][0], full + attribute[i][1]);
                
                // backtracking
                for (int k = 0; k < materials.size(); ++k)
                    materials[k] += cookbooks[i][k];
            }
        };

        dfs(0, 0, 0);

        return maxDelicious;
    }
};

int main() {

    vector<int> materials = {3,2,4,1,2};
    vector<vector<int>> cookbooks = {{1,1,0,1,2}, {2,1,4,0,0}, {3,2,4,1,0}};
    vector<vector<int>> attribute = {{3,2}, {2,4}, {7,6}};
    int limit = 5;

    Solution().perfectMenu(materials, cookbooks, attribute, limit);
}