/**
 * @brief: Leetcode_110_平衡二叉树
 * @link: https://leetcode.cn/problems/balanced-binary-tree/description/
 * @author: liangj.zhang
 * @date: 13/11/2025
 * 
 * @Difficulty: Easy
 * 
 * @Label: Tree(Structual Judgment Of Trees)
 * 
 * @Retrospect(worthy 1 - 5): 3
 * 
 * @brief_content: 判断一个树是否是平衡二叉树
 *  + 平衡二叉树：平衡二叉树 是指该树所有节点的左右子树的高度相差不超过 1。
 * 
 * @thoughts:
 *  + 【思路 1】：递归，剪枝版
 *      求树的高度的题，都不用变换，比较下左右两个子树的高度就行了；
 * 
 *      + 分析：
 *          + 时间复杂度：O(n)，平衡二叉树（或者接近平衡二叉树）的情况，都是要遍历完全的；
 *          + 空间复杂度：O(h)
 *      + rank:
 *          + 时间效率：0 ms, 击败 100%
 *          + 空间效率：22.50 MB, 击败 84.13%
 */

#include <iostream>
#include "../../../../../Include/Leetcode/Tree/Tree.h"
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
    bool ans = true;
    int __isBalanced(TreeNode* root) {

        if (!ans || !root) return 0;
        int left_h = __isBalanced(root->left);
        int right_h = __isBalanced(root->right);

        if (std::abs(left_h - right_h) > 1)
            this->ans = false;
        
        return std::max(left_h, right_h) + 1;
    }
public:
    bool isBalanced(TreeNode* root) {
        
        this->ans = true;
        __isBalanced(root);
        return this->ans;
    }
};