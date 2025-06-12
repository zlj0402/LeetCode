//
// Created by liangj.zhang on 12/6/2025
// 
// URL: https://leetcode.cn/problems/single-number/description
// 
// 思路：
//	【1】
//	+ 这题的做法有很多种，既然分类为技巧类型的题，领略之后，确实有种醍醐灌顶，茅塞顿开的感觉；
//	+ 第一眼，自己的想法是 unordere_set，因为其他数必定是出现两次，第二次出现的时候，给他删了；
//	+ 留下的必定是唯一的答案；
//	+ 优点：简单，容易想到
//	+ 缺点：us 会占用额外的空间，hash 的插入查找，虽说是 O(1)，但常数比较大；
// 
// rank:
//	+ 时间效率：16 ms, 击败 6.84%
//	+ 空间效率：23.25 MB, 击败 13.69%
// 
// 【2】
//	+ 看了讨论和题解，拍案叫绝的方式：用位运算：异或；
//	+ 还去回顾了一眼，异或运算的基本性质；此处就用到了 >> 异或运算的结合性 & 自反性 & 恒等性 <<
//	+ 结合性：a ^ b ^ c == a ^ (b ^ c) 
//	+ 自反性：a ^ a == 0
//	+ 恒等性：a ^ 0 == a
//	+ ==> 所以， a ^ b ^ b ^ c ^ c == a ^ (b ^ b) ^ (c ^ c) == a ^ 0 ^ 0 = a
//	+ 优点：位运算快，还不占用额外空间；
//	+ 缺点：没有缺点
// 
// rank: great
//	+ 时间效率：0 ms, 击败 100%
//	+ 空间效率：20.31 MB, 击败 69.79%
//

#include<vector>
using std::vector;

// 【2】
class Solution {

private:
    int ret;
public:
    int singleNumber(vector<int>& nums) {

        ret = 0;
        for (auto& e : nums) {
            ret ^= e;
        }
        return ret;
    }
};

// 【1】
/*
#include <unordered_set>
#define us unordered_set

class Solution {
public:
    int singleNumber(vector<int>& nums) {

        us<int> s;
        for (auto& e : nums) {

            if (s.find(e) != s.end())
                s.erase(e);
            else
                s.insert(e);
        }

        return *s.begin();
    }
};
*/