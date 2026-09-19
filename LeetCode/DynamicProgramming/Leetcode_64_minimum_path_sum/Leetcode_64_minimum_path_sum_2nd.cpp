/**
 * @brief: Leetcode_64_最小路径和_2nd
 * @link: https://leetcode.cn/problems/minimum-path-sum/description/
 * @author: liangj.zhang
 * @date: 2026/09/19
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
 */

#include <vector>
using std::vector;

class Solution {
private:
    static constexpr int MAXVAL = 80001; // 原来错误的写法： MAXVAL = 201; 错误，因为前两个位置的值也是叠加上来的
public:
    int minPathSum(vector<vector<int>>& grid) {
        int m = grid[0].size();
        int n = grid.size();
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                int val1 = MAXVAL, val2 = MAXVAL;
                if (i - 1 >= 0) val1 = grid[i - 1][j]; // 上一行的位置
                if (j - 1 >= 0) val2 = grid[i][j - 1]; // 上一列的位置
                int min_ = std::min(val1, val2);
                grid[i][j] += min_ == MAXVAL ? 0 : min_;
            }
        }
        return grid[n-1][m-1];
    }
};