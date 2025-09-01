"""
@brief: Leetcode_125_验证回文串
@link: https://leetcode.cn/problems/valid-palindrome/
@author: liangj.zhang
@date: 31/8/2025

@Difficulty: Easy

@Label: Two pointers

@Retrospect(worthy 1 - 5): 2

@thoughts:
    + 【思路 1】：相向双指针
        从双指针题刷过来的，自然想到的首先是这个；
        每次两个指针都往里面找到下一位符合要求的字符；
        while (l < r) => 不要加等于号（l <= r），" " => r = 0,
        如果是 <=，那么 r 会变为 -1

        + 分析：
            + 时间复杂度：O(n)
            + 空间复杂度：O(1)
                + Q: 双指针遍历了字符串 n 的长度，每次都有使用临时变量，那 n 次遍历，空间复杂度算 O(n) 吗？
                + A: 不算
                    + 代码里用到的临时变量：isalpha、isalpha2、l、r 等，都是常数级别的额外内存。
                    + >>> 它们不会随着字符串长度 n 的增加而增加。<<<
                    + 即使循环执行了 n 次，这些变量也只是被 重复覆盖赋值，并不会额外分配 n 个空间。

        + rank:
            + 时间效率：11 ms, 击败 54.97%
            + 空间效率：17.73 MB, 击败 76.75%

    + 【思路 2】
        python 特有的解法，用 filter() 过滤得到符合的字符，并连接起来；
        最后用切片 [::-1]，得到一个相反的字符串；两者比较；
"""


# 【思路 1】
"""
class Solution:
    
    def isPalindrome(self, s: str) -> bool:
        l = 0
        r = s.__len__() - 1

        while l < r:
            while l < r and not ((s[l].isalpha() and s[l].isascii()) or s[l].isdecimal()): l += 1
            while l < r and not ((s[r].isalpha() and s[r].isascii()) or s[r].isdecimal()): r -= 1

            is_dec = s[l].isdecimal()
            is_dec2 = s[r].isdecimal()

            if (is_dec ^ is_dec2):
                return False
            elif is_dec:
                if s[l] != s[r]:
                    return False
            elif not (s[l] == s[r] or ord(s[l]) - ord(s[r]) == 32 or ord(s[r]) - ord(s[l]) == 32):
                return False
            
            l += 1
            r -= 1
        
        return True
"""


# 【思路 2】
class Solution:
    def isPalindrome(self, s: str) -> bool:
        s2 = ''.join(filter(lambda c: (c.isalpha() and c.isascii()) or c.isdecimal(), s)).lower()
        return s2 == s2[::-1]


def main():
    s = "P0"
    print(Solution().isPalindrome(s))


if __name__ == "__main__":
    main()
