/**
 * @brief: Leetcode_64_最小路径和
 * @link: https://leetcode.cn/problems/minimum-path-sum/description/
 * @author: liangj.zhang
 * @date: 6/5/2026
 * 
 * @updated:
 *  + 7/5/2026: add 【思路 4】：DP 递推填表、【思路 4 -- 写法 2】：递推填表
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
 *  + 【思路 4】：DP 递推填表
 *      这一步就是递推，像爬楼梯的递推写法一样，每个位置写入递推到这个位置的结果；
 *      这里的公式（是看了灵神的题解，又恍然大悟了），
 *          可以思考一下最后一个位置 grid[m-1][n-1],
 *          走向 grid[m-1][n-1]，一定要么是从 grid[m-2][n-1]，要么是从 grid[m-1][n-2] 过来的，
 *          如果有了 grid[m-2][n-1] 和 grid[m-1][n-2] 的递推结果，我们就能得到 grid[m-1][n-1] 位置的递推结果；
 *      递推公式：f(i, j) = f(i-1, j) + f(i, j-1)
 *          >>> 注意边界 <<<：比如第一行的递推，超过边界，说明肯定是不会从界外(界线上方)走过来的，这种情况直接忽略，取从左边过来的递推结果；
 *                  如果两个来向的位置都超出边界（即出发点），递推基值为 0，再加上当前位置的 grid[0][0]
 *      其次是想到，>>> 怎样遍历，在求得一个位置的递推值时，他的来向的两个位置，都已经求过递推值了；<<<
 *          横着遍历，后续位置的递推也横着遍历，那么头脑中，可以相到，这是可以实现；
 *          也可以竖着遍历，那么后续位置的递推也要竖着遍历；
 *      + 分析：
 *          + 时间复杂度：O(mn)
 *          + 空间复杂度：O(mn)
 *      + rank:
 *          + 时间效率：0 ms, 击败 100%
 *          + 空间效率：15.27 MB, 击败 74.69%
 *  + 【思路 4 -- 写法 2】：递推填表
 *      在考虑上面 >>> 怎样遍历，在求得一个位置的递推值时，他的来向的两个位置，都已经求过递推值了；<<< 这个问题时，
 *      发现，一个位置的 grid[][] 值，在求得递推值之后，就不会再次使用这个位置的 grid[][] 值，那么我可以直接在 grid 中将递归结果写入；
 *      + 分析：
 *          + 时间复杂度：O(mn)
 *          + 空间复杂度：O(1)
 *      + rank:
 *          + 时间效率：0 ms, 击败 100%
 *          + 空间效率：14.83 MB, 击败 99.86%
 *  + 【思路 4 -- 写法 3】：递推填表
 *      既然 grid[i][j] 值只会在递推到它的位置时使用一次，那么也可以统一的用一个 dp[] 数组，长度 == grid[0].size();
 *          来记录，最新一行的递推值，（因为上一行的递推值，在使用完之后，也不会再使用第二次）
 *      ----
 *      留在以后写吧
 */

#include <vector>
#include <iostream>
using std::vector;

#define MAXLEN 201

// 【思路 4 -- 写法 2】：递推填表
class Solution {
public:
    int minPathSum(vector<vector<int>>& grid) {
        int m = grid.size();
		int n = grid[0].size();
		
		for (int i = 0; i < m; ++i) {
			for (int j = 0; j < n; ++j) {
				int x = i - 1, y = j;
				int res1 = (x < 0 || y < 0) ? -1 : grid[x][y];
				
				x = i; y = j - 1;
				int res2 = (x < 0 || y < 0) ? -1 : grid[x][y];
				
				// 边界情况：
				// 两者都在界内，取最小的；
				// 一方在界内，取在界内的；
				// 两者都在界外，值为 0；
				int res = (res1 >= 0 && res2 >= 0) ? std::min(res1, res2) : (res1 >= 0 ? res1 : (res2 >= 0 ? res2 : 0));
				
				grid[i][j] = res + grid[i][j];
			}
		}
		
		return grid[m - 1][n - 1];
    }
};

// 【思路 4】：DP 递推填表
class Solution {
private:
	static vector<vector<int>> dp;
public:
    int minPathSum(vector<vector<int>>& grid) {
        int m = grid.size();
		int n = grid[0].size();
		
		for (int i = 0; i < m; ++i) {
			for (int j = 0; j < n; ++j) {
				dp[i][j] = 0;
			}
		}
		
		for (int i = 0; i < m; ++i) {
			for (int j = 0; j < n; ++j) {
				int x = i - 1, y = j;
				int res1 = (x < 0 || y < 0) ? -1 : dp[x][y];
				
				x = i; y = j - 1;
				int res2 = (x < 0 || y < 0) ? -1 : dp[x][y];
				
				// 边界情况：
				// 两者都在界内，取最小的；
				// 一方在界内，取在界内的；
				// 两者都在界外，值为 0；且应该让 dp[][] 初始化都为 0；
				int res = (res1 >= 0 && res2 >= 0) ? std::min(res1, res2) : (res1 >= 0 ? res1 : (res2 >= 0 ? res2 : 0));
				
				dp[i][j] = res + grid[i][j];
			}
		}
		
		return dp[m - 1][n - 1];
    }
};

vector<vector<int>> Solution::dp(MAXLEN, vector<int>(MAXLEN, 0));

// 【思路 3】：dfs + 记忆化搜索
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

// 【思路 2】：也是纯递归写法
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