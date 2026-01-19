"""
@brief: Leetcode_131_分割回文串
@link: https://leetcode.cn/problems/palindrome-partitioning/description/
@author: liangj.zhang
@date: 18/1/2026

@Difficulty: Medium

@Label: BackTracking

@Retrospect(worthy 1 - 5): 4

@thoughts:
 + 【思路 1】：回溯，枚举字符间逗号
     每一个遍历，都是从当前字符，划长度 1 的字符串，判断一下划出来的字符是否是回文，是则进行下去；
                             再划长度为 2 的字符串，判断，内部（下一层）先从后续部分长度为 1，再到长度为 剩下最长；
                                         。。。
                                           n-1
                                              n
     内部的过程，其实都一样，是子集型问题，关注当前循环，和循环终止条件就可；

     + 分析：
         + 时间复杂度：回溯路径数 ≈ 2^(n-1)， 回文判断平均 O(n)，sub_str 获得平均 O(n) => O(n*2^n)
         + 空间复杂度：算上结果：O(n*2^n)
     + rank:
         + 时间效率：43 ms, 击败 89.97%
         + 空间效率：32.92 MB, 击败 78.98%
"""

class Solution:
    def partition(self, s: str) -> List[List[str]]:
        ans = []
        path = []
        n = s.__len__()

        def dfs(i: int) -> None:
            if i == n:
                ans.append(path.copy())
                return 
            for j in range(i, n):
                t = s[i:j + 1]
                if t == t[::-1]:
                    path.append(t)
                    dfs(j + 1)
                    path.pop()
        dfs(0)
        return ans