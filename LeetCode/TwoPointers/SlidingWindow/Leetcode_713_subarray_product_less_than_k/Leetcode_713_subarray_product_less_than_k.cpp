/**
 * @brief: Leetcode_713_乘积小于K的子数组
 * @link: https://leetcode.cn/problems/subarray-product-less-than-k/description/
 * @author: liangj.zhang
 * @date: 4/9/2025
 * 
 * @Difficulty: Medium
 * 
 * @Label: Sliding Window(Two Pointers)
 * 
 * @Retrospect(worthy 1 - 5): 4
 * 
 * @thoughts:
 *      + 【思路 1】：滑动窗口
 *          + 可能会有想不通的地方：
 *              + Q: 为什么每次都只考虑固定右端点 r，就能免除重复的情况呢；
 *              + A: 看到 b站 上有个评论很清晰，留了下来，作为回答：
 *                  思考方式问题，需要考虑的是 r 向右拓展时，每次对答案的贡献到底是什么。
 *                  连续的子数组。现在 r 位置进来了，那么这次对答案的贡献有哪些？那就是以 r 结尾的子数组，这些才是新的、有价值的本轮贡献。
 *                  >>> 不以 r 结尾的，那就已经在他的那一轮算掉了，在此就不能重复计算。<<<
 *                  基于此，以 r 结尾的有 【r】、【r-1, r】...【l+1, r】、【l, r】。所以这里有多少个呢，其实等价于 【l, r】 有多少个整数，就等价于 r-l+1。
 *                  举个例子，r=3, l=1，就是 【3】、【3, 2】、【3,2,1】
 *                  + QS: 最重要的是加了 >>> <<< 的地方，细细想来，跟当初做 《Leetcode_15_3sum》时一样，有类似的疑虑，可回顾一下；
 *                          这位网友评论给别人回复的时间时凌晨 03:39，这样迟早会脱发的哟
 *          + 需要注意的地方: 边界条件
 *              + 不能如下：
 *                  + while (prod >= k) {...}
 *                  + 比如: [1, 1, 1], k = 1
 *                      prod 一直为 1，那么左指针就是一直 ++ 下去，访问 nums[l] 时会越界；
 *              + 也不能如下：
 *                  + while (l < r && prod >= k) {...}
 *                  + 比如: [1, 1, 1], k = 1
 *                      prod 一直为 1，那么左指针 l 会停在和 r 一样的位置； 
 *                      res += r - l + 1; => 每次遍历的结果每次都会多加上 1;
 *              + 所以要：
 *                  + while (l <= r && prod >= k) {...}
 *          + 分析：
 *              + 时间复杂度：l 和 r 分别只会遍历一次数组 => O(n)
 *              + 空间复杂度：O(1)
 * 
 *          + rank:
 *              + 时间效率：0 ms, 击败 100%
 *              + 空间效率：63.87 MB, 击败 17.62%
 */

#include <iostream>
#include <vector>
using std::cout;
using std::endl;
using std::vector;

class Solution {
public:
    /** 
     * 以右端点 r 为固定点，得到以 r 为终点的各种组合；
     * 此次不以 r 终点的可能，在以往遍历时，就已经考虑到了；
     * 从 [l, r] 有多少种组合呢：[r, r] [r - 1, r], ..., [l, r]
     * 共 r - l + 1 种，都是以 r 为末端点的各种组合；
    */
    int numSubarrayProductLessThanK(vector<int>& nums, int k) {

        if (k <= 0) return 0;
        
        int res = 0;

        int l = 0;
        int size = nums.size();
        int prod = 1;

        for (int r = 0; r < size; ++r) {

            prod *= nums[r];
            while (l <= r && prod >= k) {
                prod /= nums[l++];
            }
            res += r - l + 1;
        }

        return res;
    }
};

int main() {

    vector<int> nums = {10,5,2,6};
    int k = 100;

    cout << Solution().numSubarrayProductLessThanK(nums, k) << endl;
    return 0;
}