/**
 * @brief: Leetcode_2517_礼盒的最大甜蜜度
 * @link: https://leetcode.cn/problems/maximum-tastiness-of-candy-basket/description/
 * @author: liangj.zhang
 * @date: 22/9/2025
 * 
 * @Difficulty: Medium (Score: 2021)
 * 
 * @Label: Binary Search
 * 
 * @Retrospect(worthy 1 - 5): 4
 * 
 * @thoughts:
 *  + 【思路 1】：二分查找猜答案
 *      今天这次，还是看的题解；昨天看题解前面一下就理解了，今天是题解描述没懂，看了代码理解了；虽然也是一次性写出来了；
 *      因为在刷二分题，能知道甜度（也是 mid 值所指代的），肯定是二分单调性的关键项；
 *      但是，想不出来，if 条件判定，如何构成 单调的公式；自然也想不到下一步 [l, r] 的范围；
 * 
 *      看了代码之后，有所理解：
 *      排完序之后，后面的某个糖果与前面某个糖果甜度的差 d，是我们要考虑的；
 *      有序的数组中，取出 3 个数，能达到 sweety 值最小，且是 最小中的最大；
 * 
 *      选定 两个糖果的差值 d，越小，能满足差值为 d 的组数越多；
 *      选定 两个糖果的差值 d，越大，能满足差值为 d 的组数越小；
 *      达到 d 再加 1，就没有能满足的组，就是我们要求的答案； -- 看到这，心中是否有了此题 二分查找的单调性
 *      
 *      就是在排序的数组中划分段，k 个数都是在数组中，就有 k - 1 个段；
 *      [5, 13, 21] 能达到的差值效果，我 [1, 13, 21] [2, 13, 21] 也能达到，
 *      段的划分起点，干脆选择最小值开始； 满足差值为 d 的个数（包括起点），能否 <= k，就是 if 判定条件；
 * 
 *      + 分析：
 *          + 时间复杂度：排序 O(nlogn) + 二分查找 O(nlogU); U => (max(price) - min(price)) / (k - 1) 
 *          + 空间复杂度：O(1)
 *      + rank:
 *          + 时间效率：48 ms, 击败 86.34%
 *          + 空间效率：51.05 MB, 击败 80.18% 
 */
#include <vector>
#include <iostream>
using std::cout;
using std::endl;
using std::vector;

#include <algorithm>

class Solution {
public:
    int maximumTastiness(vector<int>& price, int k) {

        std::sort(price.begin(), price.end(), std::less<>());
        
        auto check = [&](int d) {

            int cnt = 1;
            int pre = price[0];
            for (auto& p : price) {

                if (p - pre < d)
                    continue;
                ++cnt;
                pre = p;
            }

            return cnt;
        };

        int l(0), r((price[price.size() - 1] - price[0]) / (k - 1) + 1);
        while (l <= r) {

            int mid = l + (r - l) / 2;
            if (check(mid) >= k) 
                l = mid + 1;
            else 
                r = mid - 1;
        }

        return r;
    }
};

int main() {

    vector<int> price = {13,5,1,8,21,2};
    int k = 3;

    cout << Solution().maximumTastiness(price, k) << endl;
    
}