/**
 * @brief: Leetcode_154_寻找旋转排序数组中的最小值_II
 * @link: https://leetcode.cn/problems/find-minimum-in-rotated-sorted-array-ii/description/
 * @author: liangj.zhang
 * @date: 10/10/2025
 * 
 * @Difficulty: Hard
 * 
 * @Label: Binary Search
 * 
 * @Retrospect(worthy 1 - 5): 5
 * 
 * @thoughts:
 *  + 【思路 1】：二分查找
 *      做这题前，应该先做 《Leetcode_153_寻找旋转排序数组中的最小值》
 *      范围：[l, r, last]
 *      当前二分范围：[l, r]
 *      遇到 nums[mid] 与当前范围 nums[last] 相等的情况，那就 last-- 左移动一位; ==> 每次如此，都相当于新的一套 Leetcode_153，不用考虑与 nums[last] 相等的情况；
 *      
 *      + 分析：
 *          + 时间复杂度：O(logn)，最坏 O(n)
 *          + 空间复杂度：O(1)
 * 
 *      + rank:
 *          + 时间效率：0 ms, 击败 100%
 *          + 空间效率：15.87 MB, 击败 59.05%
 */

#include <iostream>
#include <vector>
using std::vector;
using std::cout;
using std::endl;

class Solution {
public:
    int findMin(vector<int>& nums) {
        
        int size = nums.size();
        int l(0), r(size - 2), last(size - 1);

        while (l <= r) {

            int mid = l + (r - l) / 2;
            if (nums[mid] < nums[last]) 
                r = mid - 1;
            else if (nums[mid] == nums[last]) {
                
                --last;
                r = last - 1;
            }
            else
                l = mid + 1;
        }

        return nums[l];
    }
};


int main() {

    // vector<int> nums = {2,2,2,0,1};
    // vector<int> nums = {1,3,5};
    vector<int> nums = {1, 1};
    cout << Solution().findMin(nums) << endl;
}