/**
 * @brief: Leetcode_42_接雨水
 * @link: https://leetcode.cn/problems/trapping-rain-water/description
 * @author: liangj.zhang
 * @date: 12/6/2025
 * 
 * @Difficulty: Hard
 * 
 * @Label: Two Pointers, Dynamic Programming
 * 
 * @thoughts:
 *      思路：
 *      + 找到第一个高度不为 0 的位置；
 *      + 两指针指向这；那么正戏开场；
 *      + 解题的关键点：
 *          1. 如何找到高度上升趋势与高度下降趋势的转折点；（雨水就落在两转折点之间）
 *              1.1 右指针边走，边计算两转折点之间的高度和 （i, j）-> 开区间之内的
 *              1.2 如果有连续的等高度，不算下降，直到最后一位；
 * 
 *      + 上面的思考，还是片面了；
 *          >>> 一个位置 i 的上方的存水量，是由该位置，左边最高柱 和 右边最高柱 的较小值 - height[i] 得到；<<<
 *      
 *      + 可能后续会产生的疑问：
 *          + Q: 为什么不能 rm >= lm 时，r 一直移动呢？非得谁小，移动哪边的指针；
 *              A: 就拿右边大举例子，如果 rm 一直大，一直往左走，
 *                  某个位置 x 的柱子，只能知道其右边的最大值，不能知道其左边的最大值；所以不合适；
 *          + Q: 为什么哪边小，走哪边，能保持计算不出错？中间有更高的柱子，不影响吗？
 *              A: 位置 x 的储水高度（不考虑 height[x]），是由左右两边，从一端到其这里，最低的那一方决定；
 *                  这一点，决定了 lm / rm，谁低走哪边的指针；
 *                  即使中间有更高的柱子，就是比如右边，位置 x 较小的左边的最高值 lm 定了，那么后面移动右指针的过程中，
 *                  发现有更高的 rm，也不会影响位置 x 柱子的高度；（因为柱子左右两边的最值，由较小方决定）
 * 
 * 【1】动态规划解法
 *      + 从左向右遍历一遍，确定每个位置，左边的最大值 left_max[]
 *      + 从右向左遍历一遍，确定每个位置，右边的最大值 right_max[]
 *      + 一个位置 i 上方的出水量 = min(left_max[i], right_max[i]) - height[i]
 *      + 第3次遍历一遍，得到结果 total
 * 
 *      + 时间复杂度：3 * O(n) => O(n)
 *      + 空间复杂度：2 * O(n) => O(n)
 *      + 此种方式，被叫做动态规划
 * 
 *      + rank:
 *          + 时间效率：3 ms, 击败 32.75%
 *          + 空间效率：25.55 MB, 击败 68.43%
 * 
 * 【2】双指针解法
 *      + 理解了上面的动态方式，双指针的方式才更容易理解；
 *      + 两端的对撞指针：l, r
 *      + 记录左边的最大值 left_max（lm）, 和右边的最大值 right_max（rm）
 *      + 当 lm < rm 时，处理左边的遍历；
 *          + 我们知道当前位置 i 的右边最大值已大于 lm，所以可以决定当前位置存水
 *      + 新遍历到的 height[i] 比 lm 大，则更新 lm；
 *      + 否则有沟，存水量 = lm - height[i]
 * 
 *      + 时间复杂度：O(n)
 *      + 空间复杂度：O(1)
 * 
 *      + rank:
 *          + 时间效率：0 ms, 击败 100%
 *          + 空间效率：25.36 MB, 击败 94.37%
 */


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