//
// Created by liangj.zhang on 14/6/2025
// 
// URL: https://leetcode.cn/problems/find-all-anagrams-in-a-string/description
// 
// Difficulty: Medium
// 
// Label: SlidingWindow
// 
// 思想：
//      这题完全是，自己抠出来的，虽然是滑动窗口，但似乎没显得边界感很强；
//      看了题解，和别人的讨论，他们的代码很少，我嫉妒了，留着下次写吧；
//      题解有两种做法，体会来看，自己的做法跟第二种是类似的；
// 
//      + 我的算法过程，完全是按照动态滑动窗口，应该滑动的过程来的；
//      + 一开始，计数了字符串 p 的字符频率；
//      + 每移动一次，
//      + 字符有出现在 p 中的话，减去一次记录的频率；
//      + 当所有记录的频率为 0 的话，且当次的字符频率也是 0，那么肯定就符合 异位词 的条件了；
//      + 在出现，>>> 某个字符多出现的时候，窗口的左边，应该移动到  [start, end) 范围内 该字符第一次出现位置的下一位；<<<（这一步很重要，摸索过程，调试很多遍才注意的）
//      + 而不是 [start, end) 该字符最后一次记录的下一位；
//      + 上一次 start --> new_start([start, end) 范围内 该字符第一次出现位置的下一位) => [start, new_start) 内减去的频率次数，再回溯回去；
//      + 其他细节：
//          对于出现了，没在字符串 p 中出现过的字符，我直接 reset 了所有状态，我没有再一位一位回溯；
//          当然，这其中，还能出现一些细节剪枝，或者避免上面没出现在 p 中，特殊处理的写法；
// 
// rank: great
//  时间效率：0 ms, 击败 100% （多次提交，结果是 3ms, 4ms 的次数多一些
//  空间效率：14.04 MB, 击败 15.82%
// 
// 下一次重写：题解的第一种方式，vector<int> 存储 >>> 固定大小的窗口 <<< 的词频，与一开始记录的 vector<int> 词频，进行比较；
//


#include<string>
#include<vector>
#include<iostream>
using std::string;
using std::vector;
using std::cout;
using std::endl;

#include <queue>
#define LETTER 26
using std::queue;

class Obj {

private:
    bool accept;
    const int size;
    int sum;
    bool hasc[LETTER];
    int chars[LETTER];
    int cchars[LETTER];
    queue<int> inside_pos[LETTER];

    inline void resetStatus() {

        for (int i = 0; i < LETTER; i++)
            chars[i] = cchars[i];

        sum = size;

        //accept = false;
    }

public:

    Obj(string& str) : size(str.size()), sum(size) {    // 初始化顺序是按类内定义顺序，size 定义在前

        for (int i = 0; i < LETTER; i++) {
            chars[i] = 0;
        }

        for (auto& e : str)
            chars[e - 'a'] += 1;

        for (int i = 0; i < LETTER; i++) {

            hasc[i] = chars[i] ? true : false;
            cchars[i] = chars[i];
        }

        accept = false;
    }

    // if logic error, return -1;
    int sub(char v, int idx) {

        int pos = v - 'a';
        chars[pos] -= 1;
        sum -= 1;

        if (chars[pos] == 0 && sum == 0) {
            accept = true;
        }

        return chars[pos] < 0 ? -1 : 0;
    }

    void recover(char v) {

        chars[v - 'a'] += 1;
        sum += 1;

        if (accept)
            accept = false;
    }

    void reset() {

        if (sum == size)
            return;

        // reset rec、sum
        resetStatus();
    }

    bool isAccept() const {
        return accept;
    }

    bool contains(char v) const {

        return cchars[v - 'a'] != 0;
    }

    int getInsideFirstPos(char v, int start) {

        queue<int>& q = inside_pos[v - 'a'];
        while (!q.empty() && q.front() < start)
            q.pop();

        return !q.empty() ? q.front() : -1;
    }

    void pushInsidePos(char v, int idx) {

        inside_pos[v - 'a'].push(idx);
    }
};

class Solution {
public:
    vector<int> findAnagrams(string s, string p) {

        if (p.size() > s.size()) return {};

        vector<int> ans;

        int start, end, size;
        size = s.size();

        Obj obj = Obj(p);

        start = 0;
        char v;
        for (end = 0; end < size; end++) {

            v = s[end];

            // 如果某个字符不在 p 中，start 从该位置下一位开始；
            if (!obj.contains(v)) {

                start = end + 1;
                obj.reset();
                continue;
            }

            // 如果当前字符 < 0（或者 sum < 0)，说明这段已经不可能了
            int ret = obj.sub(v, end);
            if (ret == -1) {

                int new_start = obj.getInsideFirstPos(v, start) + 1;    // 应该得到滑动窗口内第一个 v 的位置的下一位；
                for (int i = start; i < new_start; i++)
                    obj.recover(s[i]);
                start = new_start;
            }

            // 如果异位词找到；记录、恢复、 start 位置窗口左边向左移动 1 位；
            if (obj.isAccept()) {

                ans.push_back(start);
                obj.recover(s[start]);
                start += 1;
            }

            obj.pushInsidePos(v, end); // 原来错误的写法，放到了所有操作之前（字符存在的话）；应该要在先获得在上一次位置，再更新这次的位置，不然在 ret == -1 的情况，就会出现问题
        }

        return ans;
    }
};

int main() {

    string s = "cbaebabacd";
    string p = "abc";

    vector<int> ret = (new Solution())->findAnagrams(s, p);

    for (auto& e : ret)
        cout << e << " ";
    cout << endl;
}