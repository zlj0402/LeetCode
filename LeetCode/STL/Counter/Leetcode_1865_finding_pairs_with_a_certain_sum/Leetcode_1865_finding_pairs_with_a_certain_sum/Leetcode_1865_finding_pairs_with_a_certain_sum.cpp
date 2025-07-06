/**
* @brief: Leetcode_1865_找出和为指定值的下标对
* @link: https://leetcode.cn/problems/finding-pairs-with-a-certain-sum/description
* @author: liangj.zhang
* @date: 6/7/2025
* 
* @Difficulty: Medium
* 
* @Label: Hash、Two Pointers(能做，但不推荐)
* 
* @Again(worthy 0~5): 2
* 
* @brief content: 
*       + 从 nums1[] 和 nums2[] 中，找到 nums1[i] + nums2[j] == tot 的对数； 
*       + nums2[] 中的数会修改；
* 
* @condition: nums2 的长度比 nums1 的长度，大多数时候要长，nums1 在每个 cases 中的长度固定；
* 
* @thoughts:
* 【1】双指针，这是我第一眼想到的思路；
*       + 两个 map 存储两个数组中，数字的频率；
*       + 一个从最小处开始遍历，一个从最大处遍历；
*       + 除了 tot 比最小值小，或者比最大值大的情况，不考虑；
*       + 其他时候：
*           + it1 + it2 > tot, it2 往左移动
*           + it1 + it2 < tot, it1 往右移动
*           + it1 + it2 == tot, 记录 & 其中任意一指针，往它自己的下个位置移动
*       + 分析：
*           时间复杂度：count -> 最坏时间复杂度是 O(K1 + K2)，而 K1 ≤ M，K2 ≤ N, 初始化的插入：O(MlogM) + O(NlogN)，查找 O(logM) / O(logN)
*           空间复杂度：O(M) + O(N)
* 
*       + rank:
*           时间效率：2680 ms, 击败 5.56%
*           空间效率：79.89 MB, 击败 91.67%
* 
* 【2】Hash, 这是我看到提示 1，提示我只遍历 nums1 当中的数，想到的；
*       也确实应该这样做；
*       我想，确定 nums1[] 中的一个数，就能去 nums2[] hash 查找；那很方便，还用什么双指针；
*       + 两个 unordered_map 存储两个数组中，数字的频率；
*       + 遍历 nums1 (因为 nums1 的长度固定，且小)，遍历到的值，就相当于确定了一个数 num1，只要去另一边看看，有没有 tot - num1 就可以了；
*       
*       + 分析：
*           时间复杂度：count -> O(K1), 最多 O(K1) 次（K1 ≤ M）; 初始化的插入：O(M) + O(N), 查找 O(1)
*           空间复杂度：O(M) + O(N)
* 
*       + rank:
*           时间效率：75 ms, 击败 81.48%
*           空间效率：78.68 MB, 击败 94.44%
*/


#include <vector>
using std::vector;

// 【2】
#include <unordered_map>
using std::unordered_map;

#define um unordered_map

class FindSumPairs {
private:
    vector<int>* nums1, * nums2;
    um<int, int> rec1, rec2;

public:
    FindSumPairs(vector<int>& nums1, vector<int>& nums2) {

        this->nums1 = &nums1;
        this->nums2 = &nums2;

        for (auto& e : nums1)
            ++rec1[e];
        for (auto& e : nums2)
            ++rec2[e];
    }

    void add(int index, int val) {

        int e = (*nums2)[index];
        --rec2[e];
       (*nums2)[index] += val;
       ++rec2[e + val];
    }

    int count(int tot) {

        int ret = 0;
        for (auto& it : rec1) {

            int other = tot - it.first;
            if (rec2.find(other) != rec2.end())
                ret += it.second * (rec2[other]);
        }

        return ret;
    }
};

/**
 * Your FindSumPairs object will be instantiated and called as such:
 * FindSumPairs* obj = new FindSumPairs(nums1, nums2);
 * obj->add(index,val);
 * int param_2 = obj->count(tot);
 */


// 【1】
/*
#include <map>
using std::map;


class FindSumPairs {
private:
    vector<int>* nums1, * nums2;
    map<int, int> rec1, rec2;

    bool isOutOfRange(int tot) {

        int min1 = rec1.begin()->first;
        int max1 = rec1.rbegin()->first;
        int min2 = rec2.begin()->first;
        int max2 = rec2.rbegin()->first;

        return min1 + min2 > tot || max1 + max2 < tot ? true : false;
    }
public:
    FindSumPairs(vector<int>& nums1, vector<int>& nums2) {

        this->nums1 = &nums1;
        this->nums2 = &nums2;

        for (auto& e : nums1)
            ++rec1[e];
        for (auto& e : nums2)
            ++rec2[e];
    }

    void add(int index, int val) {

        int e = (*nums2)[index];
        if (--rec2[e] == 0)
            rec2.erase(e);

        (*nums2)[index] += val;
        ++rec2[e + val];
    }

    int count(int tot) {

        if (isOutOfRange(tot))
            return 0;
        
        int ret = 0;
        auto it1 = rec1.begin();
        auto it2 = rec2.rbegin();

        while (it1 != rec1.end() && it2 != rec2.rend()) {

            if (it1->first + it2->first > tot)
                it2++;
            else if (it1->first + it2->first < tot)
                it1++;
            else {

                ret += it1->second * it2->second;
                it1++;
            }
        }

        return ret;
    }
};*/

/**
 * Your FindSumPairs object will be instantiated and called as such:
 * FindSumPairs* obj = new FindSumPairs(nums1, nums2);
 * obj->add(index,val);
 * int param_2 = obj->count(tot);
 */