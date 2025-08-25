/**
 * @brief: Leetcode_2824_count_pairs_whose_sum_is_less_than_target
 * @link: https://leetcode.cn/problems/count-pairs-whose-sum-is-less-than-target/description/
 * @author: liangj.zhang
 * @date: 25/8/2025
 * 
 * @Difficulty: Easy
 * 
 * @Label: Two Pointers(Facing)、Sort
 * 
 * @Retrospect(Worthy 0 - 5): 2 
 * 
 * @thoughts:
 *      惭愧，看到题目，我下意识的以为这道题不能够打乱顺序；
 *      我首先，看了题目，有两个想法，因为我也注意到数组最多也就是 50 个数据；（这肯定是某一场周赛题，难度降低的第一题）
 *      1. 循环；O(n^2)，不是完整的 n^2，跟冒泡的逻辑过程一样，内循环每次会缩小范围；
 *      2. index sort + 双指针
 *          右指针，做一个循环之外范围的变量 j；当前遍历的 i 结束之后，j 下次只会变得更小；不需要每次从尾部开始右指针；
 * 
 *      a + b < target 跟 b + a < target 是一样的，就是变成求不重复的元组，跟 Leetcode_15_3sum 的要求一样了；
 *      所以第 2 种方式，直接是 sort（O(nlogn)） + 双指针（O(n)）
 * 
 *      + 思路 1：暴力循环（数据量小
 *          + 分析：
 *              + 时间复杂度：O(n^2)
 *              + 空间复杂度：O(1)
 *          + rank:
 *              + 时间效率：0 ms, 击败 100%
 *              + 空间效率：24.05 MB, 击败 58.32%
 * 
 *      + 思路 2：排序 + 双指针
 *          + 分析：
 *              + 时间复杂度：排序O(nlogn) + 双指针O(n)
 *              + 空间复杂度：O(1)
 *          + rank:
 *              + 时间效率：0 ms, 击败 100%
 *              + 空间效率：23.97 MB, 击败 85.62%
 */

#include <vector>
#include <iostream>
using std::cout;
using std::endl;
using std::vector;

#include <algorithm>

// 【思路 2】
class Solution {
public:
    int countPairs(vector<int>& nums, int target) {
        
        sort(nums.begin(), nums.end());
        int count = 0;
        int j = nums.size() - 1;
        for (int i = 0; i < j; ++i) {
            
            while (j > i && nums[i] + nums[j] >= target) --j;
            count += j - i;
        }
        return count;
    }
};

// 【思路 1】
/*
class Solution {
public:
    int countPairs(vector<int>& nums, int target) {
        
        int count = 0;
        for (int i = 0; i < nums.size(); ++i) {

            for (int j = i + 1; j < nums.size(); ++j) {

                if (nums[i] + nums[j] < target)
                    ++count;
            }
        }
        return count;
    }
};*/

int main() {

    int target = 2;
    vector<int> nums = {-1,1,2,3,1};
    cout << (new Solution())->countPairs(nums, target) << endl;
}