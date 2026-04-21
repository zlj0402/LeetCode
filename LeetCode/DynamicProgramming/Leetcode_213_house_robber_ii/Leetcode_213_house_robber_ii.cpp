/**
 * @brief: Leetcode_213_打家劫舍_II
 * @link: https://leetcode.cn/problems/house-robber-ii/description/
 * @author: liangj.zhang
 * @date: 18/4/2026
 * 
 * @updated:
 *  + 22/4/2026: 【思路 2 -- 写法 2】：通用线性的 状态压缩 DP 
 * 
 * @Difficulty: Medium
 * 
 * @Label: Dynamic Programming
 * 
 * @Retrospect(worthy 1 - 5): 5
 * 
 * @thoughts:
 *  + 【思路 1】：DP + 递推 + 填表
 *      灵神题解：
 *      如果偷 nums[0]，那么 nums[1] 和 nums[n−1] 不能偷，问题变成从 nums[2] 到 nums[n−2] 的非环形版本，调用 198 题的代码解决。
 *      如果不偷 nums[0]，那么问题变成从 nums[1] 到 nums[n−1] 的非环形版本，同样调用 198 题的代码解决。
 *      + 分析：
 *          + 时间复杂度：O(n)
 *          + 空间复杂度：O(n)
 *      + rank:
 *          + 时间效率：0 ms, 击败 100%
 *          + 空间效率：10.55 MB, 击败 63.80%
 *  + 【思路 2 -- 写法 1】：状态压缩
 *      + 分析：
 *          + 时间复杂度：O(n)
 *          + 空间复杂度：O(1)
 *      + rank:
 *          + 时间效率：0 ms, 击败 100%
 *          + 空间效率：9.95 MB, 击败 93.78%
 *  + 【思路 2 -- 写法 2】：通用线性的 状态压缩 DP 
 *      + 分析：同 【思路 2 -- 写法 1】：状态压缩
 *      + rank:
 *          + 时间效率：0 ms, 击败 100%
 *          + 空间效率：10.18 MB, 击败 73.04%
 */

#include <vector>
using std::vector;

// 【思路 2 -- 写法 2】：通用线性的 状态压缩 DP 
class Solution {
private:
    // 线性抢劫: 在 nums[start..end] 范围内能抢到的最大金额
    int robLinear(vector<int>& nums, int start, int end) {
        if (start > end) return 0;
        if (start == end) return nums[start];
        
        int prev2 = 0, prev1 = nums[start];
        for (int i = start + 1; i <= end; ++i) {
            int cur = std::max(prev1, prev2 + nums[i]);
            prev2 = prev1;
            prev1 = cur;
        }
        return prev1;
    }
public:
    int rob(vector<int>& nums) {
        if (nums.size() == 1) return nums[0];
        int size = nums.size();

        return std::max(robLinear(nums, 0, size - 2),
                    robLinear(nums, 1, size - 1));
    }
};

// 【思路 2 -- 写法 1】：状态压缩
class Solution {
public:
    int rob(vector<int>& nums) {
        if (nums.size() == 1) return nums[0];
        int size = nums.size();

        int prev1_2 = 0, prev1_1 = nums[0]; // 从第 1 个数 num[0] 开始选
        int prev2_2 = 0, prev2_1 = 0;   // 从第 2 个数 nums[1] 开始选
        int i = 1, cur1 = prev1_1, cur2;
        for (; i < size - 1; ++i) {
            // current max result
            cur1 = std::max(prev1_1, prev1_2 + nums[i]); 
            cur2 = std::max(prev2_1, prev2_2 + nums[i]);

            prev1_2 = prev1_1; prev1_1 = cur1;
            prev2_2 = prev2_1; prev2_1 = cur2;
        } // max: rec0[size - 1]
        // 下面的过程，只适用于 i >= 2
        cur2 = std::max(prev2_1, prev2_2 + nums[i]);

        return cur1 >= cur2 ? cur1 : cur2;
    }
};

// 【思路 1】：DP + 递推 + 填表
class Solution {
public:
    int rob(vector<int>& nums) {
        if (nums.size() == 1) return nums[0];

        int size = nums.size();
        vector<int> rec0(size + 1, 0);
        vector<int> rec1(size + 1, 0);

        rec0[0] = 0; rec0[1] = nums[0];
        for (int i = 1; i < size - 1; ++i) {    // nums[0, size - 2] => rec0[1, size - 1]
            rec0[i + 1] = std::max(rec0[i], rec0[i - 1] + nums[i]);
        } // max: rec0[size - 1]

        // 下面的过程，只适用于 i >= 2
        rec1[0] = 0; rec1[1] = 0;
        for (int i = 1; i < size; ++i) {    // nums[1, size - 1] => rec1[2, size]
            rec1[i + 1] = std::max(rec1[i], rec1[i - 1] + nums[i]);
        } // max: rec1[size]

        return rec1[size] >= rec0[size - 1] ? rec1[size] : rec0[size - 1];
    }
};