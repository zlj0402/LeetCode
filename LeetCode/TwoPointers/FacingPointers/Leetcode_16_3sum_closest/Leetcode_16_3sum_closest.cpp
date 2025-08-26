/**
 * @brief: Leetcode_16_3sum_closest
 * @link: https://leetcode.cn/problems/3sum-closest/description/
 * @author: liangj.zhang
 * @date: 26/8/2025
 * 
 * @Difficulty: Medium
 *      + 代码中 nums[i] + nums[j] + nums[k] < target, 一下描述中，我简写为 i + j + k < t
 *      + 较为难以理解的应该是，有大于有小于（< t or > t）的过程中，都记录了，进行了比较，
 *      + 那因为排序的原因，被过滤的搭配中，没有会比结果更小的吗？
 *          + 假设上一次是 k 的变化
 *              + 当前如果是 i + j + k > t,
 *                  + 那在此之前，idx k 之后的数，|i + j + >k| 只会更大（>k 表示比 nums[k] 大的后面因为 k 指针过滤掉的值
 *              + 当前如果是 i + j + k < t,
 *                  + 那么这个组合是没有忽略的，pass
 *          + 假设上一次是 j 的变化
 *              + 当前如果是 i + j + k < t，
 *                  + 那在此之前，idx j 之前的数，|i + <j + k| 只会更大（<j 表示比 nums[j] 小的前面因为 j 指针过滤掉的值
 *              + 当前如果是 i + j + k > t,
 *                  + 那么这个组合是没有忽略的，pass
 * 
 * @Label: Two Pointers(Facing)
 * 
 * @Retrospect(worthy 1 - 5): 3
 * 
 * @thoughts:
 *      + 思路 1：排序 + 双指针
 *          + 分析：
 *              + 时间复杂度：排序（O(nlogn)）+ 双指针（O(n^2)） => O(n^2)
 *              + 空间复杂度：没有申请同数组长度的栈空间堆空间 => O(1)
 *          + rank:
 *              + 时间效率：4ms, 击败 84.84%
 *              + 空间效率：13.61 MB, 击败 96.14%
 */

#include <iostream>
#include <vector>
using std::cout;
using std::endl;
using std::vector;

#include <algorithm>
#include <functional>

class Solution {
private:
    int abs_min;
    int min_sum;

public:
    int threeSumClosest(vector<int>& nums, int target) {
        
        abs_min = 200001;
        min_sum = 199999;
        int size = nums.size();
        sort(nums.begin(), nums.end(), std::less<int>());
        
        for (int i = 0; i < size - 2; ++i) {

            if (i != 0 && nums[i] == nums[i - 1]) continue;

            int sum = nums[i] + nums[i + 1] + nums[i + 2];
            if (sum > target && sum - target < abs_min) {
                
                abs_min = sum - target;
                min_sum = sum;
                continue;
            }
            sum = nums[i] + nums[size - 2] + nums[size - 1];
            if (sum < target && target - sum < abs_min) {
                
                abs_min = target - sum;
                min_sum = sum;
                continue;
            }
            
            int j = i + 1;
            int k = size - 1;
            while (j < k) {

                sum = nums[i] + nums[j] + nums[k];
                if (sum > target) {

                    --k;
                    if (sum - target < abs_min) {
                        
                        abs_min = sum - target;
                        min_sum = sum;
                    }
                }
                else if (sum < target) {

                    ++j;
                    if (target - sum < abs_min) {

                        abs_min = target - sum;
                        min_sum = sum;
                    }
                }
                else 
                    return target;
            }
        }

        return min_sum;
    }
};

int main() {

    int target = 2;
    vector<int> nums = {-1,2,1,-4};

    cout << (new Solution())->threeSumClosest(nums, target);

}