/**
 * @brief: Leetcode_2331_计算布尔二叉树的值
 * @link: https://leetcode.cn/problems/evaluate-boolean-binary-tree/description/
 * @author: liangj.zhang
 * @date: 20/11/2025
 * 
 * @Difficulty: Easy
 * 
 * @Lable: Tree(post-order traversal)
 * 
 * @Retrospect(worthy 1 - 5): 2
 * 
 * @thoughts:
 *  + 【思路 1】：递归，后序遍历
 *      树的简单难度，没有挑战性，全当签到了；
 *      + 分析：
 *          + 时间复杂度：O(n)
 *          + 空间复杂度：O(h)
 *      + rank:
 *          + 时间效率：0 ms, 击败 100%
 *          + 空间效率：23.87 MB, 击败 52.72%
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
public:
    bool evaluateTree(TreeNode* root) {
        
        if (!root->left && !root->right) return root->val;
        bool b_left = evaluateTree(root->left);
        bool b_right = evaluateTree(root->right);

        return root->val == 2 ? (b_left | b_right) : (b_left & b_right);
    }
};