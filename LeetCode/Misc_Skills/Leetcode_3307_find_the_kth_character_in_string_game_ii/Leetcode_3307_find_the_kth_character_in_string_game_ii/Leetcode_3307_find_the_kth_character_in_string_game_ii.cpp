/**
* @brief: Leetcode_3307_找出第K个字符II
* @link: https://leetcode.cn/problems/find-the-k-th-character-in-string-game-ii/description
* @author: liangj.zhang
* @date: 4/7/2025
* 
* @Difficulty: Hard
* 
* @Label: Recursion
* 
* @Again(worthy 0~5): 4
* 
* @brief content: 字符串长度每次翻倍，后一半要么是前一半原来的样子，要么是前一半每个字符+1，在拼接；初始第一次永远是'a'；求操作之后，第 K 个字符；
* 
* @thoughts:
*   给了字符 K => 能确定是第几次（times）操作之后确定了 K 的值；
*   且 能得到该字符，是由上一次（即前一半）哪个位置的字符变换得到的（变换：要么是前一个字符，原封不动，要么是 +1 之后的字符，[超过 'z'，重新变为 'a']）；
*   
*   新位置（即，上一次字符变换的位置）的字符，也是由再上一次的某个字符得来的，过程同上；
*   我们记录，该字符是否是由 [1] 操作变换得来的 => 因为我们递归时传递了 times，kth 位置的字符，是由第几次操作得来的，可以 O(1) 与参数的 operations[] 的位置比较一下；
*   记录了 K 位置的字符，从最初的 'a' 变换了几次（reverse_times）得到的 K 位置字符；
*   返回时，只需要 'a' + reverse_times % 26; 
*   简言之，关注上一次的位置 & 上一次是否是 [1] 操作变换得到
* 
*   分析：
*       时间复杂度：log(K) 的递归次数
*       空间复杂度：log(K) * （每次的参数 + 内部变量）
* 
*   rank:
*       时间效率：0 ms, 击败 100%
*       空间效率：27.91 MB, 28.13%
*/


#include <vector>
#include <iostream>
using std::vector;
using std::cout;
using std::endl;

#include <iostream>
#include <cmath>
#define LL_t long long 

class Solution {
private:
    int reverse_times;
    vector<int>* opr;

    void func(LL_t kth, int times) {

        if (times < 0)
            return;

        LL_t last_k = kth;
        if (kth > pow(2, times)) {

            last_k = kth - pow(2, times);
            if ((*opr)[times] == 1)
                ++reverse_times;
        }

        func(last_k, times - 1);
    }

public:
    char kthCharacter(long long k, vector<int>& operations) {

        reverse_times = 0;
        opr = &operations;
        int times = int(log2(k)) < log2(k) ? int(log2(k)) + 1 : log2(k);

        func(k, times - 1);

        return 'a' + reverse_times % 26;
    }
};

int main() {

    LL_t k = 12145134613;
    vector<int> operations = { 0,0,0,0,1,0,0,0,1,1,1,1,1,0,1,0,0,0,1,0,0,0,0,0,1,1,0,1,0,0,1,1,1,1,1 };

    cout << (new Solution())->kthCharacter(k, operations);
}