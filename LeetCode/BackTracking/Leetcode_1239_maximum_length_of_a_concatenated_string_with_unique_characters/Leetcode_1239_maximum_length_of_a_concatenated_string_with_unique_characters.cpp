/**
 * @brief: Leetcode_1239_串联字符串的最大长度
 * @link: https://leetcode.cn/problems/maximum-length-of-a-concatenated-string-with-unique-characters/description/
 * @author: liangj.zhang
 * @date: 6/2/2026
 * 
 * @updated: 
 *  + 9/2/2026： add【思路 1 -- 写法 2】
 *  + 13/2/2026: add【思路 1 -- 写法 3】：回溯，剪枝
 * 
 * @Difficulty: Medium
 * 
 * @Label: Backtracking
 * 
 * @Retrospect(worthy 1 - 5): 5
 * 
 * @thoughts:
 *  + 【思路 1 -- 写法 1】：backTracking -- 仅结果使用 integer 代替字符串字符个数的方式
 *      这是自己想到的写法：
 *          回溯需要的全局的变量，我是通过一个 interger 类型来完成的，仅需要 26 位 bit，我就能表示字符串；
 *          第一位对应 'a'，第一位是 1 -> 表示的字符串含有 'a' 字符；第一位是 0 -> 表示的字符串没有 'a'
 *          第二位对应 'b'，含义同上
 *          ...
 *          第26位对应 'z'，含义同上
 *          ---
 *          这里的转换的做法，同以前在 Samsung 考算法答字符串的题类似，
 *          不过这里不在乎顺序，只要表示有没有就可以了；
 *          以前是将字符串按顺序转换为整型，每个字符需要 5 位来表示，偏移 5 位来存储下一位；
 *          ---
 *      不过我没有想到，将题目中每个符合可能得字符串都保留，并转换下来，
 *          1.这样在回溯的时候，只要 | 或操作一下就可以了，如果被 | 的字符串每个字符都在全局的变量中没有存在，
 *          | 之后，字符串的每个 1 位都会加到全局变量中，结果跟想加的结果一样，
 *          ---
 *          如果，有重复的 1，或操作之后，这个位的值，相当于没有算上， | 之后的值，就会比相加的值小；
 *          这样就能比较出：构成的新字符串结构会不会有重复的字符；
 *          ---
 *          这样做，少了一次遍历字符串的时间，
 *          回溯的次数都是相近的，但每一次可能都可以少去遍历的时间；
 *          ---
 *          2.回溯次数的优化：将单个字符串，就存在重复字符的字符串剔除，在剩余的结果中进行回溯；
 * 
 *      + 分析：
 *          + 时间复杂度：O(2^n * m), m 最大是整个数组拼成的字符串的整个长度；真如果是整个字符串是最长，其他可能也不会直接跳过，平均下来，每个结果的字符串整长度大概是 m/2；
 *          + 空间复杂度：O(n), n -> 递归站的消耗
 *      + rank:
 *          + 时间效率：51 ms, 击败 42.11%
 *          + 空间效率：11.46 MB, 击败 53.39%
 * 
 * + 【思路 1 -- 写法 2】：回溯，不仅全局结果使用 integer 代替，每个字符串也使用 integer 代替，并在此之前就剔除自身不符合的字符串；
 *          理解，见写法 1 的第二段；
 *      + 分析：
 *          + 时间复杂度：O(2^n)
 *          + 空间复杂度：O(n)
 *      + rank:
 *          + 时间效率：0 ms，击败 100%
 *          + 空间效率：10.33 MB, 击败 84.59%
 * 
 * + 【思路 1 -- 写法 3】：回溯，剪枝
 *      + 当遇到组合在一起之后，不符合题目要求时，我们就切断，从该节点往下所有 dfs 的可能；
 *          + 通过遍历来得到下一个字符串；
 *          + 如果继续 dfs 得到下一个，和上面遍历到下一个，是重复的；
 *      + 要实现，随遇不合即停，我们得需要每次在进入 dfs 时都进行比较，
 *          + 一是因为，此时进来的，都是已经合法的情况；
 *          + 二是此时如果还留到 idx == size - 1 时，再去判断，有的情况，不是有的情况，是几乎95%的情况，都会因为半路终止，无法进行判断；
 *      
 *      时间效率每次必定是 0 ms，写法 2 每次还不一定必定是；
 *      + 分析：
 *          + 时间复杂度：O(2^n)，但肯定比这小，因为剪枝了
 *          + 空间复杂度：O(n)，只有最坏的情况才是 O(n)，
 *      + rank:
 *          + 时间效率：0 ms, 击败 100%
 *          + 空间效率：10.26 MB, 击败 89.86%
 */
