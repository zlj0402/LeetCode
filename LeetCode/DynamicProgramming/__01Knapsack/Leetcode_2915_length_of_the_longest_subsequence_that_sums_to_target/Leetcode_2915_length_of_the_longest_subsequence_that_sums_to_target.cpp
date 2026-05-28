/**
 * @brief: Leetcode_2915_和为目标值的最长子序列的长度
 * @link: https://leetcode.cn/problems/length-of-the-longest-subsequence-that-sums-to-target/description/
 * @author: liangj.zhang
 * @date: 26/5/2026
 * 
 * + updated:
 *  + 26/5/2026: 【思路 1/2.1/2.2】
 *  + 27/5/2026: 【思路 3 -- 写法 1】：动态规划 & 状态压缩
 *               【思路 3 -- 写法 2】：动态规划 & 状态压缩 -- 再进一步的剪枝优化
 *  + 28/5/2026: 【思路 4 -- 写法 1】：动态规划 & 状态压缩 -- 稀疏 DP -- 类似一个数组的做法；
 *               【思路 4 -- 写法 2】：动态规划 & 状态压缩 -- 真正的稀疏 DP -- 类似滚动数组的做法；
 * 
 * @Difficulty: Medium
 * 
 * @Label: Dynamic Programming & 01-Knapsack
 * 
 * @Retrospect(worthy 1 - 5): liangj.zhang
 * 
 * @thoughts:
 *  + 【思路 1】：回溯
 *      回溯 + dfs 的写法，的思路就是：
 *          选择当前的 idx 对应值之后，从 left 当中扣除；
 *          剩下的，交给下一次递归，做相同的事，就可以了；
 *      边界的处理就是：
 *          如果 left == 0 时，说明有一条 dfs 线，能获得目标和；返回 0，表示此次递归是有效的；
 *          idx >= n || left < 0，就说明这条 dfs 线，不能达到目标和，结束递归；
 *      dfs “归”之后，内容：
 *          回到某一节点之后，将该节点的所有返回情况进行比较，有合法的情况（即，能满足的情况），才选取合法的最大的 [序列长度 + 1（到达此节点，长度 + 1）]
 *          如果，一个合法的都没有，继续返回无效值；表明该条 dfs 线不符合情况；
 * 
 *      + 分析：
 *          + 时间复杂度：O(2^n)
 *          + 空间复杂度：O(n)
 *      ---
 *      超时
 * + 【思路 2】：动态规划 & 递推填表
 *      创建 arr[n + 1][target + 1],
 *      在 idx 处，t < nums[idx] 的范围，是 nums[idx] 值都比 t 大了，是不会有可能，从前面的值 + nums[idx] 到达 t == nums[idx] 的边界的；
 *          所以，t < nums[idx] => dp[idx][0-nums[idx]) 的情况，之前从前一轮 idx - 1 的状态组得到，没有变动；
 *      后面 t >= nums[idx] 的情况，除了从前一组状态继承过来，还多了 pre + nums[i] = t 的可能，从上一组 dp[idx - 1][t - nums[i]] 位置的可能结果再 + 1，与继承过来的进行比较；（当然，得前一个位置是有效情况）
 *      + 分析：
 *          + 时间复杂度：O(n * target)
 *          + 空间复杂度：O(n * target)
 *      + rank:
 *          + 时间效率：203 ms, 击败 35.82%
 *          + 空间效率：154.21 MB, 击败 32.50%
 * + 【思路 2 -- 写法 2】：动态规划 & 递推填表
 *      改变一下，默认的状态无效值，使得返回情况更简单；
 *      思路一点没变；
 * + 【思路 3 -- 写法 1】：动态规划 & 状态压缩
 *      能到填表的地步了，就能完成状态压缩；
 *      + 分析：
 *          + 时间复杂度：O(n * target)，还是可以减少 O(sum(nums)) 次遍历
 *          + 空间复杂度：O(target)
 *      + rank:
 *          + 时间效率：41 ms, 击败 83.69%
 *          + 空间效率：33.32 MB, 击败 72.94%
 * + 【思路 3 -- 写法 2】：动态规划 & 状态压缩 -- 再进一步的剪枝优化
 *      这是我将上面的写法提交上去之后，看了 top 第一个小柱子的代码，发现的；因为自己觉得已经尽可能达到最优了，怎么还不到 90%
 *      + 分析：
 *          + 时间复杂度：基于上面的【思路 3 -- 写法 1】，还能再少一点遍历次数；
 *          + 空间效率：O(target)
 *      + rank:
 *          + 时间效率：35 ms, 击败 98.15%
 *          + 空间效率：33.34 MB, 击败 68.77%
 *      ---------
 *      再细细回想，递推填表，还是 n + 1 组状态时，
 *      从 idx 1 开始，只有 t = nums[0] 的状态去更新一下就可以，后续的得到的都是默认状态；
 *         idx 2 开始，只有 t = nums[1], nums[0] + nums[1] 的状态去更新一下， t ∈ (nums[0], nums[0] + nums[1]) 之间的状态都不会有，直接继承默认就可以；
 *         idx 3 , 就不是简单的枚举了，在前一个结果之后，所有的状态基础都加上 nums[idx](当然要 < target)
 *      但可以将已有的状态放 map 当中，所以的情况 key(即 t)，加上 nums[i]，得到的状态 t_，如果已经存在，就跟 map[t] + 1 相比；
 *                                                                                   如果不存在，直接赋值 map[t] + 1
 *  + 【思路 4 -- 写法 1】：动态规划 & 状态压缩 -- 稀疏 DP -- 类似一个数组的做法；
 *      想清楚，我们其实始终，都是在前一个状态组的基础上，加上当前的 nums[i]，得到新的状态值；
 *          前一组有效状态位置的基础上，加上 nums[i]，只要 pre + nums[i] <= target 都可以处理；
 *          >>> 还要注意的一点是：我们需要从后往前遍历，从后面遍历，前面的状态对应的值，还没有在这一轮被改变；<<<
 *     + 分析：
 *          + 时间复杂度：O(n * (target/2) * log(target)) ==> O(n*target*log(target))
 *              因为我采取的是 map，可以按值的顺序进行遍历，查找插入都是 O(log(target))
 *              其次状态最坏，每次都产生前面完整一组的个数新状态（但也是控制在 target 之内），一组状态最多是 target+1 个；
 *              所以上面的，target 没有错；
 *              ---
 *              >>> 不过在 target 非常大的时候，nums.size() 比较小的时候，还是有优势的 <<<
 *          + 空间复杂度：O(target)
 *      + rank: 超时 -- 一开始确实觉得插入查找可能影响比较大，
 *                      但是，下面的写法二（类似滚动数组，这里使用 unordered_map）也是超时，我就有点怀疑了，插入查找都是 O(1)，尽然也没有过，
 *                      而且，差的就是最后一个 case，这个 case 就两个输入值，来回跑两次，都是最后一次 case，我怀疑它就是不想让 map 的方式通过；
 *  + 【思路 4 -- 写法 2】：动态规划 & 状态压缩 -- 真正的稀疏 DP -- 类似滚动数组的做法；
 *      也是基于前一组的状态，进行改变，
 *      这里使用拷贝一个 map，作为原来的状态组，有新的状态，将其和值，更新到"全局"的当中；
 *      + 分析：
 *          + 时间复杂度：O(n * target)
 *              每次拷贝 O(S_i)，总的：O(S_1 + S_2 + ... + S_n)，每一个值是一组状态，最坏一组 target 个，
 *              最坏是 O(n * target)
 *          + 空间复杂度：O(2 * target) == O(target)
 *      + rank: 超时 -- 不可思议，被做局了；
 */

