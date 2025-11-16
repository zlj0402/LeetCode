/**
 * @brief: Leetcode_951_翻转等价二叉树
 * @link: https://leetcode.cn/problems/flip-equivalent-binary-trees/description/
 * @author: liangj.zhang
 * @date: 16/11/2025
 * 
 * @Difficulty: Medium
 * 
 * @Label: Tree(dfs)
 * 
 * @Retrospect(worthy 1 - 5): 3
 * 
 * @thoughts:
 *  + 【思路 1】：dfs, 这是肯定，如何具体分如何 dfs，之后来做；
 *      第一次写的，是 chat 写的，
 *      我是想着 root1 每次先遍历左边，再右边；
 *      root2 根据哪边与 root1->left->val 相同遍历哪边，另一边相反；
 *      我无法优雅的做出来，给我考虑半天；
 * 
 *      chat 写的这个是很优雅，但还无法提前终止；
 */
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
public:
    bool flipEquiv(TreeNode* root1, TreeNode* root2) {
        // 若同为空，相等
        if (!root1 && !root2) return true;

        // 若一空一非空 or 值不同，不相等
        if (!root1 || !root2 || root1->val != root2->val) return false;

        // 两种情况
        // 情况1：不翻转
        bool same =
            flipEquiv(root1->left, root2->left) &&
            flipEquiv(root1->right, root2->right);

        // 情况2：翻转
        bool flipped =
            flipEquiv(root1->left, root2->right) &&
            flipEquiv(root1->right, root2->left);

        return same || flipped;
    }
};