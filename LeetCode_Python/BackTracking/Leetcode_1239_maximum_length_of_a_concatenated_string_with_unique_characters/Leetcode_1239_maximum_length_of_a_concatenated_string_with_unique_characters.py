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

    + 【思路 1 -- 写法 2】：即 C++ 【思路 1 -- 写法 3】，这里 python 是 chat 给的版本
         也确实是从 chat 给的版本中，体会到，用 C++ 写法 2 的版本，略改一下得到的；
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

                # 为什么这里是 valid 才往下进行：
                    # 假如当前是有重复的字符串，[1] 如果不选这个，继续往下执行dfs（即不分 valid，都往下 dfs），选择这个下一个；
                    #                         [2] 和就此从断绝该处的所有可能；在直接选择同级的这个下一个，跟上面不选但继续 dfs 下一个，达到了同一个效果；
                    #                           既如此，[2] 的这种方式还能达到剪枝的效果；
                    #                           但需要，每一次进入都要跟当前最大值比较，这种交换代价还是比较小的；
                # 至于上面的写法为什么是递归到最后，再来计算长度：
                    # 现在想想，确实可以这么做，但是存在重复的情况；
                    # 对比此处的这种写法，唯一的大优点，是去掉了自身就不符合条件的字符串；
                    # 但也不影响可以进行剪枝的那一步；
                # ["cha","r", "act","ers"]
                    # 以上面的举例，
                        # 现在组字符串组到 "cha" "r" (char)了
                        # 下一步 "act" 这个字符串，组一起("charact")是不符合题目要求的,
                        # 这时候是 dfs 进行到下一个 "ers"，还是切断 dfs，由遍历得到下一个 "ers"
                        # 这样举例说明，应该就清楚了；
                if valid:
                    dfs(i + 1, mask | curMask, length + len(arr[i]))

        dfs(0, 0, 0)
        return maxLen