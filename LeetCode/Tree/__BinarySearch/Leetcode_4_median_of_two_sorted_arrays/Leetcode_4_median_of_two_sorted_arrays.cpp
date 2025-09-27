/**
 * @brief: Leetcode_4_寻找两个正序数组的中位数
 * @link: https://leetcode.cn/problems/median-of-two-sorted-arrays/description/
 * @author: liangj.zhang
 * @date: 27/9/2025
 * 
 * @Difficulty: Hard
 * 
 * @Label: Binary Search、Two Pointers
 * 
 * @Retrospect(worthy 1 - 5): 5
 * 
 * @thoughts:
 *  这题可以用双指针，且先理解双指针，更容易理解二分的条件；
 *  不过双指针的做法，是 O(n) 的做法，不满足题目的条件 O(logn) 时间复杂度；
 *  两种做法都是，看了题解的，双指针的做法秒懂，二分其次；
 *  + 【思路 1】：双指针
 *      这次没写，留以后写；
 *  + 【思路 2】：二分查找
 *      + 写法一：最开始明白结束的划分状态后（snums[smid + 1] <= lnums[lmid + 1] && lnums[lmid] <= snums[smid + 1]），自己首先写的；
 *                  有点二分猜答案的味道；
 *      + 写法二：求取最后一个让 snums[smid] <= lnums[lmid + 1] 的位置；
 *          [-1, -2]
 *          [ 8,  9, 10]
 *          总共 5 个数，让前半部分的划分达到 (m + n + 1) / 2，在长度和为奇数时，让左边多一个数；
 *          snums[] 和 lnums[] 的组合有很多，
 *              + s: 前 0 个，l: 前 3 个；
 *              + s: 前 1 个，l: 前 2 个；      nums[0] < nums[1 + 1] => -1 < 9
 *              + ...
 *              + s: 前 2 个，l: 前 1 个；      nums[1] < nums[0 + 1] => -2 < 8
 *          有很多个，满足 snums[smid] <= lnums[lmid + 1]，但只有 idx = 1 时，是 snums[] 中最后一个满足的位置；
 *      + 分析：
 *          + 时间复杂度：O(logn)
 *          + 空间复杂度：O(1)
 *      + rank:
 *          + 写法一：
 *              + 时间效率：0 ms, 击败 100%
 *              + 空间效率：92.96 MB, 击败 68.64%
 *          + 写法二：
 *              + 时间效率：0 ms, 击败 100%
 *              + 空间效率：92.77 MB, 击败 99.22%
 */

#include <iostream>
#include <vector>
using std::cout;
using std::endl;
using std::vector;

// 【思路 2】：写法 2，类似 lower_bound / upper_bound 那种写法；
class Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        
        vector<int>& snums = nums1.size() <= nums2.size() ? nums1 : nums2;
        vector<int>& lnums = nums1.size() <= nums2.size() ? nums2 : nums1;
        int slen(snums.size()), llen(lnums.size());

        int half = (slen + llen + 1) / 2;
        int l(0), r(slen - 1);
        int smid(0), lmid(0);
        while (l <= r) {

            smid = l + (r - l) / 2;
            lmid = half - (smid + 1) - 1;
            if (snums[smid] <= lnums[lmid + 1])
                l = smid + 1;
            else
                r = smid - 1; 
        }
        smid = r;
        lmid = half - (smid + 1) - 1;
        //cout << "smid: " << r << ", lmid: " << lmid << endl;

        int sleft = smid == -1 ? INT_MIN : snums[smid];
        int sright = smid + 1 >= slen ? INT_MAX : snums[smid + 1];
        int lleft = lmid == -1 ? INT_MIN : lnums[lmid];
        int lright = lmid + 1 >= llen ? INT_MAX : lnums[lmid + 1];
        int left_max = std::max(sleft, lleft);
        int right_min = std::min(sright, lright);
        double res = (slen + llen) % 2 ? left_max * 1.0 : (left_max + right_min) / 2.0;

        return res;
    }
};

