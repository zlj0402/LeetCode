/**
 * @brief: Leetcode_1161_最大层内元素和
 * @link: https://leetcode.cn/problems/maximum-level-sum-of-a-binary-tree/description/
 * @author: liangj.zhang
 * @date: 10/1/2026
 * 
 * @Difficulty: Medium
 * 
 * @Label: BFS
 * 
 * @Retrospect(worthy 1 - 5): 3
 * 
 * @thoughts:
 *  + 【思路 1】：BFS
 *      计算每层元素和，只有比之前大的时候，记录当前层；这样就满足提议了
 *      + 分析：
 *          + 时间复杂度：O(n)
 *          + 空间复杂度：O(n)
 *      + rank:
 *          + 时间效率：0 ms, 击败 100%
 *          + 空间效率：105.56 MB, 击败 77.36%
 */
#include "../../../../../Include/Leetcode/Tree/Tree.h"
using Leetcode::Tree::BinaryTree::TreeNode;
using namespace Leetcode::Tree::BinaryTree;

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

class Solution {
public:
    int maxLevelSum(TreeNode* root) {
        
        vector<TreeNode*> arr{root}, tmp;
        int max_sum{root->val}, max_level{1};
        int sum{0}, level{1};

        while (arr.size()) {

            sum = 0;
            int size = arr.size();
            tmp.clear();
            for (int i = 0; i < size; ++i) {

                TreeNode* cur = arr[i];
                sum += cur->val;
                if (cur->left) tmp.push_back(cur->left);
                if (cur->right) tmp.push_back(cur->right);
            }

            if (sum > max_sum) {

                max_sum = sum;
                max_level = level;
            }

            arr.swap(tmp);
            ++level;
        }

        return max_level;
    }
};