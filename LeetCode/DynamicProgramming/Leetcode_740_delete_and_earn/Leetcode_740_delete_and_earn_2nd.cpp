/**
 * @brief: Leetcode_740_删除并获得点数_2nd
 * @link: https://leetcode.cn/problems/delete-and-earn/description/
 * @author: liangj.zhang
 * @date: 2026/09/14
 * 
 * @Difficulty: Medium
 * 
 * @Label: Dynamic Programming
 * 
 * @Retrospect(worthy 1 - 5): 4
 * 
 * @thoughts:
 *  + 【思路 1】：动态规划
 *      获得某个数 x 的所有值 n * x；却不能获得 x - 1 的所有值，和 x + 1 的所有值；
 *          换句话说，能获得这个位置（排过序）的值，就不能选择相邻位置的值；这不就是 打家劫舍 的问题了，如此的熟悉；
 *      根据题目条件，可以知道数值在 10000 以内，可以用一个全局的数组表示；
 *      + 那为什么，中间穿插 0 不影响结果呢，不论是递归，记忆化搜索，DP，每个位置的值，都是当前最大的可能结果；
 *          既如此，穿插 0 不会影响最大结果；
 *      + 上面是宏观的理解，微观细节上，就是选取的过程，选与不选 0，到排序后的某个位置，值上面没有任何影响；
 *      + 不穿插 0，是解决不受值范围的限制，应该也是可行的；
 *          + prev2, prev1 所代表的是到某个值的最大结果；可以用两个分别记住他们所代表的位置的值，因为那是他们最后加上的位置值的总和；
 *          + 不，记一个 prev1 位置的就可以；
 *          + 下一个位置，求当前最大结果可以用来比较；
 *          以后可以试一试；
 *      ---
 *      + sizeof(vector_obj) 不是数组的大小，仅是容器大小；
 *      + 元素个数：vector_obj.size()
 *      + 大小：vector_obj.size() * n
 * 
 *      + 分析：
 *          + 时间复杂度：O(10000)[DP] + O(n)[遍历数组]
 *          + 空间复杂度：O(10001) ==> O(1)
 *      + rank:
 *          + 时间效率：0 ms, 击败 100%
 *          + 空间效率：15 MB, 击败 97.35%
 */

#include <vector>
#include <cstring>
using std::vector;

class Solution {
private:
    static vector<int> rec;
public:
    int deleteAndEarn(vector<int>& nums) {
        // std::memset(rec.data(), 0, sizeof(rec)); // X -> 不可行，获得的仅是容器的大小；
        std::memset(rec.data(), 0, rec.size() * sizeof(rec[0]));
        int max_ = 0;

        // for (int i = 1; i < 10001; ++i) {
        //     rec[i] = 0;
        // }

        for(auto x : nums) {
            if (max_ < x) max_ = x;
            rec[x] += x;
        }

        int prev2 = 0, prev1 = 0;
        for (int i = 1; i <= max_; ++i) {
            int tmp = prev1;
            prev1 = std::max(prev2 + rec[i], prev1);
            prev2 = tmp;
        }

        return prev1;
    }
};

vector<int> Solution::rec(10001, 0);