/**
 * @brief: Leetcode_3005_最大频率元素计数
 * @link: https://leetcode.cn/problems/count-elements-with-maximum-frequency/description/
 * @author: liangj.zhang
 * @date: 22/9/2025
 * 
 * @Difficulty: Easy (Score: 1217)
 * 
 * @Label: Array、HashMap
 * 
 * @Retrospect(worthy 1 - 5): 1
 * 
 * @thoughts:
 *  + 【思路 1】：哈希
 *      做这题，是因为它是今天的每日一题中^^，赚币-ing，争取早日获得力扣电脑包；
 *      看到条件：
 *          1 <= nums.length <= 100
 *          1 <= nums[i] <= 100
 *      立马放弃了 STL 库；
 *      转用数组（且用 static），手动哈希；
 *      同频率，用个计数；出现新的大频率，计数重置为 1；
 * 
 *      + 分析：
 *          + 时间复杂度：O(n)
 *          + 空间复杂度：O(1)，也算 O(n) 吧
 *      + rank:
 *          + 时间效率：0 ms, 击败 100%
 *          + 空间效率：22.20 MB, 击败 100%
 */

#include <vector>
using std::vector;

#include <unordered_map>
using std::unordered_map;
#define um unordered_map
#define MAXLEN 101

class Solution {
private:
    // 答题，不用担心线程安全、维护性差（被多处调用）等问题
    static int arr[MAXLEN];
public:
    int maxFrequencyElements(vector<int>& nums) {
        
        for (int& e : arr)
            e = 0;

        int max_fre = -1;
        int max_fre_cnt = 0;
        for (auto& e : nums) {
            
            if (++arr[e] > max_fre) {
                
                max_fre = arr[e];
                max_fre_cnt = 1;
            }
            else if (arr[e] == max_fre)
                ++max_fre_cnt;
        }
        return max_fre * max_fre_cnt;
    }
};
int Solution::arr[] = {};