/**
 * @brief: Leetcode_2187_完成旅途的最少时间
 * @link: https://leetcode.cn/problems/minimum-time-to-complete-trips/description/
 * @author: liangj.zhang
 * @date: 19/9/2025
 * 
 * @Difficulty: Medium
 * 
 * @Label: Binary Search
 * 
 * @Retrospect(worthy 1 - 5): 3
 * 
 * @thoughts:
 *  + 【思路 1】：二分查找（判定型）
 *      + 时间 1 份 1 份 的增加，cntTrips 也是单调的变大，直到刚好 >= totalTrips；
 *      + 所以，可以使用二分查找；
 *      + 确定查找范围：
 *          + 可以把 time 数组中，除 min_time 的其他元素当成无穷大来看，合理的范围就能确定：
 *          + 二分查找的范围，我觉得应该是 [min(time), min(time) * totalTrips]
 * 
 *      + 分析：
 *          + 时间复杂度：O(n * log(min_time * totalTrips))
 *          + 空间复杂度：O(1)
 * 
 *      + rank:
 *          + 时间效率：55 ms, 击败 69.95%
 *          + 空间效率：96.16 MB, 击败 79.66%
 */

#include <iostream>
#include <vector>
using std::cout;
using std::endl;
using std::vector;

#include <algorithm>

class Solution {

// private:
//     static long long sum(vector<int>& nums, long long& dividend, int& totalTrips) {

//         long long cnt = 0;
//         for (auto& e : nums) {
            
//             cnt += dividend / e;
//             if (cnt >= totalTrips) return cnt;
//         }
//         return cnt;
//     }

public:
    // 二分查找的范围，我觉得应该是 [min(time), min(time) * totalTrips]
    // 可以把 time 数组中，其他元素当成无穷大来看，上面的范围就是合理的范围结果；
    long long minimumTime(vector<int>& time, int totalTrips) {

        if (time.size() == 1) return 1LL * time[0] * totalTrips;
        
        int min_time = *std::min_element(time.begin(), time.end());
        long long l(min_time), r = (long long)min_time * totalTrips;

        auto sum = [&](long long dividend) {
            
            long long cnt = 0;
            for (int e : time) {
                cnt += dividend / e;
                if (cnt >= totalTrips) return cnt;
            }
            return cnt;
        };

        while (l <= r) {

            long long mid = (l + r) >> 1;
            if (sum(mid) < totalTrips)
                l = mid + 1;
            else
                r = mid - 1;
        }

        return l;
    }
};

int main() {

    // vector<int> time = {1, 2, 3};
    vector<int> time = {10000};
    // int totalTrips = 5;
    int totalTrips = 10000000;

    cout << Solution().minimumTime(time, totalTrips) << endl;
}