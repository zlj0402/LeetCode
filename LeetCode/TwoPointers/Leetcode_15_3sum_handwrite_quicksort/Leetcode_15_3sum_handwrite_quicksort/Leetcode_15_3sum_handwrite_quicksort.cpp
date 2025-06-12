//
// Cerated by liangj.zhang on 12/6/2025
// 
// URL: https://leetcode.cn/problems/3sum/description
// 
// 思路：
//      + 做法跟之前写过的，排序后 + 双指针 一样；
//      + 只不过这次是手写快排，在完全一样的双指针；
// 
// rank:
//  + 时间效率：43 ms, 击败 96.93%
//  + 空间效率：28.48 MB, 击败 59.53%
//


#include <iostream>
#include <vector>
using std::cout;
using std::endl;
using std::vector;

using std::swap;
#include <ctime>

template<typename T>
int __partition(T arr[], int l, int r) {
    
    // 随机交换
    swap(arr[l], arr[rand() % (r - l + 1) + l]);
    T v = arr[l];

    // [l + 1, r] 范围内交换数据
    int i = l + 1;
    int j = r;
    while (true) {

        while (i <= j && arr[i] < v) i++;
        while (j >= i && arr[j] > v) j--;
        if (i >= j) break;
        swap(arr[i++], arr[j--]);
    }
    swap(arr[l], arr[j]);

    return j;
}

template<typename T>
void __quickSort(T arr[], int l, int r) {
    
    // 递归终止条件
    if (l >= r)
        return;

    // 递归分化，主要过程
    int p = __partition(arr, l, r);

    __quickSort(arr, l, p - 1);
    __quickSort(arr, p + 1, r);
}

template<typename T>
void quickSort(T arr[], int n) {

    srand(time(nullptr));
    __quickSort(arr, 0, n - 1);
}

class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {

        quickSort(nums.data(), nums.size());

        for (auto& item : nums)
            cout << item << " ";
        cout << endl;

        vector<vector<int>> ret;

        for (int i = 0; i < nums.size() - 2; i++) {

            if (i && nums[i] == nums[i - 1]) continue;

            int target = -1 * nums[i];
            int m = i + 1;
            int n = nums.size() - 1;

            while (m < n) {

                if (nums[m] + nums[n] < target)
                    while (++m < n && nums[m] == nums[m - 1]);
                else if (nums[m] + nums[n] > target)
                    while (--n > m && nums[n] == nums[n + 1]);
                else {

                    ret.push_back(vector<int>{nums[i], nums[m], nums[n]});
                    while (++m < n && nums[m] == nums[m - 1]);
                    while (m < --n && nums[n + 1] == nums[n]);
                }
            }
        }

        return ret;

    }
};

int main() {

    vector<int> nums = { -1,0,1,2,-1,-4 };

    vector<vector<int>> ret = (new Solution())->threeSum(nums);

    cout << endl;
    for (auto& vec : ret) {
        for (auto& e : vec)
            cout << e << " ";
        cout << endl;
    }
}