// 【思路 2】：写法 1
//          snums -> short nums[], lnums -> long nums[]
//          在明白双指针的过程后，能够意识到二分能达到效果，但是没弄清真正的二分条件思维：(snums[smid] <= lnums[lmid + 1])；（看到这，还不能明白，继续看后面）
//          只弄清楚了 snums[smid + 1] <= lnums[lmid + 1] && lnums[lmid] <= snums[smid + 1] 的状态；
//          虽然这么写，最终写出来了，但被各种边界条件耽误了一整个白天；（我这样写，像是二分猜答案）
//          真正的二分，意识到的应该是，求取最后一个让 snums[smid] <= lnums[lmid + 1] 的位置；

/*
class Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        
        vector<int>& snums = nums1.size() <= nums2.size() ? nums1 : nums2;
        vector<int>& lnums = nums1.size() <= nums2.size() ? nums2 : nums1;
        int slen(snums.size()), llen(lnums.size());

        if (slen == 0) return llen % 2 ? lnums[llen / 2] : (lnums[(llen - 1) / 2] + lnums[(llen - 1) / 2 + 1]) / 2.0;
        if (llen == 0) return slen % 2 ? snums[slen / 2] : (snums[(slen - 1) / 2] + snums[(slen - 1) / 2 + 1]) / 2.0;

        int sl(0), sr(slen - 1), ll(0), lr(llen - 1);
        int half = (slen + llen + 1) / 2;
        int lmid, smid;
        while (1) {
            smid = sr == -1 ? -1 : sl + (sr - sl) / 2;
            lmid = half - (smid + 1) - 1;
            if (smid == -1) {
                if (lnums[lmid] <= snums[smid + 1])
                    break;
            }
            else {     // smid < slen
                if (smid == slen - 1 && snums[smid] <= lnums[lmid + 1])
                    break;
                else {
                    if (snums[smid] <= lnums[lmid + 1]) {
                        if (lmid == -1 || lnums[lmid] <= snums[smid + 1])
                            break;
                        else
                            sl = smid + 1;
                    }
                    else {
                        sr = smid - 1;
                    }
                }
            }
        }

        //cout << "smid: " << smid << ", lmid: " << lmid << endl;
        double res = 0;
        if ((slen + llen) % 2) {
            if (smid != -1)
                res = std::max(snums[smid], lnums[lmid]) * 1.0;
            else
                res = lnums[lmid] * 1.0;
        }
        else {
            int left_max, right_min;
            // int left_max = lmid > -1 ? std::max(snums[smid], lnums[lmid]) : snums[smid];
            // int right_min = lmid < llen - 1 ? std::min(snums[smid + 1], lnums[lmid + 1]) : snums[smid + 1];
            if (lmid == -1)
                right_min = lnums[lmid + 1];
            else if (lmid == llen - 1) 
                right_min = snums[smid + 1];
            else 
                right_min = smid + 1 < slen ? std::min(snums[smid + 1], lnums[lmid + 1]) : lnums[lmid + 1];

            if (smid == -1)
                left_max = lnums[lmid];
            else if (smid == slen - 1 && smid + 1 == half)
                left_max = snums[smid];
            else
                left_max = lmid < llen ? std::max(snums[smid], lnums[lmid]) : snums[smid];

            res = (left_max + right_min) * 1.0 / 2;
        }
        return res;
    }
};
*/

int main() {

    vector<int> nums1 = {1};
    vector<int> nums2 = {2, 3, 4};

    // vector<int> nums1 = {3};
    // vector<int> nums2 = {-2, -1};

    // vector<int> nums1 = {1, 3, 5, 5};
    // // vector<int> nums2 = {-3, -2, -1, 0};
    // // vector<int> nums2 = {6, 7, 8, 9};
    // vector<int> nums2 = {0, 1, 2, 4};

    // vector<int> nums1 = {1, 3};
    // vector<int> nums2 = {2};

    // vector<int> nums1 = {-10, -9, -8};
    // vector<int> nums2 = {1, 2};
    cout << Solution().findMedianSortedArrays(nums1, nums2) << endl;
}