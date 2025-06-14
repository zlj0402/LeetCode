//
// Created by liangj.zhang on 14/6/2025
// 
// URL: https://leetcode.cn/problems/search-insert-position/description
// 
// Difficulty: Easy
// 
// Label: Binary Search
// 
// description:
//      + 虽然简单，但边界不好琢磨啊
//

#include <vector>
#include <iostream>
using std::cout;
using std::endl;
using std::vector;

class Solution {
public:
    int searchInsert(vector<int>& nums, int target) {

        int l, r, mid, res;
        l = 0;
        r = nums.size() - 1;
        res = -1;

        while (l <= r) {

            mid = (r - l) / 2 + l;
            if (nums[mid] < target) {
                l = mid + 1;
            }
            else if (nums[mid] > target) {
                r = mid - 1;
            }
            else {

                res = mid;
                break;
            }
        }

        return res == -1 ? l : res;
    }
};

int main() {

    int target = 7;
    vector<int> nums = { 1,3,5,6 };
    cout << (new Solution())->searchInsert(nums, target);
}