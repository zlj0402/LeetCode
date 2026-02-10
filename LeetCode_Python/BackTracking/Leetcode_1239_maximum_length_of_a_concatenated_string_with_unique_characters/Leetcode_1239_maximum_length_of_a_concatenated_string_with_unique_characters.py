"""
@brief: Leetcode_1239_串联字符串的最大长度
@link: https://leetcode.cn/problems/maximum-length-of-a-concatenated-string-with-unique-characters/description/
@author: liangj.zhang
@date: 6/2/2026

@updated:
 + 9/2/2026： add【思路 1 -- 写法 2】

@Difficulty: Medium

@Label: Backtracking

@Retrospect(worthy 1 - 5): 5

@thoughts:
    + 【思路 1】：回溯，不仅全局结果使用 integer 代替，
     不过我没有想到，将题目中每个符合可能得字符串都保留，并转换下来，
         1. 这样在回溯的时候，只要 | 或操作一下就可以了，如果被 | 的字符串每个字符都在全局的变量中没有存在，
            | 之后，字符串的每个 1 位都会加到全局变量中，结果跟想加的结果一样，
         ---
         如果，有重复的 1，或操作之后，这个位的值，相当于没有算上，| 之后的值，就会比相加的值小；
         这样就能比较出：构成的新字符串结构会不会有重复的字符；
         ---
         这样做，少了一次遍历字符串的时间，
         回溯的次数都是相近的，但每一次可能都可以少去遍历的时间；
         ---
         2. 回溯次数的优化：将单个字符串，就存在重复字符的字符串剔除，在剩余的结果中进行回溯；

     + 分析：
         + 时间复杂度：O(2^n)
         + 空间复杂度：O(n)
     + rank:
         + 时间效率：175 ms，击败 20.22%
         + 空间效率：19.19 MB，击败 37.36%
"""

from typing import List

class Solution:
    def __init__(self) -> None:
        self.__rec = []
        self.__maxSize = 0

    def __dfs(self, idx: int, res: int) -> None:
        if idx == self.__rec.__len__():
            if res.bit_count() > self.__maxSize:
                self.__maxSize = res.bit_count()
            return

        for i in range(idx, self.__rec.__len__()):
            valid = False
            if res | self.__rec[i] == res + self.__rec[i]:
                valid = True
            self.__dfs(i + 1, res | self.__rec[i] if valid else res)
        

    def maxLength(self, arr: List[str]) -> int:
        for s in arr:
            tmp = 0
            valid = True
            for c in s:
                if tmp >> (ord(c) - ord('a')) & 1:
                    valid = False
                    break
                tmp |= 1 << (ord(c) - ord('a'))
            if valid: self.__rec.append(tmp)

        self.__dfs(0, 0)

        return self.__maxSize
    

# chat 给的 -- 比上面的方式还好
from typing import List

class Solution:
    def maxLength(self, arr: List[str]) -> int:
        maxLen = 0

        def dfs(idx: int, mask: int, length: int) -> None:
            nonlocal maxLen
            maxLen = max(maxLen, length)

            for i in range(idx, len(arr)):
                curMask = 0
                valid = True

                # 计算当前字符串的 mask
                for c in arr[i]:
                    bit = 1 << (ord(c) - ord('a'))
                    # 字符串自身有重复 或 与已有 mask 冲突
                    if curMask & bit or mask & bit:
                        valid = False
                        break
                    curMask |= bit

                if valid:
                    dfs(i + 1, mask | curMask, length + len(arr[i]))

        dfs(0, 0, 0)
        return maxLen