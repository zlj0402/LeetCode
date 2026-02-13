"""
 * @brief: Leetcode_784_字母大小写全排列
 * @link: https://leetcode.cn/problems/letter-case-permutation/description/
 * @author: liangj.zhang
 * @date: 26/1/2026
 * 
 * @Difficulty: Medium
 * 
 * @Label: BackTracking & string
 * 
 * @Retrospect(worthy 1 - 5): 3
 * 
 * @thoughts:
 *  + 【思路 1 -- 写法 1】：选与不选，这里就是选择反不反转
 *      不是字母的不动；
 * 
 *      + 分析：
 *          + 时间复杂度：O(2^n), n-> string 的长度；
 *          + 空间复杂度：s -> O(n), 递归 -> O(n)，不考虑结果空间 -> O(n)
 *      + rank:
 *          + 时间效率：7 ms，击败 66.52%
 *          + 空间效率：20.56 MB, 击败 6.46%
 """

from typing import List


class Solution:
    STEP = ord('a') - ord('A')
    def letterCasePermutation(self, s: str) -> List[str]:
        ret = []
        n = s.__len__()

        s_lst = list(s)

        def revertLetter(c: str) -> str:
            if c >= 'a' and c <= 'z':
                return chr(ord(c) - Solution.STEP)
            if c >= 'A' and c <= 'Z':
                return chr(ord(c) + Solution.STEP)
            return c

        def dfs(i: int) -> None:
            if i == n:
                ret.append(''.join(s_lst))
                return
            
            dfs(i + 1)

            if s_lst[i].isascii() and s_lst[i].isalpha():
                c = s_lst[i]
                s_lst[i] = revertLetter(c=s_lst[i])
                dfs(i + 1)
                s_lst[i] = c

        dfs(0)

        return ret