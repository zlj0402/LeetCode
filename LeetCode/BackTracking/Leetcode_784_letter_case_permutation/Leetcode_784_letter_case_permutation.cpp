/**
 * @brief: Leetcode_784_字母大小写全排列
 * @link: https://leetcode.cn/problems/letter-case-permutation/description/
 * @author: liangj.zhang
 * @date: 26/1/2026
 * 
 * @Difficulty: Medium
 * 
 * @Label: BackTracking & string
 * 
 * @Retrospect(worthy 1 - 5): 3
 * 
 * @thoughts:
 *  + 【思路 1 -- 写法 1】：选与不选，这里就是选择反不反转
 *      不是字母的不动；
 * 
 *      + 分析：
 *          + 时间复杂度：O(2^n), n-> string 的长度；
 *          + 空间复杂度：s -> O(n), 递归 -> O(n)，不考虑结果空间 -> O(n)
 *      + rank:
 *          + 时间效率：0 ms，击败 100%
 *          + 空间效率：12.66 MB, 击败 88.6%
 * 
 *  + 【思路 1 -- 写法 2】：枚举反不反转，留 2026.1.27 明天写
 */

#include <vector>
#include <string>
#include <algorithm>
using std::vector;
using std::string;

class Solution {
private:
    static constexpr int step = 'a' - 'A';
    static char revertLetter(char c) {

        if (c >= 'a' && c <= 'z')
            return c - step;
        else if (c >= 'A' && c <= 'Z')  // 原来错误的写法：两个等于号少了
            return c + step;

        return c;
    }

public:
    vector<string> letterCasePermutation(string s) {
        
        vector<string> ret;
        size_t n = s.size();

        // auto dfs = [&](this auto&& dfs, size_t i) -> void {

        //     if (i >= n) {
                
        //         ret.push_back(s);
        //         return;
        //     }

        //     dfs(i + 1);

        //     if (char c = s[i]; isalpha(c)) {

        //         s[i] = revertLetter(c);
        //         dfs(i + 1);
        //         s[i] = c;
        //     }
        // };

        auto dfs = [&](auto&& dfs, size_t i) -> void {

            if (i >= n) {
                
                ret.push_back(s);
                return;
            }

            dfs(dfs, i + 1);

            if (char c = s[i]; isalpha(c)) {

                s[i] = revertLetter(c);
                dfs(dfs, i + 1);
                s[i] = c;
            }
        };
        dfs(dfs, 0);

        // dfs(0);

        return ret;
    }
};

int main() {

    string s = "FjkZh";
    Solution().letterCasePermutation(s);
}