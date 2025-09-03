//
// Created by liangj.zhang on 14/6/2025
// 
// Difficulty: Medium
// 
// Label: Prefix Sum（前缀和，一般的线性前缀和就行，不会变动；变动的话，建议用 Binary Indexed Tree / Fenwick Tree，即二叉索引树）
// 
// 思路：
//  【1】.
//  我自己是想到了前缀和这个东西，但解决办法，还是用 O(n^2) 的枚举方式，不过差值是用前缀和数组来相减的；
//  【2】.
//  看了题解的优化方式：前缀和 + hash；原题解没看懂，不好意思 (︶︹︺)
//      看了题解下面，其他人贴的，没看懂，让 chatgpt 做的解释，如下：
//

//使用前缀和的方法可以解决这个问题，因为我们需要找到和为k的连续子数组的个数。通过计算前缀和，我们可以将问题转化为求解两个前缀和之差等于k的情况。
//
//假设数组的前缀和数组为prefixSum，其中prefixSum[i]表示从数组起始位置到第i个位置的元素之和。那么对于任意的两个下标i和j（i < j），如果prefixSum[j] - prefixSum[i] = k，即从第i个位置到第j个位置的元素之和等于k，那么说明从第i + 1个位置到第j个位置的连续子数组的和为k。
//
//通过遍历数组，计算每个位置的前缀和，并使用一个哈希表来存储每个前缀和出现的次数。在遍历的过程中，我们检查是否存在prefixSum[j] - k的前缀和，如果存在，说明从某个位置到当前位置的连续子数组的和为k，我们将对应的次数累加到结果中。
//
//这样，通过遍历一次数组，我们可以统计出和为k的连续子数组的个数，并且时间复杂度为O(n)，其中n为数组的长度。

// 自己再引导式的解释一下，让自己懂：
// unordered_map<pre_sum, cnt> 里面是什么？
// -> 换一种方式，以往 um 结构中记录的 key 是什么？
//      A: 某个位置到 nums 数组起始位置的，前缀和；
// 如果，当前位置前缀和 - k，在 um 中存在，
// 那么，说明当前位置 到 以往记录的某个位置，nums 中他们之间的和为 k；
// 
// 遇到个问题：为什么 cnt += rec[pre_sum - k]; ?
//  + value 是什么？
//  + 前缀和相同（位置不同）的个数
//  + 后面又有同 value 加进来，当 pre_sum - k (== value) 找过来；
//  + rec[value] == n 里面记录的是，pre_sum 为 value 的 n 个节点;
//  + 此时，多了一个找过来的 i 点，这个窗口，左边是不是多了 n 个可以落脚的位置；
//

#include <iostream>
#include <vector>
using std::vector;
using std::cout;
using std::endl;


// 【2】
#include <unordered_map>
#define um unordered_map
using std::unordered_map;

class Solution {

private:
        um<int, int> rec;
public:
    int subarraySum(vector<int>& nums, int k) {

        int size = nums.size();
        int cnt = 0;
        
        rec.clear();
        rec.insert({0, 1}); // key -> pre_sum; cur_pre_sum - k == 0 的话，含义特殊，是：当前位置到 0 位置的和为 k; 但 key 表示的应该是当前 [0, i] 之和，所以说有点特殊，也不是那么特殊

        int pre_sum = 0;
        for (int i = 0; i < size; ++i) {

            pre_sum += nums[i];
            if (rec.find(pre_sum - k) != rec.end()) {
                cnt += rec[pre_sum - k];
            }
            ++rec[pre_sum];
        }
        return cnt;
    }
};


// 【1】
/*
class Solution {
public:
    int subarraySum(vector<int>& nums, int k) {

        int cnt = 0;

        int size = nums.size();
        vector<int> res = vector<int>(size);

        res[0] = nums[0];
        for (int i = 1; i < size; i++) {
            res[i] = res[i - 1] + nums[i];
        }

        for (int i = 0; i < size; i++) {

            for (int j = 0; j <= i; j++) {

                // nums[j, i] 和
                int sum = j > 0 ? res[i] - res[j - 1] : res[i];
                if (sum == k)
                    cnt++;
            }
        }

        return cnt;
    }
};
*/

int main() {

    int k = 0;
    vector<int> nums = { 1,-1,0 };
    cout << (new Solution())->subarraySum(nums, k);
}