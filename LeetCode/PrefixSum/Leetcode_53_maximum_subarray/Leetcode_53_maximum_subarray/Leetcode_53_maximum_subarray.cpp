/**
* @brief: Leetcode_53_最大子数组和
* @link: https://leetcode.cn/problems/maximum-subarray/description
* @author: liangj.zhang
* @date: 22/6/2025
* 
* @Difficulty: Medium
* 
* @Label: Prefix Sum
* 
* @Again(worthy 0~5): 5
* 
* @brief content: 在前缀和的基础上，进行边遍历边维护当前最小的前缀和，后续遍历到的位置 - 当前最小的前缀和 与 记录下来的最大值相比;
* 
* @thoughts:
*   看的灵神题解，先去做了 买卖股票的最佳时机：https://leetcode.cn/problems/best-time-to-buy-and-sell-stock/description/
*   求出该题的前缀和数组后，和上面只有细微的差别；
*   思路 已在 @brief content 当中进行了描述;
* 
*   分析：
*       时间复杂度：遍历了一遍原数组得到前缀和数组 O(n)，在遍历一遍前缀和数组得到结果 O(n)
*                   总的是 O(n) 时间复杂度；
*       空间复杂度：多使用了一块 O(n + 1) 的复杂度，其实应该也可以原数组中，求得前缀和；
*                   总的是 O(n) 空间复杂度;
* 
*   rank:
*       时间效率：0 ms, 击败 100%
*       空间效率：95.21 MB, 击败 55.88%
*/

#include <vector>
#include <iostream>
using std::cout;
using std::endl;
using std::vector;

#include <set>
using std::pair;
using std::set;

class Solution {
public:
    int maxSubArray(vector<int>& nums) {

        if (nums.size() == 1) return nums[0];

        vector<int> presum(nums.size() + 1, 0);
        presum[0] = 0;
        for (int i = 0; i < nums.size(); ++i) {
            presum[i + 1] = nums[i] + presum[i];
        }

        int minValue = presum[0];
        int maxDiff = -100001;
        int maxIdx = 0;
        for (int i = 1; i < presum.size(); ++i) {

            if (presum[i] - minValue > maxDiff) {

                maxDiff = presum[i] - minValue;
                maxIdx = i;
            }
            if (presum[i] < minValue)
                minValue = presum[i];
        }

        return maxDiff;
    }
};

int main() {

    vector<int> nums = { -2, -1 };
    cout << (new Solution())->maxSubArray(nums);
}