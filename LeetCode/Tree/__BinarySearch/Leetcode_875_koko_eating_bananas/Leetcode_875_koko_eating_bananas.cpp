/**
 * @brief: Leetcode_875_爱吃香蕉的珂珂
 * @link: https://leetcode.cn/problems/koko-eating-bananas/description/
 * @author: liangj.zhang
 * @date: 18/9/2025
 * 
 * @Difficulty: Medium
 * 
 * @Label: Binary Search
 * 
 * @Retrospect(worthy 1 - 5): 4
 * 
 * @thoughts:
 *  + 【思路 1】：二分查找
 *      第一次没想出来，看了灵神的题解...
 *      + 昨天做的是 Leetcode_275_h_index_ii，二分循环体里的判定条件，单调变换的是，不等式的右边；
 *      + 今天做的是 单调变换的是 不等式的左边；
 *      
 *      + 引用灵神的部分题解逻辑：
 *      + 如果珂珂能用 k=4 的速度吃掉所有香蕉，那么也能用更快的速度 k=5,6,⋯ 吃掉所有香蕉。
 *      + 如果珂珂不能用 k=3 的速度吃掉所有香蕉，那么也不能用更慢的速度 k=2,1,⋯ 吃掉所有香蕉。
 *      + 这种单调性意味着我们像 二分查找 那样，把答案 k 猜出来。
 *      + ------
 *      + 我们就是，取到一个速度，进行一次 ceil & sum 的求和；
 *      + 速度慢了，就取后半段中点的速度；
 *      + 速度快了，就去前半段中点的速度；
 *      + 然后就是确定速度的范围，我喜欢闭区间进行：
 *          + k = 1，是最低进行的速度；题目保证 n≤h ==> 1 <= h/n
 *          + k = max(piles)，是最快的速度；再快，必定不能满足 慢慢吃 的条件了；
 *      + ------
 *      + 还要明白一点，正整数运算，理论：⌈ k / p ⌉ = ⌊ (k - 1) / p ⌋ + 1
 *      + 计算机中，除法 /，就相当于 ⌊ ⌋，所以：⌈ k / p ⌉ = (k - 1) / p + 1
 * 
 *      + 分析：
 *          + 时间复杂度：找到最大值 O(logn); 速度 U, 每次求 ceil & sum => O(logU) * n
 *          + 空间复杂度：O(1)
 * 
 *      + rank:
 *          + 时间效率：4 ms, 击败 89.35%
 *          + 空间效率：22.35 MB, 击败 88.95%
 */

#include <iostream>
#include <vector>
using std::cout;
using std::endl;
using std::vector;

#include <algorithm>

// 【思路 1】：二分查找
class Solution {

private:
    long long sum(vector<int>& nums, int divisor) { // 以前错误的写法：改了 cnt 类型为 long long，却没有改返回类型；疑惑了好半天

        long long cnt = 0;
        for (auto& e : nums)
            cnt += (e - 1) / divisor;
        return cnt;
    }

public:
    int minEatingSpeed(vector<int>& piles, int h) {
        
        int size = piles.size();

        int l(1), r(*std::max_element(piles.begin(), piles.end()));
        while (l <= r) {

            int mid = l + (r - l) / 2;
            // sum > h - size => mid 取小了 => l = mid + 1
            // sum <= h - size => mid 取大了 => r = mid - 1
            if (sum(piles, mid) > h - size)
                l = mid + 1;
            else
                r = mid - 1;

        }

        return l;
    }
};

int main() {

    // vector<int> piles = {3,6,7,11};
    vector<int> piles = {805306368,805306368,805306368};
    // int h = 8;
    int h = 1000000000;

    cout << Solution().minEatingSpeed(piles, h) << endl;
}