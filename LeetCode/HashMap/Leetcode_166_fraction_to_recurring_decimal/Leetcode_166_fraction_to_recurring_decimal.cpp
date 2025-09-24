/**
 * @brief: Leetcode_166_分数到小数
 * @link: https://leetcode.cn/problems/fraction-to-recurring-decimal/description/
 * @author: liangj.zhang
 * @date: 24/9/2025
 * 
 * @Difficulty: Medium
 * 
 * @Label: HashMap、Array
 * 
 * @Retrospect(worthy 1 - 5): 3
 * 
 * @thoughts:
 *  + 【思路 1】：哈希 + 数组
 *      我是用的维护一个数组（看了大多数人选择的是 string 的一些方法，包括 to_string, string + string
 *      实际的算数过程，每次记录 除数 起始写入数组的位置；
 *      小数点 . 是放在循环前，后面方便点；
 *      有几处需要注意的地方：
 *          1. 第一次的 除数，即 numerator，第一次不计入 um<int, int> rec 当中；因为循环体，是在小数点之后的;
 *              当我们要写入第一次的 商(quo)
 *          2. 排除掉 0 的情况之后，我们能通过 ^ 异或，很快知道两整数乘积是正是负；
 *          3. 循环中，num 不能被 div 整除的时候，下一次的 num = num * 10; 不是 num / div 之后，再去 * 10;
 * 
 *      + 分析：
 *          + 时间复杂度：
 *              + 整数部分：O(log(num/div))
 *              + 小数部分：O(div)
 *              + 括号插入：O(div)
 *              + 总结：O(log(numerator)+denominator)
 *          + 空间复杂度：哈希表，最多存储 div 个不同余数（0 ~ div-1） => O(denominator)
 *      + rank:
 *          + 时间效率：0 ms, 击败 100%
 *          + 空间效率：8.51 MB, 击败 92.27%
 */

#include <string>
#include <iostream>
using std::cout;
using std::endl;
using std::string;

#include <unordered_map>
#include <cmath>
#define MAXLEN 10002
using std::unordered_map;
#define um unordered_map

// 【思路 1】：哈希 + 数组
class Solution {

private:
    static char str[MAXLEN];
    static um<int, int> rec;
    static int cursor;

    int addQuotientIntoArray(long long quo) {

        int res(cursor + 1);
        // get length
        int len(1), tmp(quo);
        while (tmp /= 10) ++len;
        // write into str[]
        for (int i = len - 1; i >= 0; --i) 
            str[++cursor] = (quo / (int)pow(10, i)) % 10 + '0';

        return res;
    }

public:
    string fractionToDecimal(int numerator, int denominator) {

        if (numerator == 0) return "0";
        
        long long num(numerator), div(denominator), quo, rem; // number, divisor, quotient, reminder
        // positive or negtive -> signed or not
        int res_start;
        if ((numerator ^ denominator) < 0){
            str[0] = '-';
            res_start = 0;
       } 
       else 
            res_start = 1;

        // change to positive
        if (num < 0) num = -1 * num;
        if (div < 0) div = -1 * div;
        // loop or not
        bool attr_loop = false;
        cursor = 0; // 采用 ++cursor，为符号位留一个位置；
        rec.clear();

        // for effective to extract the first step
        quo = num / div;
        rem = num % div;
        // . dot 前面的整数不计入循环体内
        addQuotientIntoArray(quo);
        num = rem * 10;
        // float or int
        if (rem) {
            str[++cursor] = '.';
        } 

        while (rem) {

            bool b_div = num >= div;
            if (b_div) {

                quo = num / div;
                rem = num % div;
            } else 
                quo = 0;
            //cout << num << endl;

            // record divisor
            if (rec.find(num) == rec.end())
                rec.insert({num, addQuotientIntoArray(quo)});
            else {

                attr_loop = true;
                break;
            }
            // update
            num = (b_div ? rem : num) * 10;
        }

        if (!attr_loop) 
            str[++cursor] = '\0';
        else {

            // [rec[num], cursor]
            str[++cursor + 1] = ')';
            str[++cursor + 1] = '\0';
                // cursor -> ')'; cursor - 1 => ' ' 未赋值的
            int brace_start = rec[num];
            for (int i = cursor - 1; i > brace_start; --i)
                str[i] = str[i - 1];
            str[brace_start] = '(';
        }

        return string(str + res_start);
    }
};
int Solution::cursor = 0;
char Solution::str[] = {};
um<int, int> Solution::rec = {};

int main() {

    int numerator = 210;
    int denominator = 113;
    cout << Solution().fractionToDecimal(numerator, denominator) << endl;
}