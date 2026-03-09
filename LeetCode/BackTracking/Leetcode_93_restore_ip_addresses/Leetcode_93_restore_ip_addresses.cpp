/**
 * @brief: Leetcode_93_复原_IP_地址
 * @link: https://leetcode.cn/problems/restore-ip-addresses/description/
 * @author: liangj.zhang
 * @date: 24/2/2026
 * 
 * @updated:
 *  + 9/3/2026: add【思路 1 -- 写法2】：选与不选，子集型回溯
 * 
 * @Difficulty: Medium
 * 
 * @Label: Backtracking
 * 
 * @Retrospect(worthy 1 - 5): 4
 * 
 * @thoughts:
 *  + 【思路 1】：回溯
 *      + 划分次数，3 次 -- remaining
 *      + 不能有前导 0
 *          + 单个 0 合法
 *          + 多个位时，第一位不能是 0
 *      + 其他情况时，每个数是不能超过 255
 *          + 位数超过 3 位，后面都不用看了
 *          + 小于等于 3 位，atoi(x) <= 255
 *      + 分析：
 *          + 时间复杂度：0 ≤ n ≤ 20, n = s.size()
 *              string sub_s = s.substr(...) -> O(3)
 *              stoi(sub_s) -> O(3)
 *              join(path, ".") -> O(12)
 *              剪枝后，O(1) => 因为IP地址最多4段，每段最多3位，递归树最大节点数为：3^4 = 81
 *          + 空间复杂度：递归最大为 4 -> O(1)，path, ans -> O(n)
 *      + rank:
 *          + 时间效率：0 ms, 击败 100%
 *          + 空间效率：10.29 MB, 击败 50.9%
 * 
 * + 【思路 1 -- 写法2】：选与不选，子集型回溯
 *      思路和上面一样，但做法稍有不一样，这次是选择记录上一次选择的位置，不是记录已经选择的长度；
 *      + 分析：
 *          + 时间复杂度：接近完全剪枝，0 ms，击败 100%
 *          + 空间复杂度：参考上方，O(n)
 *      + rank:
 *          + 时间效率：0 ms, 击败 100%
 *          + 空间效率：10.63 MB, 击败 36.03%
 */

#include <vector>
#include <string>
#include <iostream>
#include <sstream>
using std::vector;
using std::string;
using std::ostringstream;

// 【思路 1】：回溯
// class Solution {
// private:
//     static vector<string> path, ans;
//     static bool isValid(string& sub_s) {

//         if (sub_s.size() == 1) {
//             return true;
//         }
//         else if (sub_s.size() <= 3 && sub_s.size() > 1) {   // 没有加位数限制，stoi 处理到 10位数时，超过 int 承受范围，会报 terminate called after throwing an instance of 'std::out_of_range'
//             if (sub_s[0] != '0' && stoi(sub_s) <= 255) 
//                 return true;
//         }
//         return false;
//     }

//     string join(const vector<string>& lst, const string& sep)
//     {
//         ostringstream oss;

//         for (int i = 0; i < lst.size(); i++)
//         {
//             if (i > 0)
//                 oss << sep;

//             oss << lst[i];
//         }

//         return oss.str();
//     }

//     // remaining == 3，表示只能添加最多 3 个 '.'
//     // size_s 保存 path 中所有字符数 -> 方便剪枝
//     void dfs(string& s, int idx, int remaining, int size_s) {

//         if (remaining == 0) {
            
//             if (string sub_s = s.substr(idx) ; isValid(sub_s)) {

//                 path.push_back(sub_s);
//                 ans.push_back(std::move(join(path, ".")));
//                 path.pop_back();
//             }
//             return;
//         }

//         for (int j = idx; j < s.size(); ++j) {

//             string sub_s = s.substr(idx, j - idx + 1);

//             // 剪枝的两个关键步骤
//             if (sub_s.size() > 3 || stoi(sub_s) > 255) return;
//             if (s.size() - size_s - sub_s.size() > remaining * 3) continue; // 类型提升经典坑：s.size() - size_s - sub_s.size() - remaining * 3 > 0 => size_t 是 unsigned long long, 最后一步运算，int 会被提升为 unsigned long long，
//                                                                             // s.size() = 11, size_s = 0, sub_s.size() = 3, remaining = 3，结果是远大于 0 的数 =》 最后一步 - remaining * 3 => - 9，这个 9 原来是 int，会被提升为 ULL，因为 ULL 类型更大，8(ULL) - 9(ULL) 得负数，但按照无符号数读取
            
//             // 只判定当前的合不合法
//             if (isValid(sub_s)) {

//                 int size = sub_s.size();
//                 path.push_back(std::move(sub_s));
//                 dfs(s, j + 1, remaining - 1, size_s + size);
//                 path.pop_back();
//             }
//         }
//     }
// public:
//     vector<string> restoreIpAddresses(string s) {
        
//         path.clear(); ans.clear();

//         dfs(s, 0, 3, 0);

//         return ans;
//     }
// };

// vector<string> Solution::path, Solution::ans;

// 【思路 1 -- 写法2】：选与不选，子集型回溯
class Solution {

private:
    vector<string> path;
    vector<string> ans;
    static bool isValid(string& sub_s) {

        if (sub_s.size() == 1) {
            return true;
        }
        else if (sub_s.size() <= 3 && sub_s.size() > 1) {   // 没有加位数限制，stoi 处理到 10位数时，超过 int 承受范围，会报 terminate called after throwing an instance of 'std::out_of_range'
            if (sub_s[0] != '0' && stoi(sub_s) <= 255) 
                return true;
        }
        return false;
    }

    static string join(const vector<string>& lst, const string& sep)
    {
        ostringstream oss;

        for (int i = 0; i < lst.size(); i++)
        {
            if (i > 0)
                oss << sep;

            oss << lst[i];
        }

        return oss.str();
    }

    // dfs: remaining, leftDot
    void dfs(int idx, int lastSelected, int leftDot, string& s) {

        if (leftDot == 0) {

            if (string sub_s = s.substr(idx); isValid(sub_s)) {
                path.push_back(std::move(sub_s));
                ans.push_back(join(path, "."));
                // std::cout << ans[ans.size() - 1] << std::endl;
                path.pop_back();
            }
            return;
        }

        if (((s.size() - idx) / (leftDot + 1) > 3) || idx - lastSelected > 3 || s.size() - idx - 1 < leftDot) return;

        if (string sub_s = s.substr(lastSelected + 1, idx - lastSelected); isValid(sub_s)) {
            path.push_back(std::move(sub_s));
            dfs(idx + 1, idx, leftDot - 1, s);
            path.pop_back();
        }
        
        dfs(idx + 1, lastSelected, leftDot, s);
        
    }
public:
    vector<string> restoreIpAddresses(string s) {

        dfs(0, -1, 3, s);

        return ans;
    }
};

int main() {

    string s = "25525511135";
    Solution().restoreIpAddresses(s);
}