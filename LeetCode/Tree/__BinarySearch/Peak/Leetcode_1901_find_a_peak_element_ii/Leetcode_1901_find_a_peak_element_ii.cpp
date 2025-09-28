/**
 * @brief: Leetcode_1901_寻找峰值_II
 * @link: https://leetcode.cn/problems/find-a-peak-element-ii/description/
 * @author: liangj.zhang
 * @date: 28/9/2025
 * 
 * @Difficulty: Medium
 * 
 * @Label: Binary Search
 * 
 * @Retrospect(worthy 1 - 5): 4
 * 
 * @thoughts:
 *  + 【思路 1】：二分查找
 *      我又是看了题解，才勉强理解；
 *      要不是先做了 Leetcode_162，更难理解怎么在纵向上找到一个 peak
 * 
 *      疑问：
 *      这题，又多了一个会产生疑问的地方，在 二分 后，横向 mid 使我们更接近峰顶，得到一个新的行，又去找到这一行的最大值，
 *      与之前走过的行，与最大值同纵向的值，不会大于新找到的最大值吗？
 *      不会，就像 a0 < a < b < b1，这个过程一样；
 * 
 *      + 分析：
 *          + 时间复杂度：
 *              + 以 行 进行二分，O(logm) * n，我的写法
 *              + 以 列 进行二分，O(logn) * m
 *          + 空间复杂度：O(1)
 * 
 *      + rank:
 *          + 时间效率：0 ms, 击败 100%
 *          + 空间效率：49.27 MB, 击败 93.03%
 */

#include <iostream>
#include <vector>
using std::cout;
using std::endl;
using std::vector;

class Solution {
public:
    vector<int> findPeakGrid(vector<vector<int>>& mat) {
        
        int m(mat.size()), n(mat[0].size());
        int l(0), r(m - 2);

        int max_val, max_idx;
        auto get_max = [&](int i) {

            max_val = -1;
            max_idx = -1;
            for (int j = 0; j < n; ++j) {
                if (mat[i][j] > max_val) {
                    max_val = mat[i][j];
                    max_idx = j;
                }
            }
        };
        
        while (l <= r) {
            
            int mid = l + (r - l) / 2;
            get_max(mid);
            if (max_val > mat[mid + 1][max_idx]) {
                r = mid - 1;
            }
            else
                l = mid + 1;
        }

        get_max(l);
        return {l, max_idx};
    }
};

int main() {

    vector<vector<int>> mat = { {10,20,40,50,60,70}, {1,4,2,3,500,80} };
    vector<int> res = Solution().findPeakGrid(mat);
    cout << res[0] << " " << res[1] << endl;
}