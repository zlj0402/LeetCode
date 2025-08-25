// 
// Created by liangj.zhang on 3/6/2025
//

// updated on 24/8/2025:
//          + 回过头来再看一遍题目，突然有些不理解会什么，每次遍历从 idx i 后面以为开始;
//          + 会什么说从 idx i + 1 开始遍历，就可以避免重复呢？想了很久没有答案；没有答案的时候，就回归原始，手动走一遍；
//          + 我用题目中第一个例子，并在后面多一位 3，排序后的结果是：[-4, -1, -1, 0, 1, 2, 3]
//          + 第一层遍历 idx i 经过 idx 0(nums[0] == -4)，有组合 [-4, 1, 3];
//          + 对于第一层遍历到 idx 4(nums[4] == 1) 时，按照我们的现在的疑虑，如果从 idx 0 开始，那么 [-1, -4, 3] 的组合就会重复考虑；
//          + 总结下：
//              + 疑问：为什么内部循环，每次不从 idx 0 开始；
//              + 自答：
//                  1. 当前遍历的 idx i
//                  2. 如果能和 idx m(m < i) 组成三元组
//                  3. 那当之前 idx 经过 m 位置时，
//                  4. 就已经找到 (nums[m], nums[i], nums[k]) 这个三元组了(k 是另外一个确定其二，必定确定的位置)
// updated on 25/8/2025:
//          + 添加 思路2.2 的小优化，顺便重写一遍；

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
// 时间效率：排序：O(nlogn) + O(n^2) == O(n^2)
// 
// 思路2 -- rank:
// 时间效率：47 ms, 击败 90.27%
// 空间效率: 28.49 MB, 击败 56.21%
//  
// 思路2.2： 基于思路2之上的小优化
//      1. 当内循环，前两个数 & 当前遍历位置，三数之和 > 0，那么后面的数和 当前遍历位置之和，只会更大；
//      2. .......，后两个数 & 当前遍历位置，三叔之和 < 0，那么所有可能的组合都不会 大于0；没有遍历的必要了；
// 
// 思路2.2 -- rank:
// 时间效率：42 ms, 击败 96.09%
// 空间效率：28.4 MB, 击败 77.53%
//

#include <iostream>
#include <vector>
using std::vector;
using std::cout;
using std::endl;

#include <numeric>
#include <algorithm>
using std::swap;

// 【2.2】
class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        
        int size = nums.size();
        vector<vector<int>> res;

        sort(nums.begin(), nums.end());
        
        for (int i = 0; i < size - 2; ++i) {

            if (i != 0 && nums[i] == nums[i - 1])
                continue;

            if (nums[i] + nums[i + 1] + nums[i + 2] > 0 ||
                nums[i] + nums[size - 2] + nums[size - 1] < 0)
                continue;

            int j = i + 1;
            int k = size - 1;
            while (j < k) {
                
                int sum = nums[i] + nums[j] + nums[k];
                if (sum < 0)
                    ++j;
                else if (sum > 0)
                    --k;
                else {
                    res.push_back(vector<int>{nums[i], nums[j++], nums[k--]});
                    while (j < k && nums[j] == nums[j - 1]) ++j;
                    while (j < k && nums[k] == nums[k + 1]) --k;
                }
            }

        }

        return res;
    }
};

// 【2】
/*
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
*/

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