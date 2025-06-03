// 
// Created by liangj.zhang on 3/6/2025
//

// 思路：
// 1. 先给数组排个序；
// 2. 通过题目我们能够了解的：
//		2.1 三个数和为 0，必定有一个数字为 < 0 的；
//		2.2 假如我们确定一个数 i，我们从前往后遍历；
//		2.3 内层第二层循环，我们从下一个数 (j = i + 1) 开始，不必要再从 0 开始;
//		2.4 第二个数确定之后呢，第三个数也就确定了；
//		2.5 第三个数，必定是第二个数之后；从下一个位置开始 (k = j + 1)；
//		2.6 在剩余范围内，进行二分查找；
// chat: O(n^2*logn)
// 
// 思路2：
//	chat 给的思路，双指针
// 1. 排个序
// 2. 选定一个 值
// 3. 剩余范围内，最左最右两个指针；
// 4. 三数和 > 0, 右指针向左移；
// 5. 三数和 < 0, 左指针向右移；
// 6. 三数和 == 0, 记录；可以继续左移右移，以免有相同的数值；
// 时间效率：排序：O(nlogn) + O(n^2)
// 
// 思路2 -- rank:
// 时间效率：47 ms, 击败 90.27%
// 空间效率: 28.49 MB, 击败 56.21%
//

#include <iostream>
using std::cout;
using std::endl;

#include <vector>
#include <numeric>
#include <algorithm>
using std::vector;
using std::swap;

class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {

        int n = nums.size();

        vector<vector<int>> ret;

        sort(nums.begin(), nums.end());

        for (int i = 0; i < n - 2; i++) {

            // 重复的元素跳过考虑
            if (i > 0 && nums[i] == nums[i - 1]) continue;
            
            int l = i + 1;
            int r = n - 1;
            int _sum = -nums[i];

            while (l < r) {

                if (nums[l] + nums[r] > _sum)
                    r--;
                else if (nums[l] + nums[r] < _sum)
                    l++;
                else {

                    ret.push_back(vector<int>{nums[i], nums[l], nums[r]});

                    // 略过相同的组合
                    while (l < r && nums[l + 1] + nums[r] == _sum) l++;
                    while (r > l && nums[l] + nums[r - 1] == _sum) r--;
                    l++;
                    r--;
                }
            }
        }

        return ret;
    }
};

int main() {

    //vector<int> nums{ -1,0,1,2,-1,-4 };

    vector<int> nums{ 0, 0, 0 };
    auto ret = (new Solution())->threeSum(nums);

    for (auto it : ret) {

        for (auto t : it)
            cout << t << " ";
        cout << endl;
    }
}