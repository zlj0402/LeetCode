"""
@brief: Leetcode_3_无重复字符的最长子串
@link: https://leetcode.cn/problems/longest-substring-without-repeating-characters/description/
@author: liangj.zhang
@date: 5/9/2025

@Difficulty: Medium

@Label: Sliding Window(Two Pointers)

@Retrospect(worthy 1 - 5): 3

@description:
    是偶然决定来写这道题的，临时准备面试阿里的驱动外包；
    在牛客上搜到了阿里的外包面试，但不一定是驱动的面经；
    面经的阶段一，就是这个滑动窗口的问题；
    看了，按个例子走了一遍；然后，自己写的；
    还是有点死记硬背的感觉；后面再多写；

@thoughts:
    + 【思路 1】：滑动窗口
        左边的窗口，是 l；
        右边的窗口，是 r；
        通过 dict<char, int> 来存储访问过的字符 & 位置；
        当前 r 位置的字符：
        + 访问过，但不在 [l, r) 之内，只用更新下该字符最后出现的位置 & r - l + 1 与 max_len 比较；
        + 没访问过，记录 & r - l + 1 与 max_len 比较；
        + 访问过，且在 [l, r) 之内，l 更改为上一次该字符位置的下一位；
            + 该字符之前的字符串（包含该字符），长度已记录，没有再延长的可能；
            + 窗口的左边 l，改为该字符上次出现的位置的下一位；
              => 这样才能保证，窗口内都是没有重复的字符；
            + 那么，我们更改该字符，最后一次出现的位置；

        如果没有出现过，l 不动；
        r 随 for-loop 加 1； => 也即窗口的长度加 1；

        + 分析：
            + 时间复杂度：O(n)
            + 空间复杂度：O(1)

        + rank:
            + 时间效率：7 ms, 击败 99.71%
            + 空间效率：17.78 ms, 击败 18.02%
"""

class Solution:
    def lengthOfLongestSubstring(self, s: str) -> int:
        rec = {}
        l = 0
        length = max_len = 0
        
        for r, c in enumerate(s):
            # 没有出现过 or 出现过，但在窗口范围之外
            if rec.get(c) is None or rec[c] < l:
                length += 1
                if length > max_len:
                    max_len = length
            else:   # 出现过 and 在窗口范围内
                l = rec[c] + 1
                length = r - l + 1
            rec[c] = r
        
        return max_len