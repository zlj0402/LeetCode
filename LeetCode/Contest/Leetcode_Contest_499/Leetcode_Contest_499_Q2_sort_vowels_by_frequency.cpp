/**
 * @brief: Leetcode_Contest_499_Q2_按频率对元音排序
 * @link: https://leetcode.cn/problems/sort-vowels-by-frequency/description/
 * @author: liangj.zhang
 * @date: 26/4/2026
 * 
 * @Difficulty: Medium
 */

#include <vector>
#include <unordered_map>
#include <string>
using std::vector;
using std::unordered_map;
using std::string;

#define um unordered_map

class Solution {
private:
    static bool isYuanYin(char c) {
        return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u';
    }
public:
    string sortVowels(string s) {
        vector<int> idx;
        um<char, int> firstIdx {{'a', -1}, {'e', -1}, {'i', -1}, {'o', -1}, {'u', -1}};
        um<char, int> cnt;

        for (int i = 0; i < s.size(); ++i) {
            char c = s[i];
            if (isYuanYin(c)) {
                idx.push_back(i);
                ++cnt[c];
                if (firstIdx[c] == -1) {
                    firstIdx[c] = i;
                }
            }
        }

        int putIdx = 0;
        int maxV = -2;

        while (!(maxV == -1)) {
            maxV = -2;
            char maxK = '0';
            int maxKFirstIdx = -1;
            for (auto &[k, v] : cnt) {
                if (v > maxV) {
                    maxV = v;
                    maxK = k;
                    maxKFirstIdx = firstIdx[maxK];
                }
                else if (v == maxV) {
                    if (maxKFirstIdx > firstIdx[k]) {
                        maxV = v;
                        maxK = k;
                        maxKFirstIdx = firstIdx[maxK];
                    }
                }
            }

            for (int i = 0; i < maxV; ++i, ++putIdx) {
                s[idx[putIdx]] = maxK;
            }

            // erase
            cnt[maxK] = -1;
        }

        return s;
    }
};

int main() {
    string s = "leetcode";
    Solution().sortVowels(s);
}