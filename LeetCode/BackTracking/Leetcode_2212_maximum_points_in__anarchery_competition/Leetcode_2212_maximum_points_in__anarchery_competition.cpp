/**
 * @brief: Leetcode_2212_射箭比赛中的最大得分
 * @link: https://leetcode.cn/problems/maximum-points-in-an-archery-competition/description/
 * @author: liangj.zhang
 * @date: 20/2/2026
 * 
 * @updated:
 *  + 21/2/2026:【思路 1 -- 写法 3】：回溯，得分与不得分
 * 
 * @Difficulty: Medium
 * 
 * @Label: BackTracking
 * 
 * @Retrospect(worthy 1 - 5): 3
 * 
 * @thoughts:
 *  + 【思路 1 -- 写法 1】：回溯，枚举，lambda dfs
 *      区分得分与不得分，每次枚举得分的情况；
 *      得分取比 Alice 的得分多 1 的最小值；选取完，剩下的统一加到 ans[0] 当中；
 *      
 *      + 分析：
 *          + 时间复杂度：O(2^n * n), 最坏就是每一次向下枚举，都会更新 ans，就会 * n；
 *          + 空间复杂度：O(n)
 *      + rank:
 *          + 时间效率：7 ms, 击败 83.73%
 *          + 空间效率：12.43 MB, 击败 60.84%
 * 
 *  + 【思路 1 -- 写法 2】：回溯，枚举，normal dfs
 *      同上
 *      + 分析：同上
 *      + rank: 
 *          + 时间效率：3 ms, 击败 92.17 %
 *          + 空间效率：12.34 MB, 击败 83.74%
 * 
 *  + 【思路 1 -- 写法 3】：回溯，得分与不得分
 *      同上
 *      + 分析：同上
 *      + rank: 
 *          + 时间效率：11 ms, 击败 66.07%
 *          + 空间效率：12.41 MB, 击败 67.26%
 */

#include <vector>
using std::vector;

// 【思路 1 -- 写法 1】：回溯，枚举，lambda dfs
class Solution {
public:
    vector<int> maximumBobPoints(int numArrows, vector<int>& aliceArrows) {
         
        // [0, 11] 环，得与不得分
        int maxScore = 0;
        vector<int> path(aliceArrows.size(), 0);
        vector<int> ans;

        auto dfs = [&](this auto &&dfs, int idx, int score, int leftArrows) -> void {

            if (maxScore < score) {

                ans = path;
                maxScore = score;
                // 都是按最小得分 ans[j] 的值的，如果有多余的，就统一放入 ans[0] 当中（多余的是可以任意放的）
                if (leftArrows > 0) ans[0] += leftArrows;
            }

            for (int j = idx; j < aliceArrows.size(); ++j) {

                // 可以得分
                if (leftArrows - (aliceArrows[j] + 1) >= 0) {
                    // 直接利用递归参数，避免手动回溯
                    path[j] = aliceArrows[j] + 1;
                    dfs(j + 1, score + j, leftArrows - (aliceArrows[j] + 1));
                    path[j] = 0;
                }
            }
        };

        dfs(0, 0, numArrows);

        return ans;
    }
};

// 【思路 1 -- 写法 2】：回溯，枚举，normal dfs
class Solution {
private:
    int maxScore;
    static vector<int> path;
    static vector<int> ans;

    void dfs(int idx, int score, int leftArrows, vector<int>& aliceArrows) {

        if (maxScore < score) {

            ans = path;
            maxScore = score;
            // 都是按最小得分 ans[j] 的值的，如果有多余的，就统一放入 ans[0] 当中（多余的是可以任意放的）
            if (leftArrows > 0) ans[0] += leftArrows;
        }

        // 这里不用给 return, if idx == aliceArrows.size()
        for (int j = idx; j < aliceArrows.size(); ++j) {

            // 可以得分
            if (leftArrows - (aliceArrows[j] + 1) >= 0) {
                // 直接利用递归参数，避免手动回溯
                path[j] = aliceArrows[j] + 1;
                dfs(j + 1, score + j, leftArrows - (aliceArrows[j] + 1), aliceArrows);
                path[j] = 0;
            }
        }
    }
public:
    Solution() : maxScore(0) {}

    vector<int> maximumBobPoints(int numArrows, vector<int>& aliceArrows) {
        
        path.assign(12, 0);
        ans.assign(12, 0);
        dfs(0, 0, numArrows, aliceArrows);

        return ans;
    }
};

vector<int> Solution::path;
vector<int> Solution::ans;

// 【思路 1 -- 写法 3】：回溯，得分与不得分
class Solution {
public:
    vector<int> maximumBobPoints(int numArrows, vector<int>& aliceArrows) {
        
        vector<int> path(aliceArrows.size(), 0);
        vector<int> ans;
        int maxScore = 0;

        auto dfs = [&](this auto&& dfs, int idx, int leftArrows, int score) -> void {

            if (idx == aliceArrows.size()) {

                if (maxScore < score) {

                    maxScore = score;
                    ans = path;
                    if (leftArrows > 0) ans[0] += leftArrows;
                }
                return;
            }

            // 不选
            dfs(idx + 1, leftArrows, score);
            // 可选
            if (int curNeed = aliceArrows[idx] + 1; leftArrows - curNeed >= 0) {

                path[idx] = curNeed;
                dfs(idx + 1, leftArrows - curNeed, score + idx);
                path[idx] = 0;
            }
        };

        dfs(0, numArrows, 0);

        return ans;
    }
};