"""
@brief: Leetcode_93_复原_IP_地址
@link: https://leetcode.cn/problems/restore-ip-addresses/description/
@author: liangj.zhang
@date: 24/2/2026

@Difficulty: Medium

@Label: Backtracking

@Retrospect(worthy 1 - 5): 4

@thoughts:
    + 【思路 1】：回溯
        + 划分次数，3 次 -- remaining
        + 不能有前导 0
            + 单个 0 合法
            + 多个位时，第一位不能是 0
        + 其他情况时，每个数不能超过 255
            + 位数超过 3 位，后面都不用看了
            + 小于等于 3 位，int(x) <= 255
        + 分析：
            + 时间复杂度：0 ≤ n ≤ 20, n = len(s)
                s[idx:j+1] -> O(3)
                int(sub_s) -> O(3)
                '.'.join(path) -> O(12)
                剪枝后为 O(1)
                因为 IP 地址最多 4 段，每段最多 3 位，
                递归树最大节点数为：3^4 = 81
            + 空间复杂度：
                递归最大深度为 4 -> O(1)
                path, ans -> O(n)
        + rank:
            + 时间效率：0 ms, 击败 100%
            + 空间效率：19.48 MB, 击败 5.18%
"""
from typing import List


class Solution:
    def restoreIpAddresses(self, s: str) -> List[str]:

        path = []
        ans = []
        
        def isValid(sub_s: str) -> bool:
            if len(sub_s) == 1: return True
            elif 1 < len(sub_s) <= 3:
                if sub_s[0] != '0' and int(sub_s) <= 255:
                    return True
            return False
        
        def dfs(s: str, idx: int, remaining: int, size_s: int) -> None:
            nonlocal path, ans
            if remaining == 0:
                sub_s = s[idx:]
                if isValid(sub_s):
                    path.append(sub_s)
                    ans.append('.'.join(path))
                    path.pop()
                return
            for j in range(idx, len(s)):
                sub_s = s[idx:j+1]
                if len(sub_s) > 3 or int(sub_s) > 255: return
                if len(s) - size_s - len(sub_s) > remaining * 3: continue

                if isValid(sub_s):
                    size = len(sub_s)
                    path.append(sub_s)
                    dfs(s, j + 1, remaining - 1, size_s + size)
                    path.pop()
        dfs(s, 0, 3, 0)

        return ans