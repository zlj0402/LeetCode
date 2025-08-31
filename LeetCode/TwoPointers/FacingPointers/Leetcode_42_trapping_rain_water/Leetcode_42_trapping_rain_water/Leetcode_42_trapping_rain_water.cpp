//
// Created by liangj.zhang on 12/6/2025
// 
// URL: https://leetcode.cn/problems/trapping-rain-water/description
// 
// Difficulty: Hard
// 
// Label: Two Pointers、Dynamic Programming
// 
// 思路：
//  + 找到第一个高度不为 0 的位置；
//  + 两指针指向这；那么正戏开场；
//  + 解题的关键点：
//      1. 如何找到高度上升趋势与高度下降趋势的转折点；（雨水就落在两转折点之间）
//          1.1 右指针边走，边计算两转折点之间的高度和 （i, j）-> 开区间之内的
//          1.2 如果有连续的等高度，不算下降，直到最后一位；
// 
//  + 上面的思考，还是片面了；
//      >>> 一个位置 i 的上方的存水量，是由该位置，左边最高柱 和 右边最高柱 的较小值 - height[i] 得到；<<<
//  
// 【1】
//  + 既然是由 i 两边最高柱决定；
//  + 那么我们从左向右遍历一遍，确定每个位置，左边的最大值 left_max[]；
//  + 从右向左遍历一遍，确定每个位置，右边的最大值 right_max[]；
//  + 这样，一个位置 i 上方的出水量，就是 std::min(left_max[i], right_max[i]) - height[i]
//  + 第3次，再遍历一遍，得到结果 total；
// 
//  + 时间效率：3 * O(n) => O(n)
//  + 空间效率：2 * O(n) => O(n)
//  + 此种方式，被叫做动态规划；
// 
// rank:
//  + 时间效率：3 ms, 击败 32.75%
//  + 空间效率：25.55 MB, 击败 68.43%
// 
// 【2】. 双指针
//  + 理解了上面的动态方式，双指针的方式才更容易理解；
//  + 两端的对撞指针：l, r
//  + 记录左边的最大值 left_max（lm）, 和右边的最大值 right_max（rm）
//  + 当 lm < rm，我们来处理左边的遍历；
//      + 因为，我们知道了当前位置 i 的右边最大值（不确定，可能有更高的），但已经比记录 i 的左边最大值 lm 大；
//  + 新遍历到的 height[i] 比 max 大，我们记录；
//  +                     比 max 小，说明有沟，得到位置 i 的储水值，max - height[i]
//  
// + 时间效率：1 * O(n)
// + 空间效率：O(1)
// 
// rank: great
//  + 时间效率：0 ms, 击败 100%
//  + 空间效率：25.36 MB, 击败 94.37%
//


#include <iostream>
#include <vector>
using std::vector;
using std::cout;
using std::endl;


// 【2】
class Solution {
public:
    int trap(vector<int>& height) {
        
        int size = height.size();
        int lm, rm;
        lm = rm = 0;

        int l, r;
        l = 0; r = size - 1;

        int total = 0;

        while (l <= r) {
        
            if (lm <= rm) {

                if (height[l] > lm) 
                    lm = height[l];
                else 
                    total += lm - height[l];
                l++;
            }
            else {

                if (height[r] > rm) 
                    rm = height[r];
                else 
                    total += rm - height[r];
                r--;
            }
        }

        return total;
    }
};

// 【1】
/*
#define MAXLEN 20001

class Solution {

private:
    int left_max[MAXLEN];
    int right_max[MAXLEN];
public:
    int trap(vector<int>& height) {

        int size = height.size();

        int lm = height[0];
        for (int i = 0; i < size; i++) {

            if (height[i] > lm)
                lm = height[i];
            left_max[i] = lm;
        }

        int rm = height[size - 1];
        for (int i = size - 1; i >= 0; i--) {
            
            if (height[i] > rm)
                rm = height[i];
            right_max[i] = rm;
        }

        int total = 0;
        for (int i = 0; i < size; i++) {

            total += std::min(left_max[i], right_max[i]) - height[i];
        }

        return total;
    }
};
*/

int main() {

    vector<int> height = { 4,2,0,3,2,5 };

    cout << (new Solution())->trap(height);
}