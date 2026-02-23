/**
 * @brief: Leetcode_2698_求一个整数的惩罚数
 * @link: https://leetcode.cn/problems/find-the-punishment-number-of-an-integer/description/
 * @author: liangj.zhang
 * @date: 23/2/2026
 * 
 * @Difficulty: Medium
 * 
 * @Label: binary_search & backtracking
 * 
 * @Retrospect(worthy 1 - 5): 4
 * 
 * @thoughts:
 *  + 【思路 1】：回溯，增量式地向全局变量当中添加 数，和其对应的惩罚数（甚至忽略题目给的 n 对应的惩罚数，只记录节点）
 *          rec[lowerIdx].first == n ? rec[lowerIdx].second : rec[lowerIdx - 1].second;
 *      如果已经记录到的最大值 maxN 比当前 n 大，可以直接通过上面的方式得到；
 *          vector<std::pair<int, int>> Solution::rec{{0, 0}};
 *      我初始化时先加了一个 {0，0}，这样不至于会使得 rec[lowerIdx - 1].second 访问到一个错误的 -1 位置的可能；
 *      
 *      比最大n小，就直接从惩罚数map中找到n的位置取值
 *      比最大n大，取 map 的最后一位值，从 maxN + 1 开始到 newN 判断每个数的是否符合条件。
 * 
 *      然后回到判断一个数是否能拆分，达成子结果之和是一样的。
 *      位数的间隙是，回溯划分的边界。
 * 
 *      + 分析:
 *          + 时间复杂度：增量式求惩罚数 O(maxN)[这里不是一个 case 的复杂度分析]
 *                          求和 O(k): std::accumulate(path.begin(), path.end(), 0); k 是最坏情况
 *                          分割次数： 2^(k - 1), k 是平方的位数 -> 2^k
 *                          T(isValid(i)) = O(k * 2^k)
 *                          
 *                          k 实际是一个数 i 的 logi，重新得上面的
 *                          分割次数: 2^k = 2^O(logi) = i^O(1) -> 指数和对数互逆
 *                          求和：O(k) = O(logi)
 *                          T(isValid(i)) = O(i * logi)
 * 
 *                          T(n) = n∑(i = 1) O(ilogi) ≈ O(n^2 * logn)
 *                              如果算复杂度，这个 n 是所有 cases 最大 n;
 *          + 空间复杂度：dfs: O(k), path: O(k), 局部变量 squaresS: O(k) -> k 最坏是 n
 *                      static vector<pair<int,int>> rec; -> O(N) -> N 全局 cases 最大 n
 *                      summary: O(n)
 *      + rank:
 *          + 时间效率：3 ms, 击败 73.18% -> 这题有些奇怪，我的时间效率已经达到最左侧柱子的顶峰了，只算我击败 73.18%，不应该是 100% 吗
 *          + 空间效率：11.46 MB, 击败 15.90%
 */
#include <iostream>
#include <vector>
#include <string>
#include <numeric>
using std::string;
using std::vector;
using std::cout;
using std::endl;

class Solution {
private:
    static vector<std::pair<int, int>> rec;  // pair<n, 惩罚数>
    static int maxN;

    static int lower_bound(vector<std::pair<int, int>>& rec, int target);

    bool isValid(int i) {

        string squaresS = std::to_string(i * i);
        vector<int> path;
        bool valid = false;

        auto dfs = [&](this auto&& dfs, int idx) -> void {

            if (idx == squaresS.size()) {

                int sum = std::accumulate(path.begin(), path.end(), 0);
                if (sum == i) valid = true; 
                return;
            }

            if (valid) return;

            for (int j = idx; j < squaresS.size(); ++j) { 

                string sub_s = squaresS.substr(idx, j - idx + 1);
                path.push_back(stoi(sub_s));
                dfs(j + 1);
                path.pop_back();
            }
        };

        dfs(0);

        return valid;
    }

public:
    int punishmentNumber(int n) {
        
        // 比最大 n 小，取 rec 中 <= n 的最后一个位置
        if (n <= maxN) {

            int lowerIdx = lower_bound(rec, n);
            return rec[lowerIdx].first == n ? rec[lowerIdx].second : rec[lowerIdx - 1].second;
        }

        // 比最大 n 大，取 rec 中最后一个，然后从 maxN + 1 的位置到 newN 的判断
        // 并更改最大 maxN
        int pNum = rec[rec.size() - 1].second;

        for (int i = maxN + 1; i <= n; ++i) {

            // 判断一个数是否能组合，到其本身
            if (isValid(i)) {
                
                pNum += i * i;  // 原来错误的写法，放到了下一行的后面
                rec.push_back({i, pNum});   // 每一个确定的节点，也 push 进去，避免后续没找到，或者需要添加逻辑查找
                // cout << i << ", " << pNum << endl;
            }
        }

        // rec.push_back({n, pNum});    // 这里可以省掉，这样就只记录惩罚数的节点
        maxN = n;

        return pNum;
    }
};

vector<std::pair<int, int>> Solution::rec{{0, 0}};
int Solution::maxN = 0;

int Solution::lower_bound(vector<std::pair<int, int>>& rec, int target) {

    int left(0), right(rec.size() - 1);
    while (left <= right) {

        int mid = left + (right - left) / 2;
        if (rec[mid].first < target)
            left = mid + 1;
        else
            right = mid - 1;
    }
    
    return left;    // if nums[n - 1] < target, left -> n: equal to length of nums[]
}

int main() {

    int n = 37;

    cout << Solution().punishmentNumber(n) << endl;
    
}