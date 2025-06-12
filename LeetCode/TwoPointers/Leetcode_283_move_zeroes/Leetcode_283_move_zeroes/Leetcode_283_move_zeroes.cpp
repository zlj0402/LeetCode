//
// Created by liangj.zhang on 12/6/2025
// 
// URL: https://leetcode.cn/problems/move-zeroes/description
// 
// 思路：
//      + 就像这道题的分类，双指针
//      + 唯一注意点，就是边界；
//      + 第一次将两指针，遍历到第一个 0 的位置；
//      + 之后，让 i 保持在 0 区的第一位，j 保持在 0 区的最后一位后面；
// 
// rank: brilliant
//  + 时间效率：0 ms, 击败 100%
//  + 空间效率：23.18 MB, 击败 99.8%
//


#include <vector>
#include <iostream>
using std::vector;
using std::cout;
using std::endl;
using std::swap;

class Solution {
public:
    void moveZeroes(vector<int>& nums) {

        int i, j;
        i = j = 0;

        while (i < nums.size() && nums[i] != 0) { i++; j++; }

        while (true) {

            while (j < nums.size() && nums[j] == 0) { j++; }

            if (j < nums.size())
                swap(nums[i++], nums[j++]);
            else
                break;
        }
    }
};

int main() {

    vector<int> nums = { 0 };

    (new Solution())->moveZeroes(nums);

    for (auto item : nums)
        cout << item << " ";
    cout << endl;
}