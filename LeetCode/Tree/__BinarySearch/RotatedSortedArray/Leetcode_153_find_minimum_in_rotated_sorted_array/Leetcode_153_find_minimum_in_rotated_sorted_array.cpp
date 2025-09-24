/**
 * @brief: Leetcode_153_寻找旋转排序数组中的最小值
 * @link: https://leetcode.cn/problems/find-minimum-in-rotated-sorted-array/description/
 * @author: liangj.zhang
 * @date: 24/9/2025
 * 
 * @Difficulty: Medium
 * 
 * @Label: BinarySearch
 * 
 * @Retrospect(worthy 1 - 5): 4
 * 
 * @thoughts:
 *  + 【思路 1】：二分查找（旋转螺旋数组）
 *      旋转螺旋数组（上升为例）：
 *          + 一段递增的数组（即最初始的状态，或者后续有回到这个状态），从小到大；
 *          + 两段递增的数组（nums[0] > nums[-1] 必定如此, 题目中数组元素都不相同）；
 *          
 *          最小值一定在 nums[-1] 的左侧；
 *          我们在 [0, n - 2] 的范围内进行二分；
 *          + nums[mid] < nums[-1] 的话，
 *              右边界向左移动，r = mid - 1，右侧染蓝色 (> target: nums[-1])
 *              + 这跟原来的单调性有点不同
 *              + 但我又觉得这是单调性，从 nums[-1] 将两段粘黏起来，应该是的；但是 l, r 的变换不同；
 *              + chat 总结：旋转数组二分找最小值 不依赖“整体单调性”，而是依赖 分段单调 + 与末尾比较的判别条件。
 *          + nums[mid] >= nums[-1] 的话，
 *              左边界向右移动，l = mid + 1，左侧染红色 (< target: nums[-1])
 *      + 分析：
 *          + 时间复杂度：O(logn)
 *          + 空间复杂度：O(1)
 * 
 *      + rank:
 *          + 时间效率：0 ms, 击败 100%
 *          + 空间效率：13.76 MB, 击败 94.52%
 */

#include <vector>
#include <iostream>
using std::vector;
using std::cout;
using std::endl;

class Solution {
public:
    int findMin(vector<int>& nums) {
        
        int size = nums.size();
        int l(0), r(size - 2);
        while (l <= r) {

            int mid = l + (r - l) / 2;
            if (nums[mid] < nums[size - 1])
                r = mid - 1;    // 答案在 mid 左侧，右边界继续往左移动；右侧染蓝色（> target:nums[size - 1])
            else
                l = mid + 1;
        }
        return nums[l];
    }
};