#include <vector>
#include <iostream>
using std::vector;

// 【思路 4 -- 写法 2】：动态规划 & 状态压缩 -- 真正的稀疏 DP -- 类似滚动数组的做法；
// chat 给的稀疏 DP
class Solution {
public:
    int lengthOfLongestSubsequence(vector<int>& nums, int target) {

        unordered_map<int, int> dp;
        dp[0] = 0;

        for (int num : nums) {
            auto old = dp;
            for (auto &[sum, len] : old) {
                int ns = sum + num;
                if (ns > target) continue;
                dp[ns] = std::max(dp[ns], len + 1);
            }
        }
        return dp.count(target) ? dp[target] : -1;
    }
};

// 【思路 4 -- 写法 1】：动态规划 & 状态压缩 -- 稀疏 DP -- 类似一个数组的做法；
// 我以为的稀疏 DP
#include <unordered_map> // 状态的更新，必须是按顺序进行的；
using std::unordered_map; // 就像使用一个数组的压缩方式时，如果从前往后遍历是不对的（后面是需要依赖前面没有变换之前的值），需要从后往前；
#define um unordered_map
#include <map>
using std::map;
// 总复杂度接近：O(n * target * log(target))
class Solution {
public:
    int lengthOfLongestSubsequence(vector<int>& nums, int target) {
        int n = nums.size();

        map<int, int> dp;    // <status, status_val>
        dp[0] = 0;
        for (auto num : nums) {
            // for (auto &[k, v] : dp) {
            //     // 想象压缩成一个数组的过程，
            //     // [nums[i], target]，是依赖前一次集合的状态值，< nums[i] 直接继承原来的

            //     // 我们现在也从大到小遍历，考量 k + nums[i] <= target 时，
            // }
            for (auto it = dp.rbegin(); it != dp.rend(); ++it) {
                if (int cur = it->first + num; cur > target) continue;
                else {
                    // if (dp.find(cur) != dp.end()) {
                    //     dp[cur] = std::max(dp[cur], dp[it->first] + 1);
                    // }
                    // else {
                    //     dp[cur] = dp[it->first] + 1;
                    // }
                    // 可以简化为：因为 dp[cur] 不存在是，得到的值是 0
                    dp[cur] = std::max(dp[cur], dp[it->first] + 1);
                }
            } 
        }
        return dp.count(target) ? dp[target] : -1;
    }
};

