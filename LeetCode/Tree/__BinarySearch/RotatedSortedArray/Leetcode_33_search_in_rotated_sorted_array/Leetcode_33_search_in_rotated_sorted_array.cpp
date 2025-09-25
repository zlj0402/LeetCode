/**
 * @brief: Leetcode_33_搜索旋转排序数组
 * @link: https://leetcode.cn/problems/search-in-rotated-sorted-array/description/
 * @author: liangj.zhang
 * @date: 25/9/2025
 * 
 * @Difficulty: Medium
 * 
 * @Label: Binary Search
 * 
 * @Retrospect(worthy 1 - 5): 4
 * 
 * @thoughts:
 *  + 【思路 1】：二分查找
 *      在刷灵神的题单，最后一道二分的讲解题；
 * 
 *      首先，在昨天写过《153. 寻找旋转排序数组中的最小值》的基础上，可以找到这个最小值；
 *      然后，根据 target 与 nums[-1] 的关系，再进行一次查找是否存在 target；
 * 
 *      如何一次二分解决问题：
 *      分 3 种情况，来判断二分 mid 右边是否染蓝色（即使这样，并不代表染的蓝色区域，都比 target 要大; 只表示这部分可以不再考虑），相反染红色；
 *          1. nums[mid] 和 target 都在第一段当中，且 nums[mid] >= target，那么 mid 右边所有都可以不用考虑，r = mid - 1
 *          2. nums[mid] 在第二段，target 在第一段；不用再判断，这种 mid 右边全部染蓝色，不用考虑；
 *          3. nums[mid] 和 target 都在第二段当中，且 nums[mid] >= target, 那么 mid 右边所有也都可以不用考虑，r = mid - 1
 * 
 *      + 分析：
 *          + 时间复杂度：O(logn)
 *          + 空间复杂度：O(1)
 *      + rank:
 *          + 时间效率：0 ms, 击败 100%
 *          + 空间效率：14.83 MB, 击败 87.62%
 */

#include <iostream>
#include <vector>
using std::cout;
using std::endl;
using std::vector;

class Solution {
public:
    int search(vector<int>& nums, int target) {
        
        int size = nums.size();
        auto is_blue = [&](int mid) -> bool {

            if (nums[mid] > nums[size - 1]) {

                if ( target > nums[size - 1] && nums[mid] >= target)
                    return true;
            } 
            else {

                if (target > nums[size - 1] || nums[mid] >= target)
                    return true;
            }
            return false;
        };

        int l(0), r(size - 2);
        while (l <= r) {

            int mid = l + (r - l) / 2;
            if (is_blue(mid))
                r = mid - 1;
            else
                l = mid + 1;
        }

        return nums[l] == target ? l : -1;
    }
};

int main() {

    vector<int> nums = {1};
    int target = 0;

    cout << Solution().search(nums, target) << endl;
}