/**
 * @brief: Leetcode_17_电话号码的字母组合
 * @link: https://leetcode.cn/problems/letter-combinations-of-a-phone-number/description/
 * @author: liangj.zhang
 * @date: 12/1/2026
 * 
 * @Difficulty: Medium
 * 
 * @Label: Backtracking
 * 
 * @Retrospect(worthy 1 - 5): 3
 * 
 * @thoughts:
 *  + 【思路 1】：回溯
 *      这题，教我们，从多重循环到递归的转换
 *      视频教程：https://www.bilibili.com/video/BV1mG4y1A7Gu/
 * 
 *      >>> 从原问题到子问题的问题，适合用递归来解决 <<<
 *          原问题：构造长为 n 的字符串
 *                        |
 *                    枚举一个字母
 *                        |
 *                       \ /
 *          子问题：构造长为 n - 1 的字符串
 *          ---------
 *          回溯有一个增量构造答案的过程；
 */

#include <string>
#include <vector>
using std::vector;
using std::string;

// 常规 dfs 写法
/*
class Solution {
private:
    static string map[10];
    static char path[5];
    static vector<string> ans;

    void dfs(string& digits, int i, int n) {

        if (i == n) {

            path[n] = '\0';
            ans.push_back(string(path));
            return;
        }
        for (char c : map[digits[i] - '0']) {

            path[i] = c;
            dfs(digits, i + 1, n);
        }
    }
public:
    vector<string> letterCombinations(string digits) {
        
        ans.clear();
        dfs(digits, 0, digits.size());
        return ans;
    }
};

string Solution::map[10] = {"", "", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"};
char Solution::path[5]{};
vector<string> Solution::ans{};
*/

// 递归 lambda dfs 写法
class Solution {
private:
    static string map[10];
public:

        vector<string> letterCombinations(string digits) {
        
        vector<string> ans;
        int n = digits.size();
        string path(n, 0);
        auto dfs = [&](this auto&& dfs, int i) -> void {

            if (i == n) {

                ans.emplace_back(string(path));
                return;
            }

            for (char c : map[digits[i] - '0']) {

                path[i] = c;    // 这里直接覆盖了 i 的位置，所以 dfs 之后不需要回溯；
                dfs(i + 1);
            }
        };

        dfs(0);
        return ans;
    }
};

string Solution::map[10] = {"", "", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"};

int main() {

    string digits = "23";
    Solution().letterCombinations(digits);
}