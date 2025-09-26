/**
 * @brief: Leetcode_74_搜索二维矩阵
 * @link: https://leetcode.cn/problems/search-a-2d-matrix/description/
 * @author: liangj.zhang
 * @date: 26/9/2025
 * 
 * @Difficulty: Medium
 * 
 * @Label: Binary Search、Exclusive Method
 * 
 * @Retrospect(worthy 1 - 5): 2
 * 
 * @thoughts:
 *  + 【思路 1】：二分查找
 *      这题，跟在一个一维数组中查找，也没有什么差别了；转换一下坐标；
 * 
 *      + 分析：
 *          + 时间复杂度：O(logn)
 *          + 空间复杂度：O(1)
 *      + rank:
 *          + 时间效率：0 ms, 击败 100%
 *          + 空间效率：13.04 MB, 击败 74.88%
 */

#include <vector>
using std::vector;

class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
     
        int m(matrix.size()), n(matrix[0].size());
        int l(0), r(m * n - 1);
        while (l <= r) {

            int mid = l + (r - l) / 2;
            int x = mid / n;
            int y = mid % n;
            if (matrix[x][y] < target) 
                l = mid + 1;
            else
                r = mid - 1;
        }
        return l != m * n && matrix[l / n][l % n] == target ? true : false;
    }
};