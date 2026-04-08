/**
 * @brief: Leetcode_198_打家劫舍
 * @link: https://leetcode.cn/problems/house-robber/description/
 * @author: liangj.zhang
 * @date: 8/4/2026
 * 
 * @Difficulty: Medium
 * 
 * @Label: Dynamic Programming
 * 
 * @Retrospect(worthy 1 - 5): 5 (classic)
 * 
 * @thoughts:
 *  + 【思路 1】：回溯
 *      按正常回溯的过程来，条件上加上判断上一次的选择的位置，不是相邻的就可以；
 *      能解决问题，但超时，case 中数据比较长，不适合时间复杂度为指数级的回溯；
 *  + 【思路 2】：纯递归写法
 *      递归，解决的问题是，需要当前情况考虑，下一次考虑相同的事情；
 *          这题符合
 *      其次，还要想好递归的边界条件；
 *          这是递归的第二要素，第一是上面的：一次做什么；
 *      ---
 *      1. 当次 idx，偷 idx 家，那么偷值是 f(idx - 2) + nums[idx]
 *                  不偷 idx 家，那么偷值是 f(idx - 1)
 *      2. 边界条件：
 *          f(1) 怎么算：f(1) = max( f(-1) + nums[1], f(0) ), 只有 nums[0] 家，没有 nums[-1] 家，就是偷不到，让 f(-1) = 0
 *          f(0) 怎么算：f(0) = max( f(-2) + nums[0], f(-1) ), 同样没有 nums[-2] 的家，让 nums[-2] = 0;
 *          递归这里，让 idx < 0 时，就返回值；
 *      ---
 *      return std::max(dfs(idx - 1), dfs(idx - 2) + nums[idx]);
 *          => dfs(idx - 1)，就相当于这次的没有选
 *          => dfs(idx - 2) + nums[idx]，就相当于这次选了；
 *      但递归下去，也是考虑到所有情况，时间复杂度，完全同 回溯；
 *      也会超时；
 */


#include <vector>
using std::vector;

class Solution {
public:
    int rob(vector<int>& nums) {    // 1 <= len(nums) <= 100
        int prev2 = 0;  // f(-2)
        int prev1 = 0;  // f(-1)
        //                                                                [1,2,3,1]
        // f(0) = max(f(-2) + nums[0], f(-1)) = max(0 + nums[0], 0)     = max(1, 0) = 1
        // f(1) = max(f(-1) + nums[1], f(0)) = max(0 + nums[1], f(0))   = max(2, 1) = 2
        // f(2) = max(f(0) + nums[2], f(1)) = max(f(0) + nums[2], f(1)) = max(1 + 3, 2) = 4
        // f(3) = max(f(1) + nums[3], f(2))                             = max(2 + 1, 4) = 4
        for (int i = 0; i < nums.size(); ++i) {
            int cur = std::max(prev2 + nums[i], prev1);
            prev2 = prev1;
            prev1 = cur;
        }
        return prev1;
    }
};

int main() {
    vector<int> nums {1,2,3,1};
    Solution().rob(nums);
}

// class Solution {
// public:
//     int rob(vector<int>& nums) {
//         int n = nums.size();
//         vector<int> rec(n + 2, 0);
//         for (int i = 0; i < n; ++i) {
//             rec[i + 2] = std::max(rec[i + 1], rec[i] + nums[i]);
//         }
//         return rec[n + 1];
//     }
// };

// class Solution {
// public:
//     int rob(vector<int>& nums) {
//         int n = nums.size();
//         vector<int> rec(n, -1);

//         auto dfs = [&](this auto&& dfs, int idx) -> int {
//             if (idx < 0) return 0;
            
//             if (rec[idx] >= 0) return rec[idx];

//             rec[idx] = std::max(dfs(idx - 1), dfs(idx - 2) + nums[idx]);
            
//             return rec[idx];
//         };

//         return dfs(n - 1);
//     }
// };

// 【思路 2】：纯递归写法
// 纯递归写法，实质也是回溯的时间复杂度，递归到了各个分支
class Solution {
public:
    int rob(vector<int>& nums) {
        int n = nums.size();
        vector<int> rec(n, -1);

        auto dfs = [&](this auto&& dfs, int idx) -> int {
            if (idx < 0) return 0;
            // dfs(idx - 1) -> 相当于回溯过程中的没选
            // dfs(idx - 2) -> 相当于回溯过程中的选
            // 这种递归就相当于回溯，时间复杂度是指数级的，会超时
            return std::max(dfs(idx - 1), dfs(idx - 2) + nums[idx]);
        };

        return dfs(n - 1);
    }
};

// 【思路 1】：回溯
// 回溯 -- 能解，但超时，不可行
class Solution {
public:
    int rob(vector<int>& nums) {
        int n = nums.size();
        vector<bool> visit(n, false);
        int maxSum = -1;

        auto dfs = [&](this auto&& dfs, int idx, int sum) -> void {

            if (idx >= n) {
                if (sum > maxSum) maxSum = sum;
                return;
            }

            // 选
            if ((idx > 0 && !visit[idx - 1]) || (idx == 0 && !visit[0])) {
                visit[idx] = true;
                dfs(idx + 1, sum + nums[idx]);
                visit[idx] = false;
            }
            
            dfs(idx + 1, sum);
        };

        dfs(0, 0);

        return maxSum;
    }
};