#include <vector>
#include <string>
#include <iostream>
#include <functional>
using std::cout;
using std::endl;
using std::vector;
using std::string;

// 【思路 1 -- 写法 1】：backTracking -- 仅结果使用 integer 代替字符串字符个数的方式
class Solution {
private:
    bool isValid(unsigned int& mask, string& s, string& res) {

        bool valid = true;
        int invalidIdx = 0;

        for (int i = 0; valid && i < s.size(); ++i) {
            ++invalidIdx;
            char c = s[i];
            res.push_back(c);
            unsigned int lastMask = mask;
        
            if ((mask ^= (1U << (c - 'a'))) < lastMask)
                valid = false;
        }

        if (valid) return true;

        delMask(mask, s, res, invalidIdx);
        return false;
    }

    void delMask(unsigned int& mask, string& s, string& res, int len) {

        for (int i = 0; i < len; ++i) {

            mask ^= (1U << (s[i] - 'a'));
            res.pop_back();
        }
    }
public:
    int maxLength(vector<string>& arr) {
        
        string res;
        size_t maxLen = 0;
        size_t size = arr.size();
        unsigned int mask = 0;

        std::function<void(int)> dfs = [&](int i) -> void {
        // auto dfs = [&](this auto&& dfs, int i) -> void {

            if (res.size() > maxLen) 
                maxLen = res.size();

            for (int j = i; j < size; ++j) {

                bool valid = isValid(mask, arr[j], res);
                dfs(j + 1);
                if (valid) delMask(mask, arr[j], res, arr[j].size());
            }
        };

        dfs(0);

        return maxLen;
    }
};

// 【思路 1 -- 写法 2】：回溯，不仅全局结果使用 integer 代替，每个字符串也使用 integer 代替，并在此之前就剔除自身不符合的字符串；
class Solution {
private:
    static vector<int> rec;
    unsigned int maxSize = 0;

    void dfs(int idx, int res) {

        if (idx == rec.size()) {
            if (size_t size = __builtin_popcount(res); size > maxSize) {
                maxSize = size;
            }
            return;
        }

        for (size_t j = idx; j < rec.size(); ++j) {

            bool valid = false;
            if ((rec[j] | res) == rec[j] + res) 
                valid = true;
            dfs(j + 1, valid ? res | rec[j] : res);
            // if (valid) res ^= rec[j];
        }
    }

public:

    Solution() : maxSize(0) {}

    int maxLength(vector<string>& arr) {
        
        rec.clear();
        for (auto& s : arr) {

            int tmp = 0;
            bool valid = true;
            for (char c : s) {
                
                if (tmp & (1u << (c - 'a'))) {

                    valid = false;
                    break;
                }
                tmp |= 1u << (c - 'a'); 
            }

            // 1. 先排除自身就会有重复字符的字符串
            // 2. 转换字符串成一个 integer，26 位对应表示字符
            if (valid) rec.push_back(std::move(tmp));
        }

        dfs(0, 0);

        return maxSize;
    }
};

vector<int> Solution::rec;

// 【思路 1 -- 写法 3】：回溯，剪枝
class Solution {
private:
    static vector<int> rec;
    unsigned int maxSize = 0;

    void dfs(int idx, int res) {

        if (size_t size = __builtin_popcount(res); size > maxSize) {
            maxSize = size;
        }

        for (size_t j = idx; j < rec.size(); ++j) {

            bool valid = false;
            if ((rec[j] | res) == rec[j] + res) {

                valid = true;
                dfs(j + 1, valid ? res | rec[j] : res);
            }
        }
    }

public:

    Solution() : maxSize(0) {}

    int maxLength(vector<string>& arr) {
        
        rec.clear();
        for (auto& s : arr) {

            int tmp = 0;
            bool valid = true;
            for (char c : s) {
                
                if (tmp & (1u << (c - 'a'))) {

                    valid = false;
                    break;
                }
                tmp |= 1u << (c - 'a'); 
            }

            // 1. 先排除自身就会有重复字符的字符串
            // 2. 转换字符串成一个 integer，26 位对应表示字符
            if (valid) rec.push_back(std::move(tmp));
        }

        dfs(0, 0);

        return maxSize;
    }
};

vector<int> Solution::rec;

int main () {

    vector<string> arr = {"un","iq","ue"};
    Solution().maxLength(arr);
}
