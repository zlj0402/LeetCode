/**
 * @brief: Leetcode_167_两数之和II-输入有序数组
 * @link: https://leetcode.cn/problems/two-sum-ii-input-array-is-sorted/description/
 * @author: liangj.zhang
 * @date: 24/8/2025
 * 
 * @Difficulty: Medium
 * 
 * @Label: Two Pointers(Facing)
 * 
 * @Retrospect(Worthy 0 - 5): 2
 * 
 * @thoughts:
 *      + 用相向的双指针，这题非常 easy；
 * 
 *      + 分析：
 *          + 时间复杂度：相向遍历，最多遍历一整个数组 => O(n)
 *          + 空间复杂度：没有额外的使用数组长度的栈空间，也没有申请动态空间 => O(1)
 *      
 *      + rank:
 *          + 时间效率：0 ms, 击败 100%
 *          + 空间效率：19.03 MB, 击败 83.72%
 */

 #include <vector>
 #include <iostream>
 using std::vector;
 using std::cout;
 using std::endl;

class Solution {
public:
    vector<int> twoSum(vector<int>& numbers, int target) {
        
        // 每个输入 只对应唯一的答案
        int l = 0;
        int r = numbers.size() - 1;

        while (l < r) {

            int sum = numbers[l] + numbers[r];
            if (sum < target)
                ++l;
            else if (sum > target)
                --r;
            else
                return {l + 1, r + 1};
        }

        return {};
    }
};

int main() {

    int target = 9;
    vector<int> nums = {2,7,11,15};

    vector<int> res = (new Solution())->twoSum(nums, target);

    cout << "res[0] = " << res[0] << " "
        << "res[1] = " << res[1] << endl;

    return 0;
}