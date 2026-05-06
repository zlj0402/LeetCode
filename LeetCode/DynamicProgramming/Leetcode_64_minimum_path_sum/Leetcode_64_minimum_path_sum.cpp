/**
 * @brief: Leetcode_64_最小路径和
 * @link: https://leetcode.cn/problems/minimum-path-sum/description/
 * @author: liangj.zhang
 * @date: 6/2/2026
 * 
 * @Difficulty: Medium
 * 
 * @Label: Dynamic 
 * 
 * @Retrospect(worthy 1 - 5): 5
 * 
 * @thoughts:
 *  + 【思路 1】：回溯 + dfs
 *      第一反应是这个做法，
 *      最开始的一版，还是带上 visit 数组的，想到它只能要么往下，要么横着，其实它没有办法走重复节点的，索性将 visit 也删了，没错，前两个 case 也能得到结果；
 *      但是，这种方式只能到第 23 个 case 就超时了；
 *      dfs 走过的路径可能太多了；
 * 
 *  + 【思路 2】：也是纯递归写法
 *      跟 【思路 1】，还是有些不一样的，是你过来的顺序；
 *      思路 1 -- 如果说是，自上而下，
 *      那么 思路 2 -- 就是自下而上；
 *          而且，更专注于当前一次 dfs 做的内容；
 *      ---
 *      也是纯递归，自然也超时了；
 *  + 【思路 3】：dfs + 记忆化搜索
 *     这一步倒像是第一次写 DP 题，从递归开始越来越优的写法；
 *      + 分析：
 *          + 时间复杂度：O(mn)
 *          + 空间复杂度：O(mn)
 *      + rank:
 *          + 时间效率：3 ms, 击败 30.21%
 *          + 空间效率：15.43 MB, 击败 71.77%
 */

#include <vector>
#include <iostream>
using std::vector;

#define MAXLEN 201

class Solution {
private:
    static int Tx[2];
    static int Ty[2];
    static vector<vector<int>> map;
public:
    int minPathSum(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();

        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                map[i][j] = 0;
            }
        }

        auto dfs = [&](this auto&& dfs, int x, int y) -> int {
            int x1 = x + Tx[0];
            int y1 = y + Ty[0];
            int x2 = x + Tx[1];
            int y2 = y + Ty[1];

            int ret = -1;

            if (x1 >= 0 && y1 >= 0 && x2 >= 0 && y2 >= 0) {
                ret = std::min(map[x1][y1] != 0 ? map[x1][y1] : dfs(x1, y1), 
                                map[x2][y2] != 0 ? map[x2][y2] : dfs(x2, y2));
            }
            else if (x1 >= 0 && y1 >= 0) {
                ret = map[x1][y1] != 0 ? map[x1][y1] : dfs(x1, y1);
            }
            else if (x2 >= 0 && y2 >= 0) {
                ret = map[x2][y2] != 0 ? map[x2][y2] : dfs(x2, y2);
            }
            else {
                ret = 0;
            }

            return map[x][y] = ret + grid[x][y];
        };

        dfs(m - 1, n - 1);

        return map[m - 1][n - 1];
    }
};
vector<vector<int>> Solution::map(MAXLEN, vector<int>(MAXLEN));
int Solution::Tx[] = {0, -1};
int Solution::Ty[] = {-1, 0};

// 2
// class Solution {
// private:
//     static int Tx[2];
//     static int Ty[2];
// public:
//     int minPathSum(vector<vector<int>>& grid) {
//         int m = grid.size();
//         int n = grid[0].size();

//         auto dfs = [&](this auto&& dfs, int x, int y) -> int {
//             // if (x < 0 || y < 0) {
//             //     return 0;
//             // }
//             int x1 = x + Tx[0];
//             int y1 = y + Ty[0];
//             int x2 = x + Tx[1];
//             int y2 = y + Ty[1];

//             if (x1 >= 0 && y1 >= 0 && x2 >= 0 && y2 >= 0) {
//                 return std::min((dfs(x1, y1) + grid[x1][y1]), (dfs(x2, y2) + grid[x2][y2]));
//             }
//             else if (x1 >= 0 && y1 >= 0) {
//                 return dfs(x1, y1) + grid[x1][y1];
//             }
//             else if (x2 >= 0 && y2 >= 0) {
//                 return dfs(x2, y2) + grid[x2][y2];
//             }
//             else {
//                 return 0;
//             }
//         };

//         return dfs(m - 1, n - 1) + grid[m - 1][n - 1];
//     }
// };
// int Solution::Tx[] = {0, -1};
// int Solution::Ty[] = {-1, 0};

//【思路 1】：回溯 + dfs
// class Solution {
// private:
//     int minCost = __INT_MAX__;
//     static int Tx[];
//     static int Ty[];
// public:
//     int minPathSum(vector<vector<int>>& grid) {
//         int m = grid.size();
//         int n = grid[0].size();
//         minCost = __INT_MAX__;

//         auto dfs = [&](this auto&& dfs, int x, int y, int cost) {
//             if (x == m - 1 && y == n - 1) {
//                 if (cost < minCost) {
//                     minCost = cost;
//                 }
//                 return;
//             }

//             for (int i = 0; i < 2; ++i) {
//                 int ax = x + Tx[i];
//                 int ay = y + Ty[i];
//                 if (ax < m && ay < n) {
//                     dfs(ax, ay, cost + grid[ax][ay]);
//                 }
//             }
//         };

//         dfs(0, 0, grid[0][0]);

//         return minCost;
//     }
// };

// int Solution::Tx[] = {0, 1};
// int Solution::Ty[] = {1, 0};

int main() {
    vector<vector<int>> grid{{1,3,1}, {1,5,1}, {4,2,1}};
    std::cout << Solution().minPathSum(grid) << std::endl;
}