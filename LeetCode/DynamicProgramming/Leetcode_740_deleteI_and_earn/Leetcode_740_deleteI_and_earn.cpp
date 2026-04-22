/**
 * @brief: Leetcode_740_删除并获得点数
 * @link: https://leetcode.cn/problems/delete-and-earn/description/
 * @author: liangj.zhang
 * @date: 23/4/2026
 * 
 * @Difficulty: Medium
 * 
 * @Label: Dynamic Programming
 * 
 * @Retrospect(worthy 1 - 5):
 * 
 * @thougths:
 *  + 【思路 1 -- 写法 1】：动态规划，状态压缩 -- linkedlist 写法
 *      可惜的是，这题还是看了灵神的解析部分；
 *      最关键的一点没有解读出来：看示例 2，nums=[2,2,3,3,3,4]。如果我们选了一个等于 3 的数，那么所有等于 2 和等于 4 的数都被删除，也就是都不能选。
 *                              选了一个 3 后，剩下的 3 可以继续选。所以如果要选 3，所有的 3 都要选。
 *      这种「相邻数字不能都选」联想到 198. 打家劫舍
 *      ---
 *      看到这一点，我就知道了。
 *      好在我自己的写法，是解决了灵神的提问：如果值域更大，比如 nums[i]≤10^9，要怎么做？
 *      ---
 *      我的第一个写法是链表的形式；
 *          假设有数组：nums [1, 3, 5, 6, 6, 8] -- 顺序的，或者说排过序的数组
 *              整合后：arr  [1, 3, 5, 12, 8] -- 整合后的数组，也是顺序
 *      prev2 = 0, prev1 = arr[0] == 1;
 *      1. cur 从 1 开始，即第二个数，因为 nums.length >= 1
 *          prev1 指向的数 1，与 cur 指向的数 3 离得远，（可偷，打家劫舍的理解），加上
 *          偷完了，此时 prev1 应该指向了 cur，
 * 
 *          prev2 离 cur 肯定更远，（他原来在 prev1 的左边），prev2 可以直接使用 prev1 的值，（因为 prev1 已经是那个位置的最大值）
 *          为了好理解，模仿打家劫舍，偷完后，可以理解 prev2 此时指向 nums_i - 1 的位置（其实是空的）
 *          
 *          prev2 + arr[0] = 0 + 1 = 1, 指向 nums_i - 1 == 0
 *          prev1 + arr[1] = 1 + 3 = 4, 指向 nums_i = 1,
 *      2. cur 往后一位，即 2
 *          prev1 指向的数 3 与 cur 指向的数 5 离得远，
 *          prev2 直接继承 prev1 的值，
 *          prev1 此时可以直接偷 arr[2]，
 *          
 *          prev2 = prev1 = 4, 指向 nums_i - 1 == 1;
 *          prev1 = prev1 + arr[2] = 4 + 5 = 9, 指向 nums_i = 2,
 *      3. cur 往后一位，即 3
 *          prev1 指向的数 5，与 cur 指向的数 6 离得近，（5 和 6 相邻）
 *          curMax = std::max(prev2 + arr[3], prev1) = std::max(4 + 12, 9) = 16
 *  
 *          prev2 = prev1 == 9, 指向 nums_i - 1 = 5,
 *          prev1 = curMax == 16, 指向 nums_i = 6
 *      4. cur 往后一位，即 4
 *          prev1 指向的数 6，与 cur 指向的数 8，离得远，
 *          
 *          prev2 = prev1 = 16, 指向 nums_i = 6
 *          prev1 = prev1 + arr[4] = 16 + 8 = 24, 指向 nums_i = 8
 *      ---
 *      + 分析：
 *          + 时间复杂度：排序 O(nlogn) + 整合 O(n) + DP O(U), U 是整合后的个数
 *          + 空间复杂度：O(U)
 *      + rank:
 *          + 时间效率：0 ms, 击败 100% （多数时候是达不到 0 ms 的， 3/4 ms）
 *          + 空间效率：15.43 MB, 击败 58.49%
 */

#include <vector>
#include <iostream>
#include <algorithm>
#include <unordered_map>
using std::vector;
using std::unordered_map;

#define um unordered_map

class Solution {
public:
    int deleteAndEarn(vector<int>& nums) {
        um<int, int> rec;
        for (auto x : nums) rec[x] += x;

        vector<int> keys;
        for (auto& [k, _] : rec) keys.push_back(k);

        std::sort(keys.begin(), keys.end());
        int prev2 = 0, prev1 = rec[keys[0]];
        for (int i = 1; i < keys.size(); ++i) {
            int cur;
            if (keys[i] == keys[i - 1] + 1) {
                cur = std::max(prev2 + rec[keys[i]], prev1);
            } // keys[i] > keys[i - 1] + 1
            else {
                cur = prev1 + rec[keys[i]];
            }
            prev2 = prev1;
            prev1 = cur;
        }

        return prev1;
    }
};

class Solution {
public:
    int deleteAndEarn(vector<int>& nums) {
        std::sort(nums.begin(), nums.end());
        vector<int> values;
        vector<int> sums;

        for (int i = 0; i < nums.size(); ) {
            int val = nums[i];
            int sum = 0;
            while (i < nums.size() && nums[i] == val) {
                sum += val;
                i++;
            }
            values.push_back(val);
            sums.push_back(sum);
        }

        int prev2 = 0;
        int prev1 = sums[0];

        for (int i = 1; i < values.size(); ++i) {
            int cur;
            if (values[i] == values[i - 1] + 1) {
                cur = std::max(prev2 + sums[i], prev1);
            } else {
                cur = prev1 + sums[i];
            }
            prev2 = prev1;
            prev1 = cur;
        }

        return prev1;
    }
};

// 【思路 1 -- 写法 1】：动态规划，状态压缩 -- linkedlist 写法
class Solution {
private:
    struct Node {
        Node(int val = 0, Node *node = nullptr) : val(val), sum(0) {
            if (node != nullptr) {
                node->next = this;
            }
            next = nullptr;
        }
        int val;
        int sum;
        Node* next;
    };
public:
    int deleteAndEarn(vector<int>& nums) {
        std::sort(nums.begin(), nums.end());
        int size = nums.size();
        Node* head = new Node();    // 1 <= nums[i] <= 10^4
        Node* cur = new Node(nums[0], head);
        cur->sum += cur->val;
        for (int i = 1; i < size; ++i) {
            if (nums[i] != cur->val) {
                Node* node = new Node(nums[i], cur);
                cur = node;
            }
            cur->sum += cur->val;
        }

        // cur = head;
        // while (cur->next) {
        //     cur = cur->next;
        //     std::cout << cur->val << ", " << cur->sum << std::endl;
        // }

        Node* pNode2 = head, *pNode1 = head->next;
        int prev2 = 0, prev1 = pNode1->sum;
        while (pNode1->next) {
            cur = pNode1->next;
            int curMax;
            if (cur->val > pNode1->val + 1) {
                curMax = prev1 + cur->sum;
            } // 离得近: cur->val == pNode1->val + 1
            else {
                curMax = std::max(prev2 + cur->sum, prev1);
            }
            prev2 = prev1;
            prev1 = curMax;

            pNode2 = pNode1;
            pNode1 = cur;
        }

        return prev1;
    }
};

int main() {
    vector<int> nums {3,4,2};
    std::cout << Solution().deleteAndEarn(nums) << std::endl;
}