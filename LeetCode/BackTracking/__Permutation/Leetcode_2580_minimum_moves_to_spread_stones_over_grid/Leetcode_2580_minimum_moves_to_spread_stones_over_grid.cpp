/**
 * @brief: Leetcode_2580_将石头分散到网格图的最少移动次数
 * @link: https://leetcode.cn/problems/minimum-moves-to-spread-stones-over-grid/description/
 * @author: liangj.zhang
 * @date: 13/4/2026
 * 
 * @Difficulty: Medium
 * 
 * @Label: backtracking(permutation) & enum
 * 
 * @Retrospect(worthy 1 - 5): 4
 * 
 * @thoughts:
 *  + 【思路 1】：回溯 | 排列 | 枚举
 *      自己第一时间没有想出做法，是看的灵神题解；
 *      看完的第一感觉，这是多 low 的做法...，再看第二种《最小费用最大流》，时间效率空间效率怎么更 low；
 *      虽然全排列的做法，就是枚举出所有的情况，但不失是一种解决的方式；（然而没想到，竟是最优的方式，此题
 * 
 *      灵神思路：
 *      由于所有移走的石子个数等于所有移入的石子个数（即 0 的个数），
 *      我们可以把移走的石子的坐标记录到列表 from 中（可能有重复的坐标），移入的石子的坐标记录到列表 to 中。
 *      这两个列表的长度是一样的。
 * 
 *      to 不动，排列出所有 from 的所有情况，   
 *      然后算出每一种，from - to 的曼哈顿距离之和，比较出最小的情况；
 * 
 *      + 分析：
 *          + 时间复杂度：mn * (mn)! --- mn -> 元素个数，可见排列的时间效率的增长级别，比组合的指数级还要高
 *          + 空间复杂度：O(mn) 递归 + O(mn) 数组 -> O(mn)
 *      + rank:
 *          + 时间效率：75 ms, 击败 21.34%
 *          + 空间效率：22.28 MB, 击败 26.83%
 *      ---
 *      看了时间效率的第一个柱子，同样的做法，感觉通过 next_permutation 库接口的方式，效率要比我的方式，要高的多；
 *      明天再用这个接口写一下；
 */

#include <vector>
#include <iostream>
using std::cout;
using std::endl;
using std::vector;

#include <cmath>
#include <cassert>

class Solution {
private:
    static int calcManhattanDistance(vector<std::pair<int, int>> &path, vector<std::pair<int, int>> &to) {
        int sum = 0;
        for (int i = 0; i < path.size(); ++i)
            sum += std::abs(path[i].first - to[i].first) + std::abs(path[i].second - to[i].second);
        return sum;
    }
public:
    int minimumMoves(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();

        vector<std::pair<int, int>> from;
        vector<std::pair<int, int>> to;

        // list from/to
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (grid[i][j] > 1) {
                    for (int k = 0; k < grid[i][j] - 1; ++k) {
                        from.push_back({i, j});
                    }
                }
                else if (grid[i][j] == 0) {
                    to.push_back({i, j});
                }
            }
        }

        assert(from.size() == to.size());

        int size = from.size();
        vector<bool> visit(size, false);
        vector<std::pair<int, int>> path(size);

        // permutation & calculate Manhattan Distance
        int minSum = INT_MAX;
        auto dfs = [&](this auto&& dfs, int idx) -> void {

            if (idx == size) {
                if (int sum = calcManhattanDistance(path, to); sum < minSum) {
                    minSum = sum;
                }
                return;
            }

            for (int i = 0; i < size; ++i) {
                if (!visit[i]) {
                    visit[i] = true;
                    path[idx] = from[i];
                    dfs(idx + 1);
                    path[idx] = {-1, -1};
                    visit[i] = false;
                }
            }
        };

        dfs(0);

        return minSum;
    }
};

int main() {
    vector<vector<int>> grid = {
        {1, 1, 0},
        {1, 1, 1},
        {1, 2, 1}
    };
    Solution().minimumMoves(grid);
}