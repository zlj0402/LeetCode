/**
 * @brief: Leetcode_611_有效三角形的个数
 * @link: https://leetcode.cn/problems/valid-triangle-number/description/
 * @author: liangj.zhang
 * @date: 26/8/2025
 * 
 * @Difficulty: Medium
 * 
 * @Label: Two Pointers(Facing)
 * 
 * @Retrospect(worthy 1 - 5): 3
 * 
 * @thoughts:
 *      + 思路 1：排序 + 枚举长边的相向双指针
 *          + 三角形的构成规则：任意两边之和大于第三边 a + b > c
 *              + 上面的形式是不是很眼熟：i + j > k（nums[i] + nums[j] == target
 *                  + 我们处理过 3sum ≈ target -> https://leetcode.cn/problems/3sum-closest/description/
 *                  + 还处理不好两数的？
 *                  + 只不过这里的 target 是我们自己的数据，那我们就倒着来，k 是大数，
 *                      + 循环内部是 i + j > target，两数大于 target
 *                  + 印象中，三角形的规则还有这么一个规律：
 *                      + 较小的两边之和 > 第 3 边，一定能构成三角形；
 *                  + 那么我们就可以开始了；
 *          + 分析：
 *              + 时间复杂度：排序 O(nlogn) + 相向双指针 O(n^2)
 *              + 空间复杂度：没有申请额外很长的栈空间堆空间 O(1)
 *          + rank:
 *              + 时间效率：19 ms, 击败 99.91%
 *              + 空间效率：16.4 MB, 击败 27.32%
 */

#include <iostream>
#include <vector>
using std::cout;
using std::endl;
using std::vector;

#include <algorithm>

class Solution {
public:
    int triangleNumber(vector<int>& nums) {

        sort(nums.begin(), nums.end());
        int cnt = 0;
        int size = nums.size();
        for (int k = size - 1; k >= 2; --k) {

            if (nums[0] + nums[1] > nums[k]) {
                // 组合的计算公式得来的 C(n, r) = (n!)/[(r!)(n - r)!]
                cnt += (k - 1) * k * (k + 1) / 6;
                return cnt;
            }
            if (nums[k - 1] + nums[k - 2] < nums[k]) continue;

            int i = 0;
            int j = k - 1;
            while (i < j) {
                
                int sum = nums[i] + nums[j];
                if (sum > nums[k]) {

                    cnt += j - i;
                    --j;
                } // sum <= nums[k]
                else 
                    ++i;
            }
        }

        return cnt;
    }
};