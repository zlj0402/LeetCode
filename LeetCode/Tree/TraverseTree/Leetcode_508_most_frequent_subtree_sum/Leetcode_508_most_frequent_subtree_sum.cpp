/**
 * @brief: Leetcode_508_出现次数最多的子树元素和
 * @link: https://leetcode.cn/problems/most-frequent-subtree-sum/description/
 * @author: liangj.zhang
 * @date: 21/11/2025
 * 
 * @Difficulty: Medium
 * 
 * @Label: Tree & HashMap
 * 
 * @Retrospect(worthy 1 - 5): 3
 * 
 * @thoughts:
 *  值得学习使用 std::max_element，以及比较器的两种写法；
 * 
 *      + 分析：
 *          + 时间复杂度：遍历树 O(n) + max_element() 查找最大值 O(n) + 再遍历找 key O(n)
 *          + 空间复杂度：O(h) + O(n) => O(n)
 *      + 写法 1
 *          + rank:
 *              + 时间效率：8 ms, 击败 47.68%
 *              + 空间效率：24.27 MB, 击败 95.94%
 *      + 写法 2
 *          + rank:
 *              + 时间效率：3 ms, 击败 99.03%
 *              + 空间效率：24.32 MB, 击败 94.79%
 */

#include "../../../Include/Leetcode/Tree/Tree.h"
using Leetcode::Tree::BinaryTree::TreeNode;

#include <algorithm>
#include <vector>
using std::vector;

#include <unordered_map>
using std::unordered_map;

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */

#define um unordered_map

class Solution {
private:
    static um<int, int> rec;
    static bool Cmp(const std::pair<const int, int>& a,
                    const std::pair<const int, int>& b) {
        return a.second < b.second;
    }

    int __findFrequentTreeSum(TreeNode* root) {
        
        if (!root) return 0;

        int left = __findFrequentTreeSum(root->left);
        int right = __findFrequentTreeSum(root->right);

        int sum = left + right + root->val;
        if (rec.find(sum) != rec.end()) 
            ++rec[sum];
        else
            rec[sum] = 1;

        return sum;
    }
public:
    // 写法 2
    vector<int> findFrequentTreeSum(TreeNode* root) {
        
        rec.clear();
        vector<int> ret;
        __findFrequentTreeSum(root);
        int maxValue = std::max_element(rec.begin(), rec.end(), Cmp)->second;
        for (const auto& [k, v] : rec) {

            if (v == maxValue) {
                ret.push_back(k);
            }
        }

        return ret;
    }

    // 写法 1
    // vector<int> findFrequentTreeSum(TreeNode* root) {
        
    //     rec.clear();
    //     vector<int> ret;
    //     __findFrequentTreeSum(root);
    //     int maxValue = std::max_element(rec.begin(), rec.end(), [](const auto& a, const auto& b) {
    //                         return a.second < b.second;
    //     })->second;
    //     for (const auto& [k, v] : rec) {

    //         if (v == maxValue) {
    //             ret.push_back(k);
    //         }
    //     }

    //     return ret;
    // }
};

um<int, int> Solution::rec{};