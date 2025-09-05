/**
 * @brief: Leetcode_3_无重复字符的最长子串
 * @link: https://leetcode.cn/problems/longest-substring-without-repeating-characters/description/
 * @author: liangj.zhang
 * @date: 21/5/2025
 * @github: https://github.com/zlj0402/LeetCode/blob/master/LeetCode/SlidingWindow/Leetcode_3_Longest_Substring_Without_Repeating_Characters/Leetcode_3_Longest_Substring_Without_Repeating_Characters/Leetcode_3_Longest_Substring_Without_Repeating_Characters.cpp
 * 
 * @updated:
 *      + 5/9/2025: 【写法1.3】
 * 
 * @Difficulty: Medium
 * 
 * @Label: Sliding Window(Two Pointers)
 * 
 * @Retrospect(worthy 1 - 5): 3
 * 
 * @description:
 *      是偶然决定来写这道题的，临时准备面试阿里的驱动外包；
 *      在牛客上搜到了阿里的外包面试，但不一定是驱动的面经；
 *      面经的阶段一，就是这个滑动窗口的问题；看了，按个例子走了一遍；然后，自己写的；还是有点死记硬背的感觉；后面再多写；
 * 
 * @thoughts:
 *      + 【思路 1】：滑动窗口
 *          左边的窗口，是start；
 *          右边的窗口，是end;
 *          通过 unordered_map<char, int> 来存储访问过的字符 & 位置；
 *          当前 end 位置的字符，
 *          + 访问过，但不在 [start, end）之内，只用更新下该字符最后出现的位置 & end - start + 1 与 max_len 比较；
 *          + 没访问过，记录 & end - start + 1 与 max_len 比较；
 *          + 访问过，且在 [start, end) 之内，start 更改为上一次该字符位置的下一位；
 *              + 该字符之前的字符串（包含该字符），长度已记录，没有再延长的可能；
 *              窗口的左边 start，改为该字符上次出现的位置的下一位； => 这样才能保证，窗口内都是没有重复的字符；
 *              那么，我们更改该字符，最后一次出现的位置；
 *          
 *              如果没有出现过，start 不动；
 *              end 随 for-loop 加 1； => 也即窗口的长度加 1；
 *          + 分析：
 *              + 时间复杂度：O(n)
 *              + 空间复杂度：根据题意，字符都是是ascii 码，所以个数 => O(128)
 *          + rank:
 *              + 【写法 1】：
 *                  + 时间效率：10 ms, 击败 69.46%
 *                  + 空间效率：11.73 MB, 击败 59.64%
 *              + 【写法 1.2】：
 *                  + 时间效率：7 ms, 击败 80.53%
 *                  + 空间效率：11.68 MB, 击败 66.37%
 *              + 【写法 1.3】：
 *                  + 时间效率：4 ms, 击败 86.32%
 *                  + 空间效率：11.55 MB, 击败 77.33%
 */

#include <iostream>
#include <string>

using std::string;
using std::cout;
using std::endl;


#include <unordered_map>
using std::unordered_map;
#define um unordered_map

// 【写法1.3】：跟下面都是一个思路；这次写得这份更清晰；
class Solution {

private:
    um<char, int> rec;

public:
    int lengthOfLongestSubstring(string s) {
        
        rec.clear();
        int size(s.size()), l(0), len(0), max_len(0);

        for (int r = 0; r < size; ++r) {

            // 没有出现过 or 出现过，但在窗口范围之外
            if (rec.find(s[r]) == rec.end() || rec[s[r]] < l) {
                
                if (++len > max_len)
                    max_len = len;
            } else {    // 出现过 and 在窗口范围内

                l = rec[s[r]] + 1;
                len = r - l + 1;
            }
            
            rec[s[r]] = r;
        }

        return max_len;
    }
};

// 【写法 1.2】
/*
class Solution {
public:
    int lengthOfLongestSubstring(string s) {

        int start, end, size;
        start = end = 0;
        size = s.size();

        um<char, int> rec;
        int max_len = 0;

        for (int end = 0; end < size; end++) {

            char v = s[end];
            if (rec.find(v) != rec.end() && rec[v] >= start)
                start = rec[v] + 1;
            else if (end - start + 1 > max_len)
                max_len = end - start + 1;

            rec[v] = end;
        }

        return max_len;
    }
};
*/

// 【写法 1】
/*
class Solution {
public:
    int lengthOfLongestSubstring(string s) {

        int start, end;
        start = end = 0;

        um<char, int> rec;
        int max_len = 0;

        for (int end = 0; end < s.size(); end++) {

            char v = s[end];
            if (rec.find(v) != rec.end() && rec[v] >= start) {

                start = rec[v] + 1;
                rec[v] = end;
            }
            else {

                rec[v] = end;
                if (end - start + 1 > max_len)
                    max_len = end - start + 1;
            }
        }

        return max_len;
    }
};
*/

int main() {

	string str = "123132322";
    cout << str << ", length of longest substring: " << (new Solution())->lengthOfLongestSubstring(str) << endl;
}