/**
 * @brief: Leetcode_125_验证回文串
 * @link: https://leetcode.cn/problems/valid-palindrome/
 * @author: liangj.zhang
 * @date: 31/8/2025
 * 
 * @Difficulty: Easy
 * 
 * @Label: Two pointers
 * 
 * @Retorspect(worthy 1 - 5): 2
 * 
 * @thoughts:
 *      + 【思路 1】：相向双指针
 *          从双指针题刷过来的，自然想到的首先是这个；
 *          每次两个指针都往里面找到下一位符合要求的字符；
 *          while (l < r) => 不要加等于号（l <= r），" " => r = 0, 如果是 <=，那么 r 会变为 -1
 *          
 *          + 分析：
 *              + 时间复杂度：O(n)
 *              + 空间复杂度：O(1)
 *                  + Q: 双指针遍历了字符串 n 的长度，每次都有使用临时变量，那 n 次遍历，空间复杂度算 O(n) 吗？
 *                  + A: 不算
 *                      + 代码里用到的临时变量：isalpha、isalpha2、l、r 等，都是常数级别的额外内存。
 *                      + >>> 它们不会随着字符串长度 n 的增加而增加。<<<
 *                      + 即使循环执行了 n 次，这些变量也只是被 重复覆盖赋值，并不会额外分配 n 个空间。
 *      
 *          + rank:
 *              + 时间效率：0 ms, 击败 100%
 *              + 空间效率：9.63 MB, 击败 95.95%
 */

#include <iostream>
#include <string>
using std::cout;
using std::endl;
using std::string;

#define STEP 32

class Solution {

private:
inline bool isAlpha(char v) {

    if ((v >= 'a' && v <= 'z') || (v >= 'A' && v <= 'Z'))
        return true;
    return false;
}

inline bool isDigit(char v) {
    return v >= '0' && v <= '9';
}
    
public:
    bool isPalindrome(string s) {
        
        int l = 0;
        int r = s.size() - 1;

        while (l < r) {

            while (l < r && !(isAlpha(s[l]) || isDigit(s[l]))) ++l;
            while (l < r && !(isAlpha(s[r]) || isDigit(s[r]))) --r;

            bool isalpha = isAlpha(s[l]);
            bool isalpha2 = isAlpha(s[r]);

            if (isalpha ^ isalpha2)
                return false; 
            else if (!isalpha) {
                if (s[l] != s[r])
                    return false;
            }
            else if (!(s[l] == s[r] || s[l] - s[r] == STEP || s[r] - s[l] == STEP))
                return false;

            ++l;
            --r;
        }
        return true;
    }
};

int main() {
    string str = "A man, a plan, a canal: Panama";

    Solution sol;
    sol.isPalindrome(str);
}
