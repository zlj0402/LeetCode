//
// Created by liangj.zhang on 11/6/2025
// 
// URL: https://leetcode.cn/problems/group-anagrams/submissions/635969430
// 
// 思路：
//	【1】. 字母值之和 & 字母数 & 字母顺序后的字符之间的差和 都相同时，那么该单词一定是相同的；
//      但是，要排一次序肯定是比较慢的；
//      这个就没考虑做了；
// 
//  【2】. 从讨论中，看到别人看到，有大佬用质数乘积的方式做的；
//      + 因为：相同位数，都是质数的乘积，结果是唯一的；
//      + 一开始，就想到了，第 26 位质数，是 101，那么最长的字符串的话 100，这个计算会超出 long 的取值范围；
//      + 这是第二种方式做的，第一种做的方式是 【3】
// 
//  【3】. 统计 ‘a' - 'z' 的字符频率，组合成 string 类型，使用 map<string, vector<string>> 的类型；
//      
// rank:
//  【3】. 
//      时间效率：29 ms, 击败 15.33%
//      空间效率：25.72 MB, 击败 17.42%
//  【2】.
//      时间效率：11 ms, 击败 95.32%
//      空间效率：22.52 MB, 击败 99.13%
//

#include <iostream>
#include <string>
#include <vector>
using std::string;
using std::vector;
using std::cout;
using std::endl;

// 【3】.
/*
#include <map>
using std::map;

class Solution {

private:
    map<string, vector<string>> res;

public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {

        res.clear();
        vector<vector<string>> ret;

        for (auto& str : strs) {

            int count[26] = {};
            const char* s = str.c_str();
            while (*s)
                count[*s++ - 'a'] += 1;

            char str_c[27] = {};
            for (int i = 0; i < 26; i++)
                str_c[i] = '0' + count[i];
            str_c[26] = '\0';

            res[string(str_c)].push_back(str);
        }

        for (auto& item : res)
            ret.push_back(item.second);

        return ret;
    }
};*/

// 【2】.
#include <map>
#define UL unsigned long
using std::map;

class Solution {

private:

    static int primes[26];

    static bool isPrime(int num) {
        
        for (int i = 2; i <= (num >> 1) + 1; i++) {
            
            if (num % i == 0)
                return false;
        }

        return true;
    }

    static void getPrimes();

public:

    Solution() {
        
        getPrimes();
    }

    vector<vector<string>> groupAnagrams(vector<string>& strs) {

        map<UL, vector<string>> res;
        vector<vector<string>> ret;

        for (auto& str : strs) {
            
            UL val = 1UL;
            const char* s = str.c_str();
            while (*s) {
                
                val *= Solution::primes[*s++ - 'a'];
            }

            res[val].push_back(str);
        }

        for (auto& item : res)
            ret.push_back(std::move(item.second));

        return ret;
    }
};

int Solution::primes[26] = {};

void Solution::getPrimes() {

    int count = 0;
    int num = 2;

    while (count < 26) {

        if (isPrime(num))
            primes[count++] = num;

        num++;
    }
}

int main() {

    vector<string> strs = { "eat", "tea", "tan", "ate", "nat", "bat" };

    vector<vector<string>> ret = (new Solution())->groupAnagrams(strs);

    for (auto& item : ret) {
        
        for (auto& it : item)
            cout << it << " ";

        cout << endl;
    }
}