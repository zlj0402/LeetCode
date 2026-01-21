"""
@brief: Leetcode_131_分割回文串
@link: https://leetcode.cn/problems/palindrome-partitioning/description/
@author: liangj.zhang
@date: 18/1/2026

@updated: 
    + 20/1/2026: add  【思路 2】：回溯，逗号选或不选

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

 +  【思路 2】：回溯，逗号选或不选
     如果选了，就从上一次结束的位置，到当前位置 -> [start, i + 1)
     --
     很烧脑，只能看着代码模版来理解
    
     + 分析：
        + 时间复杂度：O(n*2^(n - 1))
        + 空间复杂度：不带结果：O(n) 栈递归 + O(n) path 占用 -> O(n)
                    带结果 O(n*2^(n - 1))
     + rank:
        + 时间效率：39 ms, 击败 96.7%
        + 空间效率：32.67 MB, 击败 82.25%
"""

"""
class Solution:
    def partition(self, s: str) -> List[List[str]]:
        ans = []
        path = []
        n = s.__len__()

        # 考虑 [i:] 怎么分割
        def dfs(i: int) -> None:
            if i == n:  # 分割完毕
                ans.append(path.copy())
                return 
            for j in range(i, n):   # 枚举子串结束的位置
                t = s[i:j + 1]      # 分割出子串
                if t == t[::-1]:    # 判断子串是否回文
                    path.append(t)
                    dfs(j + 1)  # 考虑子串 [j+1:] 怎么分割
                    path.pop()
        dfs(0)
        return ans
"""

from typing import List


class Solution:
    def partition(self, s: str) -> List[List[str]]:
        n = s.__len__()
        ans = []
        path = []

        def dfs(i: int, start: int) -> None:
            if i == n:
                ans.append(path.copy())
                return  # 原来错误的写法：忘记这里 return 了，如果缺少，会造成空串一直是回文， dfs(i+1, i+1) 那里一直执行下去
            
            if i < n - 1:
                dfs(i + 1, start)

            t = s[start: i + 1]
            if t == t[::-1]:
                path.append(t)
                dfs(i + 1, i + 1)
                path.pop()

        dfs(0, 0)

        return ans
    
def main():
    s = "aab"
    Solution().partition(s)
    

if __name__ == "__main__":
    main()