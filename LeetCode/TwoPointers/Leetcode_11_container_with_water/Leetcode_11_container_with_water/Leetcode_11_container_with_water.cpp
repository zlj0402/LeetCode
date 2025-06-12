//
// Created by liangj.zhang on 12/6/2025
// 
// URL: https://leetcode.cn/problems/container-with-most-water/description
// 
// 思路：算完全自己想的，没有参考讨论和题解；-- 唯一被提示，是题目分类；
//      + 双指针
//      + 体会过程，不然你可能会有疑问：错过的哪些可能，不会有更大值的可能吗？
//      + 指针从两端开始
//      + 在一个面积求得之后的基础上，将矮的一边，往里移动，找到更高一点的边，才有可能比当前的面积大（因为往里动，宽 width 在变小）
//      + 不管这次移动后的结果有没有比 max_area 更大，你得继续上一步，找到比当前面积更大一点的可能
// 
// ps:
//      下面的两种方式，是完全一样的；减少一些变量的定义；
//      但是效果上，空间效率差别不大；
// 
// rank:
//      + 时间效率：0 ms, 击败 100%
//      + 空间效率：
//          【1.1】
//              61.62 MB, 击败 30.8%
//          【1.2】
//              61.48 MB, 击败 75.32%
//


#include <vector>
#include <iostream>
using std::cout;
using std::endl;
using std::vector;

// 【1.2】
class Solution {
public:
    int maxArea(vector<int>& height) {

        int area, max_area;
        area = max_area = 0;

        int i, j;
        i = 0;
        j = height.size() - 1;

        int h;
        while (j > i) {

            h = std::min(height[i], height[j]);
            area = (j - i) * h;

            if (area > max_area)
                max_area = area;

            if (height[i] == h)
                while (++i < j && height[i] < h);
            else
                while (--j > i && height[j] < h);
        }

        return max_area;
    }
};

// 【1.1】
/*
class Solution {
public:
    int maxArea(vector<int>& height) {

        int area, max_area;
        area = max_area = 0;

        int i, j;
        i = 0;
        j = height.size() - 1;

        int h;
        while (j > i) {

            h = std::min(height[i], height[j]);
            area = (j - i) * h;

            if (area > max_area)
                max_area = area;

            if (height[i] == h)
                while (++i < j && height[i] < h);
            else
                while (--j > i && height[j] < h);
        }

        return max_area;
    }
};
*/

int main() {

    vector<int> height = { 1,8,6,2,5,4,8,3,7 };
    cout << (new Solution())->maxArea(height);
}