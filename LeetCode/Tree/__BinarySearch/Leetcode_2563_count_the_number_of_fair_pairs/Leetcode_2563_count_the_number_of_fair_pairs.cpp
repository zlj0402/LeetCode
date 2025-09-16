/**
 * @brief: Leetcode_2563_统计公平数对的数目
 * @link: https://leetcode.cn/problems/count-the-number-of-fair-pairs/description/
 * @author: liangj.zhang
 * @date: 16/9/2025
 * 
 * @Difficulty: Medium
 * 
 * @Label: Binary Search、Three Pointers(Facing)、Two Pointer twice
 * 
 * @Retrospect(worthy 1 - 5): 4
 * 
 * @thoughts:
 *      + 【思路 1】：二分查找
 *          + lower_bound -> 解决的是 >= target
 *          + find >= lower - nums[i]
 *          + find <= upper - nums[i]
 * 
 *          + 分析：
 *              + 时间复杂度：排序 O(nlogn) + 二分查找 O(logn) * n => O(nlogn)，常数大
 *              + 空间复杂度：O(1)
 * 
 *          + rank:
 *              + 时间效率：65 ms, 击败 71.44%
 *              + 空间效率：70.15 MB, 击败 43.06%
 * 
 *      + 【思路 2】：相向三指针
 *          + 想找的，还是 lower - nums[i] 和 upper - nums[i] 的位置
 *          + >= lower - nums[i] 和 > upper - nums[i]
 *          + 题目： upper >= lower 
 *          + 排序后的数组，随着 nums[i] 逐渐增大，lower - nums[i] 和 upper - nums[i] 都会减小
 *          + L 找到 >= lower - nums[i] 的位置；R 找到 > upper - nums[i] 的位置；
 *          + 下一次遍历，从上一次的 指针 位置开始往前，因为 [lower/upper] - nums[i] 是在不断减小的；
 *          + (i, R] 的范围，是能达成 公平数对 的范围；
 *              + L > i 时，[L, R]
 *              + L <= i 时，(i, R]
 *              + R <= i 时，循环可以结束了；
 * 
 *          + 分析：
 *              + 时间复杂度：排序 O(nlogn) + 相向三指针 2 * O(n) => O(nlogn)
 *              + 空间复杂度：O(1)
 * 
 *          + rank:
 *              + 时间效率：35 ms, 击败 99.39%
 *              + 空间效率：70.07 MB, 击败 66.77%
 */

#include <iostream>
#include <vector>
using std::cout;
using std::endl;
using std::vector;

#include <algorithm>
#include <functional>

class Solution {
public:
    long long countFairPairs(vector<int>& nums, int lower, int upper) {
        
        int size = nums.size();
        int l(size - 1), r(size - 1);
        long long cnt = 0;

        std::sort(nums.begin(), nums.end(), std::less<int>());

        for (int i = 0; i < size; ++i) {
            
            while (l >= 0 && nums[l] >= lower - nums[i]) --l; // 直到 nums[l] < lower - nums[i]
            // l += 1; // nums[l] >= lower - nums[i]; 的第一个位置
            while (r >= 0 && nums[r] > upper - nums[i]) --r;  // 直到 nums[r] <= upper - nums[i]

            if (r <= i)
                return cnt;
            
            cnt += r - std::max(l, i);
        }

        return cnt;
    }
};

// 【思路 1】：二分查找
/*
class Solution {

private:
    static int lower_bound(vector<int>& nums, int target, int left);

public:
    long long countFairPairs(vector<int>& nums, int lower, int upper) {
        
        std::sort(nums.begin(), nums.end(), std::less<int>());
        int size = nums.size();
        long long cnt = 0;

        for (int i = 0; i < size - 1; ++i) {
            // lower_bound -> 解决的是 >= target
            // find >= lower - nums[i]
            int lower_idx = lower <= nums[i] + nums[i + 1] ? 
                            i + 1 : lower_bound(nums, lower - nums[i], i + 1);
            
            // find <= upper - nums[i]
            int upper_idx = upper >= nums[i] + nums[size - 1] ? 
                            size - 1 : lower_bound(nums, upper - nums[i] + 1, i + 1) - 1;

            if (lower_idx != size) 
                cnt += upper_idx - lower_idx + 1;
        }

        return cnt;
    }
};

int Solution::lower_bound(vector<int>& nums, int target, int left) {

    int right(nums.size() - 1);
    while (left <= right) {
        
        int mid = left + (right - left) / 2;
        if (nums[mid] < target) 
            left = mid + 1;
        else
            right = mid - 1;
    }
    return left;
}
*/

int main() {

    // vector<int> nums = {0,1,7,4,4,5};
    // vector<int> nums = {-5,-7,-5,-7,-5};
    vector<int> nums = {1, 7, 9, 2, 5};
    int lower = 11;
    int upper = 11;

    cout << Solution().countFairPairs(nums, lower, upper) << endl;

    return 0;
}