/**
 * @brief: Leetcode_3379_转换数组
 * @link: https://leetcode.cn/problems/transformed-array/description
 * @author: liangj.zhang
 * @date: 5/2/2026
 * 
 * @Difficulty: Easy
 * 
 * @Lable: circular queue
 * 
 * @Retrospect(worthy 1 - 5): 2
 * 
 * @thoughts:
 *  + 【思路 1】：得到 新的坐标 是唯一的关键，然后弄清楚谁赋给谁；
 *      每日一题，赚 10 积分；
 *      ---
 *      新位置的值 nums[new_idx] 赋给 result[i]，i 是原下标；
 *      这题也是必须要开一个新的空间
 * 
 *      + 分析：
 *          + 时间复杂度：O(n)
 *          + 空间复杂度：O(n)
 *      + rank:
 *          + 写法一：
 *              + 时间效率：7 ms, 击败 75.73%
 *              + 空间效率：25.38 MB, 击败 12.62%
 *          + 写法二：
 *              + 时间效率：8 ms, 击败 54.37%
 *              + 空间效率：25.31 MB, 击败 19.42%
 */
#include <vector>
#include <iostream>
using std::vector;

// 写法 2
class Solution {
public:
    vector<int> constructTransformedArray(vector<int>& nums) {
        
        int len = nums.size();
        vector<int> result(len, 0);

        for (int i = 0; i < len; ++i) {
            int step = nums[i] > 0 ? nums[i] : nums[i] % len + len;
            result[i] = nums[(i + step) % len];
        }
        return result;
    }
};

// 写法 1
/*
class Solution {
private:
    int nextPos(int idx, int val, int len) {

        if (val > 0) {
            return (idx + val) % len;
        }
        else if (val < 0) {
            int new_idx = (idx + val) % len;
            if (new_idx < 0)
                new_idx += len;
            return new_idx;
        }
        else
            return idx;
    }

    int nextPos(int idx, vector<int>& nums) {
        return nextPos(idx, nums[idx], nums.size());
    }
public:
    vector<int> constructTransformedArray(vector<int>& nums) {
        
        int len = nums.size();
        vector<int> result(len, 0);

        for (int i = 0; i < len; ++i) {
            result[i] = nums[nextPos(i, nums)];
        }
        return result;
    }
};
*/

int main() {

    std::cout << -1 % 4 << std::endl; 
    std::cout << -2 % 4 << std::endl; 
    std::cout << -3 % 4 << std::endl; 
    std::cout << -4 % 4 << std::endl; 
    std::cout << -5 % 4 << std::endl; 
    std::cout << -6 % 4 << std::endl; 
}