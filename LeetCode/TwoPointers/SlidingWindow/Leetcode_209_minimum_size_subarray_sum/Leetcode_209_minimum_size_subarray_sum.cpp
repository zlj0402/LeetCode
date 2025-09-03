/**
 * @brief: Leetcode_209_长度最小的子数组
 * @link: https://leetcode.cn/problems/minimum-size-subarray-sum/description/
 * @author: liangj.zhang
 * @date: 3/9/2025
 * 
 * @Difficulty: Medium
 * 
 * @Label: Sliding Window
 * 
 * @Retrospect(1 - 5): 3
 * 
 * @thoughts:
 *      + 【思路 1】：滑动窗口
 *          虽然是在刷题单阶段，但在视频讲解前，我就暂停了，先自己想了下；
 *          这题的滑动窗口（也是一种双指针），也是很容易想到的；
 * 
 *          + 分析：
 *              + 时间复杂度：l 和 r 最多都只遍历一遍数组的长度 => O(n)
 *              + 空间复杂度：不会随着数组长度的变化，自己使用的变量，不会有更多的空间占用 => O(1)
 *          
 *          + rank:
 *              + 时间效率：0 ms, 击败 100%
 *              + 空间效率：31.34 MB, 击败 88.74%
 */

#include <iostream>
#include <vector>
using std::cout;
using std::endl;
using std::vector;

class Solution {
public:
    int minSubArrayLen(int target, vector<int>& nums) {
        
        int l, r;
        l = r = 0;
        int size = nums.size();
        
        int sum = 0;
        int len = 0;
        int min_len = size + 1;
        while (r < size) {

            sum += nums[r++];
            ++len;

            while (sum >= target) {

                if (min_len > len)
                    min_len = len;
                sum -= nums[l++];
                --len;
            }
        }

        return min_len == size + 1 ? 0 : min_len;
    }
};

int main() {

    int target = 7;
    vector<int> nums = {2,3,1,2,4,3};

    cout << Solution().minSubArrayLen(target, nums);
}