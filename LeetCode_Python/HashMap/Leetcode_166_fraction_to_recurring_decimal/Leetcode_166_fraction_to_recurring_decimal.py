"""
@brief: Leetcode_166_分数到小数
@link: https://leetcode.cn/problems/fraction-to-recurring-decimal/description/
@author: liangj.zhang
@date: 24/9/2025

@Difficulty: Medium

@Label: HashMap, Array

@Retrospect(worthy 1 - 5): 3

@thoughts:
    + 【思路 1】：哈希 + 字符串函数
    - 注意事项：
        1. 第一次的除数 numerator，不计入哈希表 rec，因为循环体是在小数点之后写入；
            当写入第一次商(quo)时特殊处理。
        2. 排除 0 的情况后，通过异或可以快速判断两个整数乘积正负。
        3. 循环中，num 不能被 div 整除时，下一次 num = num * 10，而不是先 num / div 再 *10。

    + 分析：
        - 时间复杂度：O(log(numerator)+denominator2)
        - 空间复杂度：O(denominator)

    + rank:
        - 时间效率：0 ms, 击败 100%
        - 空间效率：17.65 MB, 击败 75.79%
"""

class Solution:
    def fractionToDecimal(self, numerator: int, denominator: int) -> str:
        if numerator == 0: return "0"
        res = ''
        if (numerator ^ denominator) < 0:
            res += '-'
        
        rec = dict()
        num, den, quo, rem = abs(numerator), abs(denominator), 0, 0
        # 整数部分
        quo = num // den
        rem = num % den
        res += str(quo)
        if rem:
            res += '.'
        else:
            return res
        num = rem * 10

        loop = False
        cursor = len(res)
        while rem:
            b_div = num >= den
            if b_div:
                quo = num // den
                rem = num % den
            else:
                quo = 0

            if rec.get(num) is None:
                res += str(quo)
                rec[num] = cursor
                cursor += len(str(quo))
            else:
                loop = True
                break

            num = (rem if b_div else num) * 10

        return res[:rec[num]] + '(' + res[rec[num]:] + ')' if loop else res

def main():
    numerator = 4
    denominator = 333
    print(Solution().fractionToDecimal(numerator, denominator))

if __name__ == "__main__":
    main()