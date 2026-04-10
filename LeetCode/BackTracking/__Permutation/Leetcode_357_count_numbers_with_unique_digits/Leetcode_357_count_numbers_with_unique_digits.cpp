/**
 * @brief: Leetcode_统计各位数字都不同的数字个数
 * @link: https://leetcode.cn/problems/count-numbers-with-unique-digits/description/
 * @author: liangj.zhang
 * @date: 10/4/2026
 * 
 * @Diffculty: Medium
 * 
 * @Label: Backtracking & Permutation
 * 
 * @Retrospect(worthy 1 - 5): 4
 * 
 * @thoughts:
 *  + 【思路 1】：纯数学的排列组合思路
 *      第 1 位（最高位），不能为 0，可选数字：1–9，共 9 种选择
 *      第 2 位 可以为 0，但不能与第 1 位重复，剩余可选数字：9 个
 *      第 3 位，不能与前 2 位重复，剩余可选：8 个，
 *      排列形式：9 * A(9, n-1), 其中 A(n, r) = n! / (n - r)!
 * 
 *      + 分析：
 *          + 时间复杂度：O(n)
 *          + 空间复杂度：其实也算 O(n)
 *      + rank:
 *          + 时间效率：0 ms, 击败 100%
 *          + 空间效率：7.63 MB, 击败 81.25%
 */

#include <vector>
#include <iostream>
#include <cassert>
using std::vector;

class Solution {
private:
    static constexpr auto pow = [](int n, int expo) -> int {
        assert(base >= 0 && n >= 0);
        int sum = 1;
        for (int i = 0; i < expo; ++i)
            sum *= n;
        return sum;
    };

	// A(n,r) = n! / (n - r)! ---> [n, n - r + 1]
	static constexpr auto A = [](int n, int r) -> int {
		assert(n >= r);
		int sum = 1;
		for (int i = n; i > n - r; --i)
			sum *= i;
		return sum;
	};
	
	// C(n,r) = n! / ( (n - r)! * r! ) = A(n,r) / r!
	static constexpr auto C = [](int n, int r) -> int {
		assert(n >= r);
		int rFactorial = 1;
		for (int i = 1; i <= r; ++i)
			rFactorial *= i;
		return A(n, r) / rFactorial;
	};
	
	// n 位数，不存在重复数字的可能
	int countNDigitUniqueNumbers(int n) {
        assert(n >= 1);
        if (n == 1) return C(10, 1);
        return 9 * A(9, n - 1);	
    }
	
	static vector<int> rec;
public:
    int countNumbersWithUniqueDigits(int n) {
      	if (n == 0) return 1;
        int sum = 0;
        for (int i = 1; i <= n; ++i) {
            if (rec[i] == 0) {
                rec[i] = countNDigitUniqueNumbers(i);
                // std::cout << i << " " << rec[i] << std::endl;
            }
            sum += rec[i];
        }
        return sum;
    }
};

vector<int> Solution::rec(9, 0);

int main() {
    Solution().countNumbersWithUniqueDigits(8);
}