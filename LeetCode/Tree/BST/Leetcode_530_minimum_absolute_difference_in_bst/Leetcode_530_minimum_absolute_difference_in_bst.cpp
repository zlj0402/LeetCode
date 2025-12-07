/**
 * @brief: Leetcode_530_二叉搜索树的最小绝对差
 * @link: https://leetcode.cn/problems/minimum-absolute-difference-in-bst/description/
 * @author: liangj.zhang
 * @date: 7/12/2025
 * 
 * @Difficulty: Easy
 * 
 * @Label: BST
 * 
 * @Retrospect(worthy 1 - 5): 3
 * 
 * @thoughts:
 *  + 【思路 1】：BST 中序遍历
 *      BST 中序遍历的过程，刚好是 从小到大 遍历的；
 *      差值的最小，一定出现在从小到大的过程中，相邻的两个值中；
 * 
 *      + 分析：
 *          + 时间复杂度：O(n)
 *          + 空间复杂度：O(n)
 *      + rank: 
 *          + 时间效率: 0 ms, 击败 100%
 *          + 空间效率: 24.89 MB, 击败 81.06%
 */

#include "../../../../Include/Leetcode/Tree/Tree.h"
using Leetcode::Tree::BinaryTree::TreeNode;

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
private:
    int last;
    int min;
    void __getMinimumDifference(TreeNode* root) {

        if (!root) return;

        __getMinimumDifference(root->left);
        // int sub = std::abs(root->val - last);
        int sub = root->val - last; // BST 中，中序遍历，一个只会比一个大，没必要 abs()
        if (sub < min) min = sub;
        last = root->val;
        __getMinimumDifference(root->right);
    }
public:
    int getMinimumDifference(TreeNode* root) {
        
        last = INT_MIN >> 1;    // 避免减法溢出，即使是有符号数；任何有符号整数溢出（signed integer overflow）都是 UB
        min = INT_MAX;
        __getMinimumDifference(root);
        return min;
    }
};