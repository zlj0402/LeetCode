"""
@brief: Leetcode_17_电话号码的字母组合
@link: https://leetcode.cn/problems/letter-combinations-of-a-phone-number/description/
@author: liangj.zhang
@date: 12/1/2026

@Difficulty: Medium

@Label: Backtracking

@Retrospect(worthy 1 - 5): 3

@thoughts:
 + 【思路 1】：回溯
     这题，教我们，从多重循环到递归的转换
     视频教程：https://www.bilibili.com/video/BV1mG4y1A7Gu/

     >>> 从原问题到子问题的问题，适合用递归来解决 <<<
         原问题：构造长为 n 的字符串
                       |
                   枚举一个字母
                       |
                      \ /
         子问题：构造长为 n - 1 的字符串
         ---------
         回溯有一个增量构造答案的过程；

     + 分析：
         + 时间复杂度：遍历最坏有 4^n，每个结果组成一个答案 n, 总的时间复杂度是 O(n * 4^n)
         + 空间复杂度：递归站空间 O(n)，临时路径 path 是 O(n)，结果空间 O(k^n * n), k 是每层循环遍历个数，按键最少 3 个字母，最多 4 个字母 -> k 的范围 [3,4]
                     => 但写题，一般可能不算结果空间，
                         => 不算结果空间，O(n)
                         => 算结果空间，O(k^n * n)
     + rank:
         + 时间效率：0 ms, 击败 100%
         + 空间效率：19.21 MB, 击败 5.01%
"""


class Solution:
    MAP = ['', '', 'abc', 'def', 'ghi', 'jkl', 'mno', 'pqrs', 'tuv', 'wxyz']

    def letterCombinations(self, digits: str) -> List[str]:
        n = digits.__len__()
        path = [''] * n
        res = []

        def dfs(i: int) -> None:
            if i == n:
                res.append(''.join(path))
                return
            for c in Solution.MAP[int(digits[i])]:
                path[i] = c
                dfs(i + 1)
        dfs(0)
        return res