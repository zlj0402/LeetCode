/**
 * @brief: Leetcode_2300_咒语和药水的成功对数
 * @link: https://leetcode.cn/problems/successful-pairs-of-spells-and-potions/description/
 * @author: liangj.zhang
 * @date: 15/9/2025
 * 
 * @Difficulty: Medium
 * 
 * @Label: Sort && Binary Search、Counter && Suffix Sum
 * 
 * @Retrospect(worthy 1 -5): 3
 * 
 * @thoughts:
 *  + 【思路 1】：排序 + 二分查找
 *      success / potion 向上取整的结果，就是 lower_bound 参数中的 target; 对每个元素都要进行；
 *      当然 potions，在一开始就要进行升序排序；
 * 
 *      + ps: 学习到了正整数运算，达到 ceil 效果的 skill 了：
 *              + >>> (Dividend - 1) / Divisor + 1 <<<
 *              + (被除数 - 1) / 除数 + 1
 * 
 *      + 分析：
 *          + 时间复杂度：排序 O(mlogm); m -> potions.size(); 为每个 spell，进行二分查找 -> O(nlogm); n -> spells.size()
 *              + 总结：O((n + m)logm)
 *          + 空间复杂度：O(1)，忽略排序的栈开销；
 * 
 *      + rank:
 *          + 时间效率：43ms, 击败 93.28%
 *          + 空间效率：122.08 MB, 击败 97.77%
 * 
 *  + 【思路 2】：Counter && 后缀和
 *      在题解中看了，能够理解，留着以后做吧；-- 15/9/2025
 */

#include <iostream>
#include <vector>
using std::cout;
using std::endl;
using std::vector;

#include <algorithm>
#include <functional>
#include <cmath>

// 【思路 1】：排序 + 二分查找
class Solution {

private:
    static int lower_bound(vector<int>& nums, long long target) {

        int left(0), right(nums.size() - 1);
        while (left <= right) {

            int mid = left + (right - left) / 2;
            if (nums[mid] < target)
                left = mid + 1;
            else
                right = mid - 1;
        }

        return left;
    }

public:
    vector<int> successfulPairs(vector<int>& spells, vector<int>& potions, long long success) {
        
        std::sort(potions.begin(), potions.end(), std::less<int>());
        int size = spells.size();
        int po_size = potions.size();
        vector<int> res(size);

        for (int i = 0; i < size; ++i) {
            // quotient
            // long long quo = std::ceil(success * 1.0 / spells[i]);
            long long quo = (success - 1) / spells[i] + 1;  // better in 整数运算
            if (quo > potions[po_size - 1]) 
                continue;
            
            int idx = lower_bound(potions, quo);
            res[i] = po_size - idx;
        }

        return res;
    }
};

int main() {
    
    vector<int> spells = {3,1,2};
    vector<int> potions = {8, 5, 8};
    long long success = 16;

    Solution().successfulPairs(spells, potions, success);
}