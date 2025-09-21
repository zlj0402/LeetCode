/**
 * @brief: Leetcode_243_最小化数组中的最大值
 * @link: https://leetcode.cn/problems/minimize-maximum-of-array/description/
 * @author: liangj.zhang
 * @date: 21/9/2025
 * 
 * @Difficulty: Medium
 * 
 * @Label: Binary Search、Prefix Sum & Greedy
 * 
 * @Retrospect(worthy 1 - 5): 4
 * 
 * @thoughts:
 *  + 【思路 1】：二分查找（二分猜答案）
 *      自己没写出来，以为从后往前比较平均值，就能得到答案，并不行；
 *      看了题解的前面，我就知道了；自己取平均值，只是一种取值；
 *      把 min(nums) <= limit <= max(nums) 作为二分的范围，每一次的 mid，都从后往前摊，nums[i] 高于 limit 的（要加上 extra），就移给下一个；
 *      
 *      + 灵神题解：
 *      + 把 nums[i] 想象成一个大小为 nums[i] 的积木堆，我们可以把一个积木移动到左边相邻的积木堆中。进一步地，多出的积木并不是只能移动一次，而是可以多次向左移动，从 i 移动到 i−1，再移动到 i−2，依此类推。
 * 
 *      + 写了三种写法，第二种更快一点，但更喜欢第三种，封装起来更清晰；
 *      + 后两种写法，是在看了同样的二分算法，但更快的代码，才意识到 考虑 extra 就可以了；当然自己考虑的 最后的 cur(nums[0] + extra) 也没错；
 * 
 *      + 分析：
 *          + 时间复杂度：O(n * logU), U = max(nums) - min(nums)
 *          + 空间复杂度：O(1)
 *      + rank:
 *          + 时间效率：12 ms, 击败 78.05%
 *          + 空间效率：73.3 MB, 击败 68.05
 * 
 *  + 【思路 2】：前缀和 & 贪心算法；（留以后写，不然都没意识到用的是贪心
 */

#include <vector>
#include <iostream>
using std::cout;
using std::endl;
using std::vector;

#include <algorithm>

class Solution {

public:
    int minimizeArrayValue(vector<int>& nums) {
        
        int size(nums.size());
        int max_val = *std::max_element(nums.begin(), nums.end());
        int min_val = *std::min_element(nums.begin(), nums.end());
        int l(min_val), r(max_val);
        
        while (l <= r) {

            int mid = l + (r - l) / 2;

            long long extra = 0;

            // 循环写法 1：关注的是 nums[0] 加上 上一次的 extra 与 limit(mid) 的大小关系；
            // int i = size;
            // long long cur;
            // while (--i >= 0) {

            //     while (i > 0 && (1LL * nums[i] + extra) <= mid) {--i; extra = 0;}
            //     cur = 1LL * nums[i] + extra;
            //     if (cur > mid) {
            //         extra = cur - mid;
            //     }
            // }
            // if (cur > mid)
            //     l = mid + 1;
            // else
            //     r = mid - 1;

            // 循环写法2：只关注 extra 值；就知道 nums[0] 加上 上一次的进值 extra，与 limit 的大小关系，
            // 新的 extra > 0 则表示 limit 取小了 => l = mid + 1;
            // 新的 extra <= 0 则表示 limit 取大了 => r = mid - 1; 
            for (int i = size - 1; i >= 0; --i) {

                if (nums[i] + extra > mid)
                    extra = nums[i] + extra - mid;
                else
                    extra = 0;
            }

            if (extra)
                l = mid + 1;
            else
                r = mid - 1;

            // 循环写法3：同循环2，用 lambda 封装一下;
            // auto check = [&](int limit) {

            //     long long extra = 0;
            //     for (int i = size - 1; i >= 0; --i) {

            //         if (nums[i] + extra > mid)
            //             extra = nums[i] + extra - limit;
            //         else
            //             extra = 0;
            //     }

            //     return extra;
            // };

            // if (check(mid))
            //     l = mid + 1;
            // else 
            //     r = mid - 1;
        }

        return l;
    }
};

int main() {
    
    // vector<int> nums = {3,7,1,6};
    // vector<int> nums = {10,s 1};
    vector<int> nums = {8, 0, 16};
    cout << Solution().minimizeArrayValue(nums) << endl;
}