/**
 * @brief: Leetcode_784_字母大小写全排列
 * @link: https://leetcode.cn/problems/letter-case-permutation/description/
 * @author: liangj.zhang
 * @date: 26/1/2026
 * 
 * @updated:
 *  + 31/1/2026: 【思路 2】：bfs
 * 
 * @Difficulty: Medium
 * 
 * @Label: BackTracking & string
 * 
 * @Retrospect(worthy 1 - 5): 3
 * 
 * @thoughts:
 *  + 【思路 1】：dfs: 选与不选，这里就是选择反不反转
 *      不是字母的不动；
 * 
 *      + 分析：
 *          + 时间复杂度：O(2^n), n-> string 的长度；
 *          + 空间复杂度：s -> O(n), 递归 -> O(n)，不考虑结果空间 -> O(n)
 *      + rank:
 *          + 时间效率：0 ms，击败 100%
 *          + 空间效率：12.66 MB, 击败 88.6%
 * 
 *  + 【思路 2】：bfs
 *      举例：a1b2
 *              ""
 *            /   \
 *           a     A
 *           |     |
 *          a1     A1
 *         /  \   /  \
 *       a1b a1B A1b A1B
 *       |    |   |    |
 *    a1b2 a1B2 A1b2 A1B2
 * 
 *      之所以称这种做法为 BFS，因为队列中始终存在的，是当前层所具有的元素；（当一层结束时，剩余元素是下一层的所有元素）
 *      ---
 *      这种BFS有点奇妙；
 * 
 *      + 分析：
 *          + 时间复杂度：O(n * 2^n), n 是字符串的长度
 *          + 空间复杂度：O(n * 2^n)，队列中元素个数最多为 2^n
 *      + rank:
 *          + 时间效率：0 ms, 击败 100%
 *          + 空间效率：14.27 MB, 击败 43.62%
 */

#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include <queue>
using std::vector;
using std::string;
using std::cout;
using std::endl;
using std::queue;

// 【思路 2】：bfs
class Solution {
public:
    vector<string> letterCasePermutation(string s) {
        
        vector<string> ret;
        queue<string> qu;

        qu.emplace("");
        while(!qu.empty()) {

            string& cur = qu.front();
            if (cur.size() == s.size()) {
                ret.push_back(cur);
                qu.pop();
            }
            else {
                int pos = cur.size();
                if (isalpha(s[pos])) {

                    string next = cur;
                    next.push_back(s[pos] ^ 32);
                    qu.emplace(next);
                }
                cur.push_back(s[pos]);
            }
        }

        return ret;
    }
};

// 【思路 1】：dfs: 选与不选，这里就是选择反不反转
/*
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
*/

int main() {

    string s = "a1b2";
    vector<string> ret = Solution().letterCasePermutation(s);

    for (auto s : ret)
        cout << s << " ";
    cout << endl;
}