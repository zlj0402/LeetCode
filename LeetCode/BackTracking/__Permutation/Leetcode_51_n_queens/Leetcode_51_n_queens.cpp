/**
 * @brief: Leetcode_51_N_皇后
 * @link: https://leetcode.cn/problems/n-queens/description/
 * @author: liangj.zhang
 * @date: 14/3/2026
 * 
 * @updated:
 *  + 28/3/2026: add
 * 
 * @Difficulty: Hard
 * 
 * @Label: Backtracking
 * 
 * @Retrospect(worthy 1 - 5): 5
 * 
 * @thoughts: 
 *  + 【思路 2】：回溯
 *      python 写得第一版，是通过存储每一行坐标，然后跟当前行的坐标相减，求斜率的绝对值，如果是 1，则说明这个位置不能选；
 *      列都是通过集合来排除；
 * 
 *      这里斜线的比较是通过，坐标特性：
 *          左斜线：y - x 是恒定的，同一斜线上；
 *          有些先：y + x 是恒定的；
 *      + 分析：
 *          + 时间复杂度：O(n! * n) -> 后面的 n 是copy的那份，当然拷贝的次数，肯定是远低于 n!
 *          + 空间复杂度：递归 O(n)， 结果拷贝：O(n^2), 辅助结构 O(n)，结果集 O(k * n^2), k 是 结果个数
 *      + rank:
 *          + 时间效率：12 ms, 击败 18.36%
 *          + 空间效率：13.86 MB, 击败 12.37%
 *  + 【思路 1】：回溯
 *      同 python 写的那一版，存储坐标，然后
 *          1. 是否在同一列
 *          2. 是否在同一斜线：abs(path[i] - col) == abs(n - i)
 *      + 分析: 完全同上
 *      + rank:
 *          + 时间效率：3 ms, 击败 81.84%
 *          + 空间效率：12.39 MB, 击败 20.78%
 */

#include <vector>
#include <string>
using std::vector;
using std::string;

#include <unordered_set>
using std::unordered_set;
#define us unordered_set

class Solution {
public:
    vector<vector<string>> solveNQueens(int n) {
        us<int> cols;
        us<int> leftUp;
        us<int> rightUp;

        vector<int> path;
        vector<vector<string>> ans;
        auto dfs = [&](this auto&& dfs, int row) -> void {

            if (row == n) {
                vector<string> tmp;
                for (int i = 0; i < n; ++i) {
                    vector<char> r(n, '.');
                    r[path[i]] = 'Q';
                    tmp.emplace_back(string(r.begin(), r.end()));
                }
                ans.emplace_back(tmp);
                return;
            }

            for (int col = 0; col < n; ++col) {
                // col 没选过 && 左斜不会冲突 && 右斜不会冲突
                if (int _sub = col - row, _sum = col + row;
                    !cols.contains(col) && !leftUp.contains(_sub) && !rightUp.contains(_sum)) {
                    cols.insert(col);
                    leftUp.insert(_sub);
                    rightUp.insert(_sum);
                    path.push_back(col);

                    dfs(row + 1);

                    path.pop_back();
                    rightUp.erase(_sum);
                    leftUp.erase(_sub);
                    cols.erase(col);
                }
            }
        };

        dfs(0);

        return ans;
    }
};

class Solution {
private:
    vector<int> path;
    vector<vector<string>> ans;
    bool isConflict(int col) {
        int n = path.size();
        for (int i = 0; i < n; ++i) {
            // (i, path[i]) - (n, col)
            if (path[i] == col || abs(path[i] - col) == abs(n - i))
                return true;
        }
        return false;
    }
public:
    vector<vector<string>> solveNQueens(int n) {
        path.clear();
        ans.clear();

        auto dfs = [&](this auto&& dfs, int row) -> void {

            if (row == n) {
                vector<string> tmp;
                for (int i = 0; i < n; ++i) {
                    vector<char> r(n, '.');
                    r[path[i]] = 'Q';
                    tmp.emplace_back(std::move(string(r.begin(), r.end())));
                }
                ans.emplace_back(std::move(tmp));
                return;
            }

            for (int col = 0; col < n; ++col) {
                // col 没选过 && 左斜不会冲突 && 右斜不会冲突
                if (!isConflict(col)) {
                    path.push_back(col);

                    dfs(row + 1);

                    path.pop_back();
                }
            }
        };

        dfs(0);

        return ans;
    }
};