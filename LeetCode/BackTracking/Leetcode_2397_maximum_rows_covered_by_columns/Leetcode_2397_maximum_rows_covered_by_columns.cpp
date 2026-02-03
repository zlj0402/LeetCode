/**
 * @brief: Leetcode_2397_被列覆盖的最多行数
 * @link: https://leetcode.cn/problems/maximum-rows-covered-by-columns/description/
 * @author: liangj.zhang
 * @date: 2/2/2026
 * 
 * @updated:
 *  + 3/2/2026: 【思路 2】：Bitmap
 * 
 * @Difficulty: Medium
 * 
 * @Label: BackTracking(DFS) | Bitmap
 * 
 * @Retrospect(worthy 1 - 5): 4
 * 
 * @thoughts:
 *  + 【思路 1】：BackTracking(DFS)
 *      回溯相当于，遍历的方式不重复的挑出每种情况
 *      当达到 numSelect 时，查看跟这一行的和是不是相同，相同则可以记上一行；所有行被相比较之后，与最大值相比；
 *      + 分析：
 *          + 时间复杂度：遍历 matrix 得到每行的和：O(m*n) + DFS: O(C(n, numSelect) * m * numSelect)
 *          + 空间复杂度：O(m) 局部数组，dfs: O(numSelect)
 * 
 *  + 【思路 2】：Bitmap
 *     本来没有理解这种做法的，第二天就突然有所理解了；
 *     理解参考代码注释；
 *      + 分析：
 *          + 时间复杂度：O(m*n) + O(2^n)
 *          + 空间复杂度：O(m) 临时数组
 */
#include <vector>
#include <numeric>
using std::vector;

class Solution {
public:
    int maximumRows(vector<vector<int>>& matrix, int numSelect) {
        
        int rowCnt = matrix.size();
        int colCnt = matrix[0].size();
        vector<int> matMask(rowCnt, 0);
        for (int i = 0; i < rowCnt; ++i) {
            for (int j = 0; j < colCnt; ++j) {
                matMask[i] |= matrix[i][j] << j;
            }
        }
        // -----------------------------------

        int maxCnt = -1;
        for (int mask = 0; mask < (1 << colCnt); ++mask) {
            if (__builtin_popcount(mask) != numSelect) continue;

            int cnt = 0;
            for (int i = 0; i < rowCnt; ++i)
                if ((matMask[i] & mask) == matMask[i])  // mask 的 1 完全包含 matMask[i] 中的 1; mask 中 1 仅代替被选中的列，1 的个数即被选中的列的个数；
                    ++cnt;                              // 你可能在想特殊情况，matMask[i] 中这一行全是 0，mask 表示的，选中的列数和 numSelect 相同时，依然满足(matMask[i] & mask) == matMask[i]
        
            if (cnt > maxCnt) maxCnt = cnt;
        }

        return maxCnt;
    }
};

/*
class Solution {
public:
    int maximumRows(vector<vector<int>>& matrix, int numSelect) {
        
        int rowCnt = matrix.size();
        int colCnt = matrix[0].size();

        vector<int> matSum(rowCnt, 0);
        for (int i = 0; i < rowCnt; ++i) {
            matSum[i] = std::accumulate(matrix[i].begin(), matrix[i].end(), 0);
        }

        int maxColumns = -1;
        vector<int> mat(rowCnt, 0);

        auto dfs = [&](auto&&dfs, int i, int selected) -> void {

            if (selected == numSelect) {

                int cnt = 0;
                for (int i = 0; i < rowCnt; ++i) 
                    if (matSum[i] == mat[i])
                        ++cnt;

                if (cnt > maxColumns)
                    maxColumns = cnt;
                return;
            }

            for (int j = i; j < colCnt; ++j) {
                
                for (int k = 0; k < rowCnt; ++k) mat[k] += matrix[k][j];
                dfs(dfs, j + 1, selected + 1);
                for (int k = 0; k < rowCnt; ++k) mat[k] -= matrix[k][j];
            }
        };

        dfs(dfs, 0, 0);
        return maxColumns;
    }
};
*/

int main() {


    vector<vector<int>> matrix = {{0,0,0},{1,0,1},{0,1,1},{0,0,1}};
    int numSelect = 2;
    Solution().maximumRows(matrix, numSelect);
}