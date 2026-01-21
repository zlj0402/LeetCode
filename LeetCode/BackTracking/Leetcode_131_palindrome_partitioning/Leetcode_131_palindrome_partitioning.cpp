/**
 * @brief: Leetcode_131_分割回文串
 * @link: https://leetcode.cn/problems/palindrome-partitioning/description/
 * @author: liangj.zhang
 * @date: 19/1/2026
 * 
 * @Difficulty: Medium
 * 
 * @Label: BackTracking
 * 
 * @Retrospect(worthy 1 - 5): 4
 * 
 * @thoughts:
 *  + 【思路 1】：回溯，枚举字符间逗号
 *      每一个遍历，都是从当前字符，划长度 1 的字符串，判断一下划出来的字符是否是回文，是则进行下去；
 *                              再划长度为 2 的字符串，判断，内部（下一层）先从后续部分长度为 1，再到长度为 剩下最长；
 *                                          。。。
 *                                            n-1
 *                                               n
 *      内部的过程，其实都一样，是子集型问题，关注当前循环，和循环终止条件就可；
 *      ---
 *      何为枚举了：每次遍历，都决定了是一次划分；
 *                  for (size_t j = i; j < n; ++j) {
 *                      string sub_s = s.substr(i, j - i + 1);
 * 
 *      + 分析：
 *          + 时间复杂度：回溯路径数 ≈ 2^(n-1)， 回文判断平均 O(n)，sub_str 获得平均 O(n) => O(n*2^n)
 *          + 空间复杂度：算上结果：O(n*2^n)
 *      + rank:
 *          + 时间效率：35 ms, 击败 98.27%
 *          + 空间效率：52.49 MB, 击败 84.96%
 * 
 *  + 【思路 2】：回溯，逗号选
 *      如果选了，就从上一次结束的位置，到当前位置 -> [start, i + 1)
 *      ---
 *      何为选或不选：当前 dfs 当中，有选，不选两种可能；
 *                  ...
 *                  if (i < n - 1) dfs(i + 1, start);
 *                  ...
 *                  if (isPalindrome(s, start, i)) {
 *                      path.push_back(s.substr(start, i - start + 1));
 * 
 *      + 分析：
 *          + 时间复杂度：O(n*2^(n - 1))
 *          + 空间复杂度：不带结果：O(n) 栈递归 + O(n) path 占用 -> O(n)
 *                          带结果 O(n*2^(n - 1))
 *      + rank:
 *          + 时间效率：48 ms, 击败 85.07%
 *          + 空间效率：69.89 MB, 击败 76.53%
 */

#include <vector>
#include <string>
using std::vector;
using std::string;

/*
class Solution {
private:
    bool isPalindrome(string& s) {

        size_t front{0}, rear{s.size() - 1};
        while (front < rear) {

            if (s[front] != s[rear])
                return false;
            ++front;
            --rear;
        }
        return true;
    }
public:
    vector<vector<string>> partition(string s) {
        
        vector<vector<string>> ret;
        vector<string> path;
        size_t n = s.size();

        auto dfs = [&](this auto&&dfs, size_t i) -> void {

            if (i == n) {

                ret.push_back(path);
                return;
            }

            for (size_t j = i; j < n; ++j) {

                string sub_s = s.substr(i, j - i + 1);
                if (isPalindrome(sub_s)) {

                    path.push_back(sub_s);
                    dfs(j + 1);
                    path.pop_back();
                }
            }
        };

        dfs(0);

        return ret;
    }
};
*/

class Solution {
private:
    static bool isPalindrome(string& s, size_t left, size_t right) {

        while (left < right) {

            if (s[left] != s[right]) 
                return false;

            ++left;
            --right;
        }
        return true;
    }

public:
    vector<vector<string>> partition(string s) {
        
        vector<vector<string>> ret;
        vector<string> path;
        size_t n = s.size();

        auto dfs = [&](this auto&&dfs, size_t i, size_t start) -> void {

            if (i == n) {

                ret.push_back(path);
                return;
            }

            if (i < n - 1) 
                dfs(i + 1, start);

            if (isPalindrome(s, start, i)) {
                path.push_back(s.substr(start, i - start + 1));
                dfs(i + 1, i + 1);
                path.pop_back();
            }
        };

        dfs(0, 0);

        return ret;
    }
};