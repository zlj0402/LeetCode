/**
* @brief: Leetcode_200_岛屿数量
* @link: https://leetcode.cn/problems/number-of-islands/description
* @author: liangj.zhang
* @date: 22/6/2025
* 
* @Difficulty: Medium
* 
* @Label: Graph
* 
* @brief content: 求连通分量
* 
* @Again(Worthy 0~5): 1
* 
* @thoughts:
*	思路很简单，求连通分量；
*	当时三星入职的 Adv 考试都不会这么简单；
*	+ 加了一个剪枝：grid[m][n] == '0' 非岛屿的部分，我是标记访问，但不会 dfs;
* 
*	分析：
*		时间复杂度：O(M * N)，每个点都会遍历一遍;
*		空间复杂度：O(M * N), 申请了满足最大要求的空间
* 
*	rank:
*		时间效率：14 ms, 击败 99.95%
*		空间效率：15.99 MB, 击败 62.12%
*/

#include <vector>
using std::vector;

#include <cstring>
#define MAXLEN 300

bool visited[MAXLEN][MAXLEN];
int Tx[4] = { -1, 0, 1, 0 };
int Ty[4] = { 0, 1, 0, -1 };

class Solution {
private:
    vector<vector<char>>* grid;
    int x, y;
    int ccount;

    void dfs(int m, int n) {

        visited[m][n] = true;

        for (int i = 0; i < 4; ++i) {

            int nm = m + Tx[i];
            int nn = n + Ty[i];
            if (nm >= 0 && nm < x && nn >= 0 && nn < y) {

                if (!visited[nm][nn] && (*grid)[nm][nn] == '1') {

                    visited[nm][nn] = true;
                    dfs(nm, nn);
                }
                else if (!visited[nm][nn] && (*grid)[nm][nn] == '0') {
                    visited[nm][nn] = true;
                }
            }
        }
    }

public:
    int numIslands(vector<vector<char>>& grid) {

        this->grid = &grid;
        x = grid.size();
        y = grid[0].size();
        ccount = 0;
        memset(visited, 0, std::max(x, y) * MAXLEN);

        for (int i = 0; i < x; ++i) {

            for (int j = 0; j < y; ++j) {

                if (!visited[i][j] && grid[i][j] == '1') {

                    ++ccount;
                    dfs(i, j);
                }
            }
        }

        return ccount;
    }
};