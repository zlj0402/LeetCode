//
// Created by liangj.zhang on 13/6/2025
// 
// URL: https://leetcode.cn/problems/majority-element/description
// 
// Difficulty: Easy
// 
// Label: Sort、...
// 
// 思路：
//      看到题目，想了一下，我能想到 时间复杂度为 O(n)，空间效率为 O(1) 的只有 快排的变式；暂时想不到其他方式；
//      但我还是将题目，放在了 Misc-Skill 的目录下，没有放在 Sort 目录题下面；
//      
//      换一下描述：就是找 Kth 大的值，且 K 就是中值；排在中间的那两个或一个位置的数；
//      目前阶段对快排比较熟，打开编译器，手写代码，Cases，不到 10 min 就提交了；
// 
// rank: brilliant
//      时间效率：0 ms, 击败 100%
//      空间效率：27.42 MB, 击败 98.22%
//


#include <vector>
#include <iostream>
using std::vector;
using std::cout;
using std::endl;

#include <ctime>
using std::swap;

class Solution {

private:

    int __partition(int* arr, int l, int r) {

        std::swap(arr[l], arr[rand() % (r - l + 1) + l]);
        int v = arr[l];

        int i = l + 1;
        int j = r;

        while (1) {

            while (i <= r && arr[i] < v) i++;
            while (j >= i && arr[j] > v) j--;
            if (i >= j) break;
            swap(arr[i++], arr[j--]);
        }
        swap(arr[l], arr[j]);

        return j;
    }

    void quickSort(int* arr, int l, int r, int rank) {

        if (l >= r)
            return;

        int p = __partition(arr, l, r);
        if (p < rank)
            quickSort(arr, p + 1, r, rank);
        else if (p > rank)
            quickSort(arr, l, p - 1, rank);
        else
            return;
    }

public:
    int majorityElement(vector<int>& nums) {

        srand(time(nullptr));

        int rank = nums.size() / 2;

        quickSort(nums.data(), 0, nums.size() - 1, rank);

        return nums[rank];
    }
};

int main() {

    vector<int> nums = { 1, 2, 3, 4, 10, 9, 8, 7, 6, 5 };

    cout << (new Solution())->majorityElement(nums);
}