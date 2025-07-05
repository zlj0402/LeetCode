/**
* @brief: Leetcode_1394_找出数组中的幸运数
* @link: https://leetcode.cn/problems/find-lucky-integer-in-an-array/description
* @author: liangj.zhang
* @date: 5/7/20205
* 
* @Difficulty: Easy
* 
* @Label: Array、Map(STL)
* 
* @Again(worthy 0~5): 0
* 
* @thoughts
* 【1】用 map 写，倒着找幸运数，这样如果有，倒着找的话，理论更快（如果 N 能达到条件的话）
*       分析：
*           时间复杂度：O(N * logN) 的查找，最后找到幸运数的最糟糕情况 O(500)，O(NlogN) + O(500)，结果还是 O(NlogN)；
*           空间复杂度：红黑树用到的空间，很多时候比 N 要大一些；
*       rank:
*           时间效率：0 ms, 击败 100%
*           空间效率：13.51 MB, 击败 91.57%
*                   
* 
* 【2】用数组固定大小，因为题目最多就 500 个数，且范围在 [1, 500];
*       + 用 static 的类属性数组，这样后面的 cases 都是用的同一个；
*       + 就是每次需要遍历 500 下；
*       + 但是，相对于 N 较大时，O(logN）的查找，咱们数组的 O(1) 有优势；
*       分析：
*           时间复杂度：清 0 一次 O(500)，计数一次 O(N), 倒着找幸运数 O(500), 只有计数那次，算 O(N); chat 说的，说我认为 遍历 500 次，不算 O(N)，算 O(1);
*                       chat: 但其实，时间复杂度不是“单纯比大小”，而是看“是否随着 N 增长而变化”：
*                               + 固定 500 次，不变 → O(1)；
*                               + N 次变化 → O(N)。
*           空间复杂度：O(500) = O(1)
*       rank:
*           时间效率：0 ms, 击败 100%
*           空间效率：13.35 MB, 击败 98.88%
*/


#include <vector>
using std::vector;

// 【2】
#define MAXLEN 501

class Solution {
private:
    static int ary[MAXLEN];

public:
    int findLucky(vector<int>& arr) {

        for (int i = 1; i < MAXLEN; ++i)
            ary[i] = 0;

        for (auto& e : arr) 
            ++ary[e];

        int ret = -1;
        for (int i = MAXLEN - 1; i > 0; --i) {

            if (ary[i] == i) {

                ret = i;
                break;
            }
        }

        return ret;
    }
};

int Solution::ary[MAXLEN];

// 【1】
/*
#include <map>
using std::map;

class Solution {
private:
    map<int, int> rec;
public:
    int findLucky(vector<int>& arr) {

        rec.clear();
        for (auto& e : arr)
            ++rec[e];
        int ret = -1;
        for (auto it = rec.rbegin(); it != rec.rend(); ++it) {

            if (it->first == it->second) {

                ret = it->first;
                break;
            }
        }
        return ret;
    }
};*/