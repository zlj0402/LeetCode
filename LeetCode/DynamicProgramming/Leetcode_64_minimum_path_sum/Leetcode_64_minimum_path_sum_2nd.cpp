/**
 * @brief: Leetcode_64_最小路径和_2nd
 * @link: https://leetcode.cn/problems/minimum-path-sum/description/
 * @author: liangj.zhang
 * @date: 2026/09/19
 * 
 * @updated:
 *  + 2026/09/20: add 【思路 2 -- 写法 1】：记忆化搜索 -- 先上再左，【思路 2 -- 写法 2】：记忆化搜索 -- 先左再上
 *  + 2026/09/21: add 【思路 3】：滚动数组
 * 
 * @Difficulty: Medium
 * 
 * @Label: DP
 * 
 * @Retrospect(worthy 1 - 5): 4
 * 
 * @thoughts:
 *  + 【思路 1】：动态规划
 *  即使重新写这道题，乍一看这道题的前一分钟，还是挺无助的，这怎么写；
 *  但知道这道题是以 DP 为方法为解，迅速又回到 DP 的核心法门，f(n) = Relation(f(n1), f(n2))
 *      即，当前值，由前一步位置的值决定，
 *  那么，我在一个位置 (i, j)，我只要找到前一步位置的值，比较得到最小值，加到自身就可以了；
 *      一个合法的位置都没有，即没有前面的位置可以过来，最小值为 0；
 *      有一个合法的，那就取那个值；
 *      有两个合法的，那就取两者之间最小值；
 *  ---
 *  极限最小的最大值：路径数最多是 200 + 199，就算 400，每个值最大是 200，那么简单的最小最大值就是 400 * 200（真正的是 199 * 200 + 1）
 *  + 分析：
 *      + 时间复杂度：O(m * n)
 *      + 空间复杂度：O(1)，可以在原数组中直接修改
 *  + rank:
 *      + 时间效率：0 ms, 击败 100%
 *      + 空间效率：15.07 MB, 击败 89.26%
 * 
 * ===
 *  不知道这题递归能不能解，但肯定是没有上面这个方式简单；
 * 
 *  + 【思路 2 -- 写法 1】：记忆化搜索 -- 先上再左，
 *      递归能解，从最右下方，递到最左上方；归的时候，是完全相反的过程；直到一个没有递过的分支，再到底；（图纸上画画就能理解）
 *      + 分析：
 *          + 时间复杂度：O(mn) 状态数
 *          + 空间复杂度：O(mn)备份的rec + O(m + n)递归 == O(mn)
 *      + rank:
 *          + 时间效率：0 ms, 击败 100%
 *          + 空间效率：15.98 MB, 击败 52.58%
 * 
 *  + 【思路 2 -- 写法 2】：记忆化搜索 -- 先左再上
 *      同 写法1 差不多
 *      + 分析：同上
 *      + rank:
 *          + 时间效率：3 ms, 击败 29.31%
 *          + 空间效率：16.07 MB, 击败 33.84%
 * 
 *  + 【思路 3】：滚动数组
 *      只利用持久的一行，（当然也可以额外用一个数组）
 *          如果是申请全部空间，当遍历到某一行，除了前一行有用，再前面的行已经失去了作用。
 *      这就是滚动数组的思想；
 *      + 分析：
 *          + 时间复杂度：O(mn)
 *          + 空间复杂度：O(1)
 *      + rank:
 *          + 时间效率：0 ms, 击败 100%
 *          + 空间效率：14.94 MB, 击败 96.40%
 */

#include <vector>
#include <iostream>
using std::vector;

// 【思路 3】：滚动数组
class Solution {
public:
    int minPathSum(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();

        // i = 0
        for (int j = 1; j < n; ++j) {
            grid[0][j] += grid[0][j - 1];
        }
        for (int i = 1; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (j > 0) {
                    grid[0][j] = std::min(grid[0][j], grid[0][j - 1]) + grid[i][j];
                }
                else {
                    grid[0][j] += grid[i][j];
                }
            }
        }

        return grid[0][n-1];
    }
};

// 【思路 2 -- 写法 1】：记忆化搜索 -- 先上再左，
class Solution {
private:
    static constexpr int MAXVAL = 80000;
public:
    int minPathSum(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();
        vector<vector<int>> rec(m, vector<int>(n, -1));

        auto dfs = [&](this auto&& dfs, int i, int j) {
            if (i < 0 || j < 0) return MAXVAL;
            if (rec[i][j] != -1) return rec[i][j];

            int min_ = std::min(dfs(i - 1, j), dfs(i, j - 1));

            return rec[i][j] = grid[i][j] + ((min_ == MAXVAL) ? 0 : min_);
        } (m - 1, n - 1);

        return rec[m - 1][n - 1];
    }
};

// 【思路 2 -- 写法 2】：记忆化搜索 -- 先左再上
class Solution {
private:
    static constexpr int MAXVAL = 80000;
public:
    int minPathSum(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();
        vector<vector<int>> rec(m, vector<int>(n, -1));

        auto dfs = [&](this auto&& dfs, int i, int j) {
            if (i < 0 || j < 0) return MAXVAL;
            if (rec[i][j] != -1) return rec[i][j];

            int min_ = std::min(dfs(i, j - 1), dfs(i - 1, j));

            return rec[i][j] = grid[i][j] + ((min_ == MAXVAL) ? 0 : min_);
        } (m - 1, n - 1);

        return rec[m - 1][n - 1];
    }
};

// class Solution {
// private:
//     static constexpr int MAXVAL = 80000; // 原来错误的写法： MAXVAL = 201; 错误，因为前两个位置的值也是叠加上来的
// public:
//     int minPathSum(vector<vector<int>>& grid) {
//         int m = grid[0].size();
//         int n = grid.size();
//         for (int i = 0; i < n; ++i) {
//             for (int j = 0; j < m; ++j) {
//                 int val1 = MAXVAL, val2 = MAXVAL;
//                 if (i - 1 >= 0) val1 = grid[i - 1][j]; // 上一行的位置
//                 if (j - 1 >= 0) val2 = grid[i][j - 1]; // 上一列的位置
//                 int min_ = std::min(val1, val2);
//                 grid[i][j] += min_ == MAXVAL ? 0 : min_;
//             }
//         }
//         return grid[n-1][m-1];
//     }
// };

int main() {
    vector<vector<int>> grid = {{1,3,1}, {1,5,1}, {4,2,1}};
    std::cout << Solution().minPathSum(grid) << std::endl;
}