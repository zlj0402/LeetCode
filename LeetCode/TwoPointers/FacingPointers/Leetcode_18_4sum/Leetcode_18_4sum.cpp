/**
 * @brief: Leetcode_18_四数之和
 * @link: https://leetcode.cn/problems/4sum/description/
 * @author: liangj.zhang
 * @date: 27/8/2025
 * 
 * @Difficulty: Medium
 * 
 * @Label: Two Pointers(Facing)
 * 
 * @Retrospect(worthy 1 - 5): 2
 * 
 * @thoughts:
 *      + 【思路 1】排序 + 相向双指针 + 优化剪枝
 *          思路跟三数之和还是一样的，只是外面多套了一层枚举，时间复杂度是 O(n^3)
 *          + 分析：
 *              + 时间复杂度：排序O(nlogn) + 嵌套的相向双指针 O(n^3) ==> O(n^3)
 *              + 空间复杂度：没有申请额外的空间 O(1)
 *          + rank:
 *              + 时间效率：0 ms, 击败 100%
 *              + 空间效率：17.09 MB, 击败 60.48%
 * 
 *      + 【思路 1.2】以递归的方式实现（也是多数之和的模板了）
 *          本质上，还是上面的思路，做法是以递归的方式实现，5、6数之和，也能按照这个模板来；
 *          这是别人写的，有更优化的小点，在前 k 个数之和 > target 的情况：
 *              最前面的 k 个数 > target => 直接 break
 *              最后面的 k - 1 数 + 枚举确定的数 < target，枚举还能往后改变情况
 *              但是前 k 个数 > target 情况改变不了
 *          + 分析：
 *              + 时间复杂度：排序O(nlogn) + 嵌套的相向双指针 O(n^3) ==> O(n^3)
 *              + 空间复杂度：至少递归 n - k - 1 次 ==> O(n)
 *          + rank:
 *              + 时间效率：3 ms, 击败 90.18%
 *              + 空间效率：17.68 MB, 击败 5.28%
 */

#include <iostream>
#include <vector>
using std::cout;
using std::endl;
using std::vector;


#include <algorithm>
// 【思路 1】
/* 
class Solution {
public:
    vector<vector<int>> fourSum(vector<int>& nums, int target) {

        sort(nums.begin(), nums.end());
        
        vector<vector<int>> res;
        int size = nums.size();
        for (int i = 0; i < size - 3; ++i) {

            if (i != 0 && nums[i] == nums[i - 1]) continue;

            if ((long long)nums[i] + nums[i + 1] + nums[i + 2] + nums[i + 3] > target) break;
            if ((long long)nums[i] + nums[size - 3] + nums[size - 2] + nums[size - 1] < target) continue;

            for (int j = i + 1; j < size - 2; ++j) {
                
                if (j != i + 1 && nums[j] == nums[j - 1]) continue;

                if ((long long)nums[i] + nums[j] + nums[j + 1] + nums[j + 2] > target) break;
                if ((long long)nums[i] + nums[j] + nums[size - 2] + nums[size - 1] < target) continue;

                int m = j + 1;
                int n = size - 1;

                while (m < n) {

                    long long sum = (long long)nums[i] + nums[j] + nums[m] + nums[n];
                    if (sum < target) 
                        ++m;
                    else if (sum > target)
                        --n;
                    else {
                        res.push_back({nums[i], nums[j], nums[m++], nums[n--]});
                        while (m < n && nums[m] == nums[m - 1]) ++m;
                        while (m < n && nums[n + 1] == nums[n]) --n;
                    }
                }
            }
        }

        return res;
    }
};
*/

// 【思路 1.2 -- 递归方式】

class Solution
{
public:
    std::vector<std::vector<int>> fourSum(std::vector<int> &nums, int target)
    {
        std::sort(nums.begin(), nums.end());
        return kSum(nums, target, 0, 4);
    }

private:
    /**
     * 通用的 k 数之和求解函数
     * @param nums 已排序的数组
     * @param target 目标和
     * @param start 搜索起始位置
     * @param k 需要找的数字个数
     * @return 所有满足条件的 k 元组
     */
    std::vector<std::vector<int>> kSum(std::vector<int> &nums, long long target, int start, int k)
    {
        std::vector<std::vector<int>> result;

        // 边界检查
        if (start >= nums.size() || nums.size() - start < k)
        {
            return result;
        }

        // 递归终止条件：k == 2，使用双指针求解两数之和
        if (k == 2)
        {
            return twoSum(nums, target, start);
        }

        // 递归情况：固定一个数，求解 (k-1) 数之和
        for (int i = start; i <= nums.size() - k; ++i)
        {
            // 去重：跳过重复的数字
            if (i > start && nums[i] == nums[i - 1])
            {
                continue;
            }

            // 剪枝优化：最小情况检查
            long long minSum = nums[i];
            for (int j = 1; j < k; ++j)
            {
                minSum += nums[i + j];
            }
            if (minSum > target)
            {
                break;
            }

            // 剪枝优化：最大情况检查
            long long maxSum = nums[i];
            for (int j = 1; j < k; ++j)
            {
                maxSum += nums[nums.size() - j];
            }
            if (maxSum < target)
            {
                continue;
            }

            // 递归调用：在剩余部分中寻找 (k-1) 个数
            std::vector<std::vector<int>> subResults = kSum(nums, target - nums[i], i + 1, k - 1);

            // 将当前数字添加到所有子结果的前面
            for (auto &subResult : subResults)
            {
                subResult.insert(subResult.begin(), nums[i]);
                result.push_back(subResult);
            }
        }

        return result;
    }

    /**
     * 两数之和的双指针实现
     * @param nums 已排序的数组
     * @param target 目标和
     * @param start 搜索起始位置
     * @return 所有满足条件的二元组
     */
    std::vector<std::vector<int>> twoSum(std::vector<int> &nums, long long target, int start)
    {
        std::vector<std::vector<int>> result;
        int left = start;
        int right = nums.size() - 1;

        while (left < right)
        {
            long long sum = (long long)nums[left] + nums[right];

            if (sum < target)
            {
                left++;
            }
            else if (sum > target)
            {
                right--;
            }
            else // sum == target
            {
                result.push_back({nums[left], nums[right]});

                // 去重
                while (left < right && nums[left] == nums[left + 1])
                {
                    left++;
                }
                while (left < right && nums[right] == nums[right - 1])
                {
                    right--;
                }

                left++;
                right--;
            }
        }

        return result;
    }
};


int main() {

    vector<int> nums = {1,0,-1,0,-2,2};
    int target = 0;

    vector<vector<int>> res = (new Solution())->fourSum(nums, target);

    for (auto& v : res) {
        for (auto& e : v)
            cout << e << " ";
        cout << endl;
    }
}