// // 【思路 3 -- 写法 2】：动态规划 & 状态压缩 -- 再进一步的剪枝优化
// class Solution {
// public:
//     int lengthOfLongestSubsequence(vector<int>& nums, int target) {
//         int n = nums.size();

//         vector<int> dp(target + 1, -1);
//         dp[0] = 0;

//         int s = 0;
//         for (auto num : nums) {
//             s += num;
//             // 第一次只会遍历 1 次，非常 nice
//             // 第二次只会遍历 [nums[i], min(target, s)]
//             // for (int t = std::min(target, s); t >= num; --t) {
//             //     if (int pre = dp[t - num]; dp[t] == -1) {
//             //         if (pre != -1) dp[t] = pre + 1;
//             //     }
//             //     else {
//             //         // if (pre != -1) => 这里加或不加，都不影响了，理论上是可以加的，表示前面对应位置是有效的；
//             //         dp[t] = std::max(dp[t], pre + 1);
//             //     }
//             // }

//             // 进而可以简洁成下面这样：
//             for (int t = std::min(target, s); t >= num; --t) {
//                 if (int pre = dp[t - num]; pre != -1) {
//                     dp[t] = std::max(dp[t], pre + 1);
//                 }
//             }
//         }
//         return dp[target];
//     }
// };

// // 【思路 3 -- 写法 1】：动态规划 & 状态压缩
// class Solution {
// public:
//     int lengthOfLongestSubsequence(vector<int>& nums, int target) {
//         int n = nums.size();

//         vector<int> dp(target + 1, -1);
//         dp[0] = 0;

