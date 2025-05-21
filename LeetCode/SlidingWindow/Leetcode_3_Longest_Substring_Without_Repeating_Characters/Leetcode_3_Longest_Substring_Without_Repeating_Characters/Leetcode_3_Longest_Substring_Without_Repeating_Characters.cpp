//
// Created by liangj.zhang on 21/5/2025
//

// ps:
// 是偶然决定来写这道题的，临时准备面试阿里的驱动外包；
// 在牛客上搜到了阿里的外包面试，但不一定是驱动的面经；
// 面经的阶段一，就是这个滑动窗口的问题；看了，按个例子走了一遍；然后，自己写的；还是有点死记硬背的感觉；后面再多写；

// 思路：
// 左边的窗口，是start；
// 右边的窗口，是end;
// 当出现以前记录过的字符：record.find(cur) != record.end()，再比较是否在窗口内：record[cur] >= start
// 窗口的左边 start，改为该字符上次出现的位置的下一位； => 这样才能保证，窗口内都是没有重复的字符；
// 那么，我们更改该字符，最后一次出现的位置；
// 
// 如果没有出现过，start 不动；
// end 随 for-loop 加 1； => 也即窗口的长度加 1；

// rank:
// 时间；10ms, 击败69.46%
// 空间：11.73MB, 击败59.64%

#include <iostream>
#include <string>
#include <unordered_map>

#define um unordered_map

using std::string;
using std::cout;
using std::endl;
using std::unordered_map;


class Solution {

    public:
        int lengthOfLongestSubstring(string s) {

            int start = 0;
            int end;
            char cur;
            um<char, int> record;   // int -> 最后一次出现的位置；（cur之前
            int maxLen = 0;

            for (end = 0; end < s.size(); end++) {
                
                cur = s[end];
                if (record.find(cur) != record.end() && record[cur] >= start) {
                    start = record[cur] + 1;
                }
                record[cur] = end;

                maxLen = std::max(end - start + 1, maxLen);
            }
            return maxLen;
        }
};

int main() {

	string str = "123132322";
    cout << str << ", length of longest substring: " << (new Solution())->lengthOfLongestSubstring(str) << endl;
}