/**
 * @brief: Leetcode_22_括号生成
 * @link: https://leetcode.cn/problems/generate-parentheses/description/
 * @author: liangj.zhang
 * @date: 1/3/2026
 * 
 * @updated:
 *  + 4/3/2026: add 【思路 1 -- 写法 2】：回溯（选与不选）+ 剪枝 + dfs
 * 
 * @Difficulty: Medium
 * 
 * @Label: Backtracking & pruning & dfs
 * 
 * @Retrospect(worthy 1 - 5): 4
 * 
 * @thoughts:
 *  + 【思路 1 -- 写法 1】：回溯（枚举）
 *      我的思路是，什么时候是不合法的匹配？
 *          在某个位置 idx 上时，[0, idx] 范围内，如果右括号数 > 左括号数时，一定是不合法的，后面位置再怎么搭配，也不可能使得最后结果合法；
 *                                              如果右括号数 <= 左括号数，后面才有可能合法；
 *      就着这个想法，如果在 dfs 递归的时候，如果能够知道左右括号数，就好了；
 *      
 *      假设一开始 path[2 * n] 数组内都是右括号，我们回溯枚举 C(2n, n) 左括号的情况；
 *          右括号数怎么计算，是光脑子想难以一开始想到的，我先按照回溯的模板写下代码时，写到：
 *          for (int j = idx; j < 2 * n; ++j)，
 *          此次遍历，枚举 path[idx] 为左括号，下一次同为 idx 时遍历，枚举 j = idx + 1 时，idx 位置没有被选为左括号，那么就是多了右括号数，
 *          每次多的右括号数就是， j - idx
 *          把左括号数和右括号数，加在 dfs 参数上；每次就能知道左括号，和右括号数；
 * 
 *      + 分析：
 *          + 时间复杂度：生成合法括号的数量是第 n 个 卡特兰数：Cn ​= 1/(n+1) * ​C(2n, n) = (4^n) / (n^(3/2))
 *                       构造结果，每次 O(2*n) -> O(n)
 *                      + summary: Cn * O(n) = O(4^n / n^(1/2))
 *          + 空间复杂度：
 *              + 递归：O(n)
 *              + path: O(2*n)
 *              + summary：O(Cn * 2 * n) = O(Cn * n) = O(4^n / n^(1/2))
 *      + rank:
 *          + 时间效率：0 ms, 击败 100%
 *          + 空间效率：10.13 MB, 击败 90.82%  
 * 
 * + 【思路 1 -- 写法 2】：回溯（选与不选）
 *      只要记住，如果出现右括号数比左括号多的时候，就不该递归下去了；
 *      + 分析：完全剪枝同上
 *      + rank: 
 *          + 时间效率：0 ms, 击败 100%
 *          + 空间效率：10.02 MB, 击败 91.46%
 */

#include <vector>
#include <string>
#include <iostream>
using std::vector;
using std::string;

// 【思路 1 -- 写法 1】：回溯（枚举）
class Solution {
public:
    vector<string> generateParenthesis(int n) {
     
        vector<char> path(2 * n, ')');
        vector<string> ans;
        auto dfs = [&](this auto&& dfs, int idx, int left, int right) -> void {

            if (left == n) {
                ans.push_back(std::move(string(path.begin(), path.end())));
                //std::cout << ans[ans.size() - 1] << std::endl;
                return;
            }

            for (int j = idx; j < 2 * n; ++j) {

                if (right + (j - idx) > left) return;
                
                path[j] = '(';
                dfs(j + 1, left + 1, right + (j - idx));
                path[j] = ')';
            }
        };

        dfs(0, 0, 0);

        return ans;
    }
};

// 【思路 1 -- 写法 2】：回溯（选与不选）
class Solution {
public:
    vector<string> generateParenthesis(int n) {

        vector<char> path(2 * n, ')');
        vector<string> ans;
        
        [&](this auto&& dfs, int idx, int left, int right) -> void {
            
            if (right > left) return;
            
            if (left == n) {
                ans.push_back(string(path.begin(), path.end()));
                return;
            }
            
            // 选
            path[idx] = '(';
            dfs(idx + 1, left + 1, right);
            path[idx] = ')';
            
            // 不选
            dfs(idx + 1, left, right + 1);
        } (0, 0, 0);
        
        return ans;
    }
};

int main() {

    int n = 3;
    Solution().generateParenthesis(n);
}