//         for (int i = 0; i < n; ++i) {
//             for (int t = target; t >= nums[i]; --t) {
//                 if (int pre = dp[t - nums[i]]; dp[t] == -1) {
//                     if (pre != -1) dp[t] = pre + 1;
//                 }
//                 else {
//                     dp[t] = std::max(dp[t], pre + 1);
//                 }
//             }
//         }

//         return dp[target];
//     }
// };

int main() {
    // vector<int> nums = {1, 2, 3, 4, 5};//4,1,3,2,1,5
    vector<int> nums = {4,1,3,2,1,5};
    // int target = 9;
    int target = 7;
    std::cout << Solution().lengthOfLongestSubsequence(nums, target) << std::endl;
}


// // 【思路 2 -- 写法 2】：动态规划 & 递推填表
// class Solution {
// public:
//     int lengthOfLongestSubsequence(vector<int>& nums, int target) {
//         int n = nums.size();

//         vector dp(n + 1, vector<int>(target + 1, -1));
//         dp[0][0] = 0;

//         for (int i = 0; i < n; ++i) {
//             for (int t = 0; t <= target; ++t) { // 原来错误的写法: int t = 1; => 要将 f[0] = 1 延续下去，后面直接能从 0 到 t 的结果，也能算一个情况；

//                 dp[i + 1][t] = dp[i][t];
//                 if (t >= nums[i]) {
//                     int pre = dp[i][t - nums[i]];
//                     if (pre > -1)
//                         dp[i + 1][t] = std::max(dp[i + 1][t], pre + 1);
//                 }
//             }
//         }

//         return dp[n][target]; 
//     }
// };

// // 【思路 2】：动态规划 & 递推填表
// class Solution {
// public:
//     int lengthOfLongestSubsequence(vector<int>& nums, int target) {
//         int n = nums.size();

//         vector dp(n + 1, vector<int>(target + 1, 0));
//         dp[0][0] = 1;

//         for (int i = 0; i < n; ++i) {
//             for (int t = 0; t <= target; ++t) { // 原来错误的写法: int t = 1; => 要将 f[0] = 1 延续下去，后面直接能从 0 到 t 的结果，也能算一个情况；
//                 // if (t < nums[i]) {
//                 //     dp[i + 1][t] = dp[i][t];
//                 // }
//                 // else if (int preStatus = dp[i][t - nums[i]]; preStatus == 0) {
//                 //     dp[i + 1][t] = dp[i][t];
//                 // }
//                 // else {
//                 //     // 错误写法：在没有选择从 dp[i][t - nums[i]] 过来之前，dp[i][t] 可能是有值的，如果比现在这种 preStatus + 1 情况大；那就漏掉了；
//                 //     // dp[i + 1][t] = std::max(dp[i + 1][t], preStatus + 1);
//                 // }

//                 dp[i + 1][t] = dp[i][t];
//                 if (t >= nums[i]) {
//                     int pre = dp[i][t - nums[i]];
//                     if (pre > 0)
//                         dp[i + 1][t] = std::max(dp[i + 1][t], pre + 1);
//                 }
//             }
//         }

//         return dp[n][target] == 0 ? -1 : dp[n][target] - 1; 
//     }
// };

// // 【思路 1】：回溯
// class Solution {
// public:
//     int lengthOfLongestSubsequence(vector<int>& nums, int target) {
//         int n = nums.size();

//         // 能达到 target，就在返回值后，递增个数；
//         auto dfs = [&](this auto&& dfs, int idx, int left) -> int {
//             if (left == 0) return 0;
//             if (idx >= n || left < 0) return -2;

//             int len = -2;
//             for (int i = idx; i < n; ++i) {
//                 int tmp = dfs(i + 1, left - nums[i]);
//                 if (tmp != -2)
//                     len = std::max(tmp + 1, len);
//             }

//             return len;
//         };

//         int ans = dfs(0, target);
//         return ans == -2 ? -1 : ans; 
//     